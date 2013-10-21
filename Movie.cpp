#include "Movie.IMPL.h"
#include "FPSModerator.h"


namespace TUL{
	struct MovieDecoder::Impl{
		Impl() : noDecodedBytes(0){};
		~Impl(){
			m_pFrameOut.reset();
			m_FrameBuffer.clear();

			if(m_pStreamV) m_pStreamV.reset();
			if(m_pFile) m_pFile.reset();
		}
	
		// 核のデータ
		FilePtr m_pFile;
		StreamPtr m_pStreamV;
	
		// 速度管理用
		FPSModerator m_Fps;

		// 動画情報保持
		int m_NumOfFrames;
		float m_FrameRate;
		float m_Duration;
		double m_SecPerFrame;

		// デコードされた画像データ出力用
		FramePtr m_pFrameOut;
		std::shared_ptr<uint8_t> m_Buffer;
	
		// 画面サイズが変更された時用に直前のサイズ保持
		int m_CurrentHeight;
		int m_CurrentWidth;
	
		// 毎回生成する必要もない為保持
		SwsCtxPtr m_pImgConvertContext;
	
		int noDecodedBytes;
		std::vector<AVFrame> m_FrameBuffer;
	};

	//////////////////////////////////////////////////////////////////////////////////////////

	void libavInit(){
		static bool done = false;
		if(!done){
			av_register_all();
			av_log_set_level(AV_LOG_ERROR);
		}
		done = true;
	}


	void MovieDecoder::init(){
		libavInit();
		close();
		__impl__ = std::make_shared<Impl>();
		setScreen();
	}

	void MovieDecoder::init(int width, int height){
		assert(m_Width<0 || m_Height<0);
		m_Width = width;
		m_Height = height;
		init();
	}

	void MovieDecoder::setScreen(){
		std::shared_ptr<uint8_t> buffer;
		__impl__->m_pFrameOut = initFrame(m_Width, m_Height, &buffer);
		__impl__->m_Buffer = buffer;
	}

	void MovieDecoder::setScreen(int width, int height){
		if(width==m_Width && height==m_Height) return;
		m_Width = width;
		m_Height = height;
		setScreen();
	}

	void MovieDecoder::close(){
		__impl__.reset();

		m_State = Closed;
	}

	bool MovieDecoder::open(std::string fileName){
		if (m_State != Closed) init();

		// ファイルのロード
		auto file = loadFile(fileName);
		__impl__->m_pFile = file;
		assert(file!=NULL);

		// ストリームのロード
		int streamIndex;
		__impl__->m_pStreamV = getStream(file, &streamIndex);
		if(__impl__->m_pStreamV==nullptr){
			// フレームレートの入手
			__impl__->m_FrameRate = (float)file->FmtCtx->streams[streamIndex]->r_frame_rate.num;
			__impl__->m_SecPerFrame = (double)file->FmtCtx->streams[streamIndex]->r_frame_rate.den / __impl__->m_FrameRate;
			__impl__->m_Duration = (float)file->FmtCtx->streams[streamIndex]->duration;
			__impl__->m_NumOfFrames = (int)file->FmtCtx->streams[streamIndex]->nb_frames;
		
			__impl__->m_pStreamV = createStream(file, streamIndex, m_Width, m_Height);
		}
	
		assert(__impl__->m_pStreamV!=nullptr);

		__impl__->m_Fps.setFPS(1/__impl__->m_SecPerFrame);
		m_State = Playing;

		return true;
	}

	uint8_t * MovieDecoder::decode(){
		if(m_State!=State::Playing) return nullptr;
		// fps管理
		if(__impl__->m_pFrameOut->data[0] && !__impl__->m_Fps.step()) return nullptr;

		// フレームの入手
		auto pFrameIn = getNextFrame(__impl__->m_FrameBuffer, __impl__->m_pStreamV, &__impl__->noDecodedBytes);
		if(pFrameIn==nullptr){
			m_State = State::Stopped;
			return nullptr;
		}

		// 画面のサイズが変わっていたら
		if (__impl__->m_CurrentWidth != m_Width || __impl__->m_CurrentHeight != m_Height) {
			__impl__->m_CurrentWidth = m_Width;
			__impl__->m_CurrentHeight = m_Height;
			__impl__->m_pImgConvertContext.reset();
		}

		if(__impl__->m_pImgConvertContext==nullptr){
			/* 変換の設定 */
			auto p = sws_getContext(
				__impl__->m_pStreamV->CodecCtx->width, __impl__->m_pStreamV->CodecCtx->height,
				__impl__->m_pStreamV->CodecCtx->pix_fmt, m_Width, m_Height, PIX_FMT_RGB32, 
				SWS_FAST_BILINEAR | SWS_CPU_CAPS_MMX2, NULL, NULL, NULL
			);
			assert(p!=NULL);
			__impl__->m_pImgConvertContext = std::shared_ptr<struct SwsContext>(p, SwsContextRelease);
		}

		/* 画像変換する */
		sws_scale(
			__impl__->m_pImgConvertContext.get(), pFrameIn->data, pFrameIn->linesize, 0,
			__impl__->m_pStreamV->CodecCtx->height, __impl__->m_pFrameOut->data, __impl__->m_pFrameOut->linesize
		);

		return __impl__->m_pFrameOut->data[0];
	}


	bool MovieDecoder::seek(int tsms){
		auto streamIndex = __impl__->m_pStreamV->StreamIdx;
		auto frame = av_rescale(
			tsms,
			__impl__->m_pFile->FmtCtx->streams[streamIndex]->time_base.den,
			__impl__->m_pFile->FmtCtx->streams[streamIndex]->time_base.num
		);

	   return seekByFrame(frame/1000);
	}

	bool MovieDecoder::seekByFrame(int frame){
		if(
			avformat_seek_file(
				__impl__->m_pFile->FmtCtx.get(),
				__impl__->m_pStreamV->StreamIdx,
				0, frame, frame, AVSEEK_FLAG_FRAME
			) < 0
		){
			return false;
		}
		avcodec_flush_buffers(__impl__->m_pStreamV->CodecCtx);
		return true;
	}
};