#include "FPSModerator.h"
#include <boost\chrono.hpp>
#include "RingBuffer.hpp"
#include <algorithm>
/*
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
*/
namespace TUL{
	enum{BufferSize = 30};
	struct FPSModerator::Impl{
		Impl(unsigned int fps=60) : frame(fps){}
		boost::chrono::steady_clock::time_point lastTime;
		RingBuffer<unsigned int, BufferSize> currentFPSs;
		unsigned int frame;	//ê›íËFPS
		boost::chrono::duration<int_least64_t, boost::nano> errorTime;
	};
	FPSModerator::FPSModerator(unsigned int settingFPS){
		__impl__ = std::make_shared<Impl>(settingFPS);
	}
	bool FPSModerator::step(){
		auto currentTime  = boost::chrono::high_resolution_clock::now();
		auto pastTime     = (currentTime - __impl__->lastTime) + __impl__->errorTime;
		auto frameBase = boost::chrono::milliseconds(1000/__impl__->frame);

		if(frameBase <= pastTime){
			__impl__->lastTime = currentTime;
			__impl__->currentFPSs.update(boost::chrono::milliseconds(1000) / pastTime);
			__impl__->errorTime = pastTime % frameBase;
			return true;
		}
		return false;
	}
	void FPSModerator::setFPS(unsigned int fps){
		__impl__->frame = fps;
	}
	unsigned int FPSModerator::getActualFPS(){
		int sum = 0;
		for(auto it=__impl__->currentFPSs.begin(); it!=__impl__->currentFPSs.end(); it++){
			sum += *it;
		}
		return sum/BufferSize;
	}
};