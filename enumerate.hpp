#pragma once
#include <algorithm>
#include <functional>
#include <vector>
#include <map>


/*
*@function enumerate
*�@�ȉ��̂悤�Ɏg��
*�@for_each(l.begin(), l.end(), enumerate<void>([](int elem, int index){
*�@  ...
*�@}));
*/


namespace TUL{

	template<typename Result, typename Function>
	class Enumerate{
	public:
		Enumerate(unsigned long i, Function func) : index(i), func(func) {};

		template<typename T1> inline Result operator()(T1 t1){
			++index;
			return func(t1, index-1);
		}
	private:
		unsigned long index;
		Function func;
	};

	// void �͕������ꉻ����K�v����
	template<typename Function>
	class Enumerate<void, Function>{
	public:
		Enumerate(unsigned long i, Function func) : index(i), func(func) {};

		template<typename T1> inline void operator()(T1 t1){
			++index;
			func(t1, index-1);
		}
	private:
		unsigned long index;
		Function func;
	};
	
	// �{��
	template<typename Result, typename Function>
	inline auto enumerate(unsigned long i, Function func) -> Enumerate<Result, Function>{
		return Enumerate<Result, Function>(i, func);
	}

	// start = 0 �̂���
	template<typename Result, typename Function>
	inline auto enumerate(Function func) -> Enumerate<Result, Function>{
		return Enumerate<Result, Function>(0, func);
	}
};