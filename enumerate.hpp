#pragma once
#include <algorithm>
#include <functional>
#include <vector>
#include <map>


namespace TUL{

	template<typename Result, typename Function>
	class Enumerate{
	public:
		Enumerate(unsigned long i, Function func) : index(i), func(func) {};

		template<typename T1> Result operator()(T1 t1){
			++index;
			return func(t1, index-1);
		}
	private:
		unsigned long index;
		Function func;
	};

	template<typename Function>
	class Enumerate<void, Function>{
	public:
		Enumerate(unsigned long i, Function func) : index(i), func(func) {};

		template<typename T1> void operator()(T1 t1){
			++index;
			func(t1, index-1);
		}
	private:
		unsigned long index;
		Function func;
	};
	
	template<typename Result, typename Function>
	auto enumerate(unsigned long i, Function func) -> Enumerate<Result, Function>{
		return Enumerate<Result, Function>(i, func);
	}
	template<typename Result, typename Function>
	auto enumerate(Function func) -> Enumerate<Result, Function>{
		return Enumerate<Result, Function>(0, func);
	}
};