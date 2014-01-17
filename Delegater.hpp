#pragma once
#include <memory>


/*
*@class Delegater
*�@->���Z�q���g�����ƂŌ��̃I�u�W�F�N�g�ɃA�N�Z�X
*/

namespace TUL{
	template<class T>
	class Delegater{
	public:
		void setDelegateObject(std::shared_ptr<T> & object){
			delegate_object = object;
		}
		void releaseDelegateObject(){
			delegate_object.reset();
		}
		T * getDelegateObject(){
			return delegate_object.get();
		}
		T * operator->(){
			return getDelegateObject();
		}
		T * operator*(){
			return getDelegateObject();
		}
	private:
		std::shared_ptr<T> delegate_object;
	};

	template<class T>
	void ReleaseDelegater(T * p){
		p->releaseDelegateObject(); // ���̂��̂͐�ɏ���
		delete p;
	}
};