#pragma once
#include <array>
#include "Error.h"

/*
*@class RingBuffer
*@ˆÈ‘O‚Ìó‘Ô‚ğ‚¿‚å‚Á‚Æ‚ÌŠÔ•Û‚µ‚Ä‚¨‚«‚½‚¢‚à‚Ì‚É
*  ˆË‘¶ TUL::Error
*/

namespace TUL{
	template<class T, int N>
	class RingBuffer{
	public:
		RingBuffer() : m_CurrentIndex(0){};
		RingBuffer(T & data) : m_CurrentIndex(0){
			m_Data.fill(data);
		}

		T & current(){
			return m_Data[m_CurrentIndex];
		}
	
		T & operator*(){
			return current();
		}
		T & operator->(){
			return current();
		}

		void update(T & data){
			update();
			m_Data[m_CurrentIndex] = data;
		}
		void update(){
			m_CurrentIndex = (m_CurrentIndex + 1)%N;
		}


		T & prev(unsigned int x = 1){
			if(x>N) ERROR_MSG(_T("x‚ª‘å‚«‚·‚¬‚Ü‚·"));
			if(x<0) ERROR_MSG(_T("x‚Í”ñ•‰‚Å‚·"));
			int preIndex = (m_CurrentIndex-x)%N;
			if(preIndex<0){
				preIndex = N - preIndex;
			}
			return m_Data[preIndex];
		}
	private:
		int m_CurrentIndex;
		std::array<T, N> m_Data;
	};
};