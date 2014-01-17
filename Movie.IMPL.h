#pragma once
#include <memory>
#include <string>
#include <vector>
#include <assert.h>

#include "Movie.h"

namespace TUL{
	//--------------------------------- Struct ------------------------------------------
	//-----------------------------------------------------------------------------------

	struct MovieFile;
	struct MovieStream;

	typedef std::shared_ptr<MovieFile> FilePtr;
	typedef std::shared_ptr<MovieStream> StreamPtr;
	typedef std::shared_ptr<AVFrame> FramePtr;
	typedef std::shared_ptr<struct SwsContext> SwsCtxPtr;


	struct MovieStream{
		MovieStream() : CodecCtx(NULL){init();}
		MovieStream(FilePtr parent, AVCodecContext * context, int idx) : CodecCtx(context), StreamIdx(idx), parent(parent){init();}
		~MovieStream(){
			avcodec_close(CodecCtx);
		}
		void init(){}

		AVCodecContext * CodecCtx;

		int StreamIdx;
		std::weak_ptr<MovieFile> parent;
	};

	struct MovieFile{
		std::shared_ptr<AVFormatContext> FmtCtx;
		std::vector<StreamPtr> Streams;
		~MovieFile(){
			Streams.clear();
			FmtCtx.reset();
		}
	};

	//------------------------------ Function -------------------------------------------
	//-----------------------------------------------------------------------------------

	void AVFormatContextRelease(AVFormatContext * p){
		av_close_input_file(p);
	}

	void AVFrameRelease(AVFrame * p){
		avcodec_free_frame(&p);
	}

	void SwsContextRelease(struct SwsContext * p){
		sws_freeContext(p);
	}

	namespace{
		AVFrame * initFrame(){
			// �t���[���̈���m��
			AVFrame *frame_raw = avcodec_alloc_frame();
			assert(frame_raw!=nullptr);

			std::fill(frame_raw->data, frame_raw->data+8, nullptr);

			return frame_raw;
		}

		FramePtr initFrame(int width, int height, std::shared_ptr<uint8_t> * pBuffer){
			// �ۑ��p�o�b�t�@���m��
			int numBytes  = avpicture_get_size(PIX_FMT_RGB32, width, height);
			auto buffer_raw = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));
			assert(buffer_raw!=nullptr);
			*pBuffer = std::shared_ptr<uint8_t>(buffer_raw, av_free);

			auto raw_frame = initFrame();
			auto frame = std::shared_ptr<AVFrame>(raw_frame, AVFrameRelease);

			// �o�b�t�@���t���[���փZ�b�g
			avpicture_fill(
				(AVPicture *)(frame.get()), buffer_raw, PIX_FMT_RGB32, width, height
			);

			return frame;
		}

		FilePtr loadFile(std::string fileName){
			auto file = std::make_shared<MovieFile>();
			assert(file!=nullptr);

			// �t�@�C���̃w�b�_��ǂ݁A�t�H�[�}�b�g�𓾂�
			AVFormatContext * pFormatContext = NULL;
			if (avformat_open_input(&pFormatContext, fileName.c_str(), NULL, NULL)!=0) return nullptr;
			file->FmtCtx = std::shared_ptr<AVFormatContext>(pFormatContext, AVFormatContextRelease);

			// �t�@�C���̒��g����X�g���[�����𓾂�
			if (av_find_stream_info(file->FmtCtx.get()) < 0) return nullptr;

			return file;
		}

		StreamPtr createStream(FilePtr file, int index, int width, int height){
			auto stream = std::make_shared<MovieStream>(file, file->FmtCtx->streams[index]->codec, index);
			assert(stream!=nullptr);

			// codec��T��
			AVCodec *codec = avcodec_find_decoder(stream->CodecCtx->codec_id);
			if (codec->capabilities & CODEC_CAP_TRUNCATED) stream->CodecCtx->flags |= CODEC_FLAG_TRUNCATED;
		
			// codec���J��
			if (codec==nullptr || avcodec_open2(stream->CodecCtx, codec, NULL) < 0) {
				return false;
			}

			// MovieFile���ӔC������
			file->Streams.push_back(stream);

			return stream;
		}

		StreamPtr getStream(FilePtr file, int * streamIndex){
			/* �r�f�I�X�g���[����T�� */
			for(int i=0; i<file->FmtCtx->nb_streams; ++i){
				*streamIndex = i;
				if (file->FmtCtx->streams[i]->codec->codec_type != AVMEDIA_TYPE_VIDEO) continue;
			
				for(int j=0; j<file->Streams.size(); ++j){
					if (file->Streams[j]->StreamIdx == i){
						return file->Streams[j];
					}
				}
				return nullptr;
			}
		}

		bool getNextPacket(std::vector<FramePtr> & frameBuffer, FilePtr file, StreamPtr streamV, int * noDecodedBytes){
			AVPacket packet;
			while(av_read_frame(file->FmtCtx.get(), &packet) >= 0){
				for(auto it=file->Streams.begin();it!=file->Streams.end(); it++) {
					// �܂������֌W�Ȃ����͔̂�΂�
					if((*it)->StreamIdx!=packet.stream_index) continue;
				
					// �Ώۂ̃X�g���[���łȂ���Δ�΂�
					if (packet.stream_index!=streamV->StreamIdx) continue;
			
					*noDecodedBytes += packet.size;
					uint8_t * rawData = packet.data;
					
						

					while (*noDecodedBytes > 0) {
						/* �p�P�b�g����t���[���𕜍�����  */
						int isFinish = 0;
						auto ref_frames = (*it)->CodecCtx->refcounted_frames;
						auto frame = std::shared_ptr<AVFrame>(initFrame(), [ref_frames](AVFrame * p){
							if(ref_frames==1){
								av_frame_unref(p);
							}
							AVFrameRelease(p);
						});
						auto bytesDecoded = avcodec_decode_video2((*it)->CodecCtx, frame.get(), &isFinish, &packet);

						*noDecodedBytes -= bytesDecoded;
						rawData += bytesDecoded;
					
						/* �������܂��̏ꍇ�͎��̃p�P�b�g�܂ŏ������΂� */
						if (!isFinish) continue;
						
						av_free_packet(&packet);
						frameBuffer.push_back(frame);
						return true;
					}
				}
				av_free_packet(&packet);
			}
			return false;
		}
	
		FramePtr getNextFrame(std::vector<FramePtr> & frameBuffer, StreamPtr streamV, int * noDecodedBytes){
			// �t���[�����E���Ă���
			while (frameBuffer.size()==0) {
				if (!getNextPacket(frameBuffer, streamV->parent.lock(), streamV, noDecodedBytes)) {
					break;
				}
			}
			if (frameBuffer.empty()) return nullptr;

			auto output = frameBuffer.back();
			frameBuffer.erase(frameBuffer.begin());
			
			return output;
		}
	};
};