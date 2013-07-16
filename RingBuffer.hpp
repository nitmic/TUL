#pragma once
#include <array>
#include "Error.h"
#include <boost\iterator\iterator_facade.hpp>

/*
*@class RingBuffer
*@ˆÈ‘O‚Ìó‘Ô‚ğ‚¿‚å‚Á‚Æ‚ÌŠÔ•Û‚µ‚Ä‚¨‚«‚½‚¢‚à‚Ì‚É
*  ˆË‘¶ TUL::Error boost::iterator_facade
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
		void update(T && data){
			update();
			m_Data[m_CurrentIndex] = data;
		}
		void update(){
			m_CurrentIndex = (m_CurrentIndex + 1)%N;
		}


		T & prev(unsigned int x = 1){
			if(x>=N) ERROR_MSG(_T("x‚ª‘å‚«‚·‚¬‚Ü‚·"));
			int preIndex = (m_CurrentIndex-x)%N;
			if(preIndex<0){
				preIndex += N;
			}
			return m_Data[preIndex];
		}


		class iterator: public boost::iterator_facade<iterator, T, boost::forward_traversal_tag>{
			public:
				iterator(RingBuffer<T,N> * pBase,unsigned int index) : pBase(pBase), index(index){}
			private:
				friend class boost::iterator_core_access;
				void increment() { index++; }
				T& dereference() const {return pBase->prev(index);}
				bool equal(const iterator& other) const { return index == other.index; }
			private:
				unsigned int index;
				RingBuffer<T,N> * pBase;
		};
		iterator begin(){ return iterator(this, 0);}
		iterator end() { return iterator(this, N);}
	private:
		int m_CurrentIndex;
		std::array<T, N> m_Data;
	};
};