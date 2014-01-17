#pragma once
#include <memory>

/*
*@class FPSModerator
*　FPSModerator::stepで1f経過したかどうかを判定。Sleepはしない
*　依存 windows以外は boost::chrono http://d.hatena.ne.jp/faith_and_brave/20080908/
*/

namespace TUL{
	class FPSModerator{
	public:
		bool step();
		void setFPS(unsigned int fps);
		unsigned int getActualFPS();
		FPSModerator(unsigned int fps=60);
	private:
		struct Impl;
		std::shared_ptr<Impl> self;
	};
};