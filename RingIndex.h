#pragma once
#include <assert.h>

namespace TUL{
	class RingIndex{
	public:
		RingIndex() : size(-1), index(-1){}

		explicit RingIndex(int size) : size(size), index(0){
			assert(size>0);
		}
		RingIndex & operator++(){
			assert(size>0);

			index++;
			if(index>=size) index = 0;
			return *this;
		}
		RingIndex operator++(int){
			auto tmp = *this;
			++*this;
			return tmp;
		}
		RingIndex & operator--(){
			assert(size>0);
			index--;
			if(index<0) index = size-1;
			return *this;
		}
		
		RingIndex operator--(int){
			auto tmp = *this;
			--*this;
			return tmp;
		}
		
		RingIndex& operator=(int i){
			assert(size>0);
			while(i<0){i += size;}
			index = i % size;
			return *this;
		}
		
		RingIndex& operator+=(RingIndex i);
		RingIndex& operator+=(int i){
			*this = index + i;
			return *this;
		}
		
		RingIndex operator+(RingIndex i);
		RingIndex operator+(int i){
			RingIndex ri(size);
			ri = index + i;
			return ri;
		}
		
		RingIndex& operator-=(RingIndex i);
		RingIndex& operator-=(int i){
			*this = index - i;
			return *this;
		}
		
		RingIndex operator-(RingIndex i);
		RingIndex operator-(int i){
			RingIndex ri(size);
			ri = index - i;
			return ri;
		}

		operator int(){
			return index;
		}
	private:
		int index;
		int size;
	};
};