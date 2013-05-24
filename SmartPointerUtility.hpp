#pragma once
#include <vector>
#include <memory>

namespace{
	template<class T>
	void doNothing(T & p){};
};

/**
*@brief 型からポインタを除去するtype_trait.
*/
template<class T>
struct remove_pointer{};

template<class T>
struct remove_pointer<std::shared_ptr<T>>{
	typedef T type;
};

template<class T>
struct remove_pointer<std::weak_ptr<T>>{
	typedef T type;
};



/**
*@brief 型をshared_ptrにするtype_trait.
*/
template<class T>
struct toShared{};

template<class T>
struct toShared<std::shared_ptr<T>>{
	typedef std::shared_ptr<T> type;
};

template<class T>
struct toShared<std::weak_ptr<T>>{
	typedef std::shared_ptr<T> type;
};



/**
*@brief	shared_ptrにして返す
*@return shared_ptr
*@param p    : shared_ptr or weak_ptr.
*/
template<class T>
std::shared_ptr<T> & getShared(std::shared_ptr<T> & p){
	return p;
}

template<class T>
std::shared_ptr<T> getShared(std::weak_ptr<T> & p){
	return p.lock();
}


/**
*@brief	スマートポインタが有効かどうか. 有効なら関数を呼ぶ.
*@return bool
*@param p    : shared_ptr or weak_ptr.
        func : When smart-pointer is valid, it is called.

*/
template<class T>
void isExist(T & p){
	isExist(p, doNothing<toShared<T>::type>);
}

template<class T>
bool isExist(T & p, std::function<void(toShared<T>::type &)> func){
	if(auto & shared_p = getShared(p)){
		func(shared_p);
		return true;
	}
	return false;
}

/**
*@brief	vectorに入ったスマートポインタが有効かどうか. 有効なら関数を呼び, 無効ならeraseする.
*@return void
*@param v    : std::vector<shared_ptr or weak_ptr>
        func : When smart-pointer is valid, it is called.
*/
template<class T>
void isExistOrErase(std::vector<T> & v){
	isExistOrErase(v, doNothing<toShared<T>::type>);
}

template<class T>
void isExist(T & v, std::function<void(toShared<T>::type &)> func){
	for(auto it=v.begin();it!=v.end();++it){
		if(!isExist(*it, func)){
			it = v.erase(it);
		}
	}
}




/**
*@brief	スマートポインタが判定を満たしているかどうか. trueなら関数を呼ぶ.
*@return bool
*@param p         : shared_ptr or weak_ptr.
        func      : When checkFunc return true, it is called.
        checkFunc : When smart-pointer is valid, it is called.
*/
template<class T, typename Func>
bool isTrue(T & p, Func checkFunc){
	return isTrue(p, doNothing<toShared<T>::type>, checkFunc);
}

template<class T, typename Func>
bool isTrue(T & p, std::function<void(toShared<T>::type &)> func, Func checkFunc){
	if(auto & shared_p = getShared(p)){
		if(shared_p->checkFunc()){
			func(shared_p);
			return true;
		}
	}
	return false;
}

/**
*@brief	スマートポインタが判定を満たしているかどうか. trueなら関数を呼び, falseならeraseする.
*@return void
*@param v    : std::vector<shared_ptr or weak_ptr>
        func      : When checkFunc return true, it is called.
        checkFunc : When smart-pointer is valid, it is called.
*/
template<class T, typename Func>
bool isTrueOrErase(std::vector<T> & v, Func checkFunc){
	itTrueOrErase(v, doNothing<toShared<T>::type>, checkFunc);
}
template<class T, typename Func>
bool isTrueOrErase(std::vector<T> & v, std::function<void(toShared<T>::type &)> func, Func checkFunc){
	for(auto it=v.begin();it!=v.end();++it){
		if(!isTrue(*it, func, checkFunc)){
			it = v.erase(it);
		}
	}
}


/**
*@brief	スマートポインタが判定を満たしているかどうか. falseなら関数を呼ぶ.
*@return bool
*@param p         : shared_ptr or weak_ptr.
        func      : When checkFunc return false, it is called.
        checkFunc : When smart-pointer is valid, it is called.
*/
template<class T, typename Func>
bool isFalse(T & p, Func checkFunc){
	return isFalse(p, doNothing<toShared<T>::type>, checkFunc);
}
template<class T, typename Func>
bool isFalse(T & p, std::function<void(toShared<T>::type &)> func, Func checkFunc){
	if(auto & shared_p = getShared(p)){
		if(shared_p->checkFunc()){
			return true;
		}
		func(shared_p);
	}
	return false;
}