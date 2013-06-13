#pragma once
#include <array>
#include <cstdarg>

template<class T, int N=2>
class Point{
	std::array<T, N> p;
public:
	Pointer(T x, ...){
		auto it = p.begin();
		*it++ = x;

		va_list argptr;
		va_start (argptr,x);
		for (; it!=p.end(); ++it){
			*it = va_arg(argptr, T);
		}

		va_end(argptr);
	}
	T & operator[](int index){
		return p[index];
	}	
	T & operator[](char index){
		switch(index){
		case 'x':
			return p[0];
		case 'y':
			if(N >= 2) return p[1];
		case 'z':
			if(N >= 3) return p[2];
		default:
			ERROR_MSG(_T("Argment is not 'x', 'y' or 'z'."));
			exit(0);
		};
	}

};


template<class T, int N=2>
class Vector{
	std::array<T, N> v;
public:
	Vector(T x, ...){
		auto it=v.begin();
		*it++ = x;

		va_list argptr;
		va_start (argptr,x);
		for (; it!=v.end(); ++it){
			*it = va_arg(argptr, T);
		}

		va_end(argptr);
	}
	T & operator[](int index){
		return v[index];
	}
	
	T & operator[](char index){
		switch(index){
		case 'x':
			return v[0];
		case 'y':
			if(N >= 2) return v[1];
		case 'z':
			if(N >= 3) return v[2];
		default:
			ERROR_MSG(_T("Argment is not 'x', 'y' or 'z'."));
			exit(0);
		};
	}
};