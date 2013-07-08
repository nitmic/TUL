#include "FPSModerator.h"
#include "RingBuffer.hpp"
#include <boost\chrono.hpp>

namespace TUL{
	struct FPSModerator::Impl{
		enum{BufferSize = 30};
		Impl(unsigned int fps=60) : frame(fps){}
		boost::chrono::steady_clock::time_point lastTime;
		RingBuffer<unsigned int,BufferSize> fpsBuffer;
		unsigned int frame;	//ê›íËFPS
	};
	FPSModerator::FPSModerator(unsigned int settingFPS){
		__impl__ = std::make_shared<Impl>(settingFPS);
	}
	bool FPSModerator::step(){
		auto currentTime  = boost::chrono::high_resolution_clock::now();
		auto pastTime     = (currentTime - __impl__->lastTime);
		auto frameBase = boost::chrono::nanoseconds((1000*1000*1000)/__impl__->frame);
		if(frameBase <= pastTime){
			__impl__->lastTime = currentTime;
			unsigned int fps = boost::chrono::milliseconds(1000) / pastTime;
			__impl__->fpsBuffer.update(fps);
			return true;
		}
		return false;
	}
	void FPSModerator::setFPS(unsigned int fps){
		__impl__->frame = fps;
	}
	unsigned int FPSModerator::getActualFPS(){
		unsigned int sum = 0;
		for(int i=0; i<Impl::BufferSize; i++){
			sum += __impl__->fpsBuffer.prev(i);
		}
		return sum / Impl::BufferSize;
	}
};