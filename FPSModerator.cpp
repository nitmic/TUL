#include "FPSModerator.h"

#include <array>
#include <algorithm>
#include <numeric>

#ifdef _MSC_VER
	#include <Windows.h>
#else
	#include <boost\chrono.hpp>
#endif

namespace TUL{
	struct FPSModerator::Impl{
		enum{BufferSize = 30};
		
		unsigned int frame;	//ê›íËFPS
		#ifdef _MSC_VER
			int fps, lastFPS;
			int lastTime;
			int errorTime;
			int currentTime;
			int pastTime;
		#else
			boost::chrono::duration<int_least64_t, boost::nano> errorTime;
			boost::chrono::steady_clock::time_point lastTime;
		#endif
		std::array<unsigned int, BufferSize> currentFPSs;
		int bufferIter;
	};

	FPSModerator::FPSModerator(unsigned int settingFPS){
		self = std::make_shared<Impl>();
		self->frame = settingFPS;
		#ifdef _MSC_VER
			self->lastFPS = -1;
			self->lastTime  = 0;
			self->errorTime = 0;
		#endif
		self->currentFPSs.fill(0);
		self->bufferIter = 0;
	}
	bool FPSModerator::step(){
		#ifdef _MSC_VER	
			auto currentTime  = timeGetTime();
			auto pastTime     = (currentTime - self->lastTime) * 3 + self->errorTime;
			auto frameBase = 3000/self->frame;
		#else
			auto currentTime  = boost::chrono::high_resolution_clock::now();
			auto pastTime     = (currentTime - self->lastTime) + self->errorTime;
			auto frameBase = boost::chrono::nanoseconds((1000*1000*1000)/self->frame);
		#endif
		if(frameBase <= pastTime){
			self->lastTime = currentTime;
			self->errorTime = pastTime % frameBase;
			
			#ifdef _MSC_VER
			self->currentFPSs[self->bufferIter] = 1000/pastTime;
			#else
				self->currentFPSs[self->bufferIter] = boost::chrono::milliseconds(1000) / pastTime;
			#endif
			self->bufferIter = (self->bufferIter+1)%Impl::BufferSize;
			return true;
		}
		return false;
	}
	void FPSModerator::setFPS(unsigned int fps){
		self->frame = fps;
	}
	unsigned int FPSModerator::getActualFPS(){
		return std::accumulate(self->currentFPSs.begin(), self->currentFPSs.end(), 0) / Impl::BufferSize;
	}
};