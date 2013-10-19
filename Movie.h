#pragma once
#include <string>
#include <memory>

extern "C" {
   #include <string.h>
   #include <libavcodec/avcodec.h>
   #include <libavformat/avformat.h>
   #include <libswscale/swscale.h>
#ifdef SOUND_OPENAL
   #include <signal.h>
   #include <AL/al.h>
   #include <AL/alc.h>
   #include <AL/alut.h>
#endif
}

namespace TUL{
	class MovieDecoder{
	public:
		enum State{Closed, Playing, Paused, Stopped };

		MovieDecoder() : m_Width(-1), m_Height(-1){};
		MovieDecoder(int width, int height) : m_Width(width), m_Height(height){init();}
		~MovieDecoder(){ if(m_State != Closed) close();}

		void init(int width, int height);
		bool open(std::string fileName);
		uint8_t * decode();
		void close();
		void setScreen(int width, int height);
		State getState(){return m_State;};
	
		bool seek(int tsms);
		bool seekByFrame(int frame);
	private:
		struct Impl;
		std::shared_ptr<Impl> __impl__;

		void init();
		void setScreen();
	
		bool m_NeedResize;
		int m_Width;
		int m_Height;
		State m_State;
	};
};