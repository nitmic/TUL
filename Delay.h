#pragma once
#include <functional>

namespace TUL{
	class Delay{
	public:
		Delay() : i(-1){};
		Delay(int i, std::function<void(void)> func) : i(i), func(func){};
		bool isActive(){
			return i>0;
		}
		bool step(){
			--i;
			if(i!=0) return false;
			func();
			return true;
		}
	private:
		int i;
		std::function<void(void)> func;
	};
};