#pragma once
#include <memory>

/*
*@class FPSModerator
*Å@àÀë∂ boost::chrono http://d.hatena.ne.jp/faith_and_brave/20080908/
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
		std::shared_ptr<Impl> __impl__;
	};
};