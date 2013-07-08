#include "FPSModerator.h"
#include <boost\chrono.hpp>

namespace TUL{
	struct FPSModerator::Impl{
		Impl(unsigned int fps=60) : frame(fps){}
		boost::chrono::steady_clock::time_point lastTime;
		unsigned int currentFPS;
		unsigned int frame;	//ê›íËFPS
	};
	FPSModerator::FPSModerator(unsigned int settingFPS){
		__impl__ = std::make_shared<Impl>(settingFPS);
	}
	bool FPSModerator::step(){
		auto currentTime  = boost::chrono::high_resolution_clock::now();
		auto pastTime     = (currentTime - __impl__->lastTime);
		auto frameBase = boost::chrono::milliseconds(1000/__impl__->frame);
		if(frameBase <= pastTime){
			__impl__->lastTime = currentTime;
			__impl__->currentFPS = boost::chrono::milliseconds(1000) / pastTime;
			return true;
		}
		return false;
	}
	void FPSModerator::setFPS(unsigned int fps){
		__impl__->frame = fps;
	}
	unsigned int FPSModerator::getActualFPS(){
		return __impl__->currentFPS;
	}
};