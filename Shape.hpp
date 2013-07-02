#pragma once
#include <array>
#include <cstdarg>
#include "Error.h"
#include <string>
/*
namespace TUL{

	template<class T, int N=2>
	class Vector{
		std::array<T, N> v;
	public:
		Vector(T v1=0, T v2=0, T v3=0, T v4=0, T v5=0, T v6=0){
			v[0] = v1;
			if(N==1) return;
			v[1] = v2;
			if(N==2) return;
			v[2] = v3;
			if(N==3) return;
			v[3] = v4;
			if(N==4) return;
			v[4] = v5;
			if(N==5) return;
			v[5] = v6;
		}
		T & operator[](int index){
			return v[index];
		}
	
		T & operator[](std::string index){
			if(index == "x")
				return v[0];
			if(index == "y")
				if(N >= 2) return v[1];
			if(index == "z")
				if(N >= 3) return v[2];
			
			ERROR_MSG(_T("Argment is not 'x', 'y' or 'z'."));
			exit(0);
		}
		Vector<T, N> operator*(T rv) const{
			Vector<T, N> result;
			for(int i=0; i<N; ++i){
				result[i] = v[i] * rv;
			}
			return result;
		}
		Vector<T, N> operator+(Vector<T, N> & rv) const{
			Vector<T, N> result;
			for(int i=0; i<N; ++i){
				result[i] = v[i] + rv[i];
			}
			return result;
		}
		Vector<T, N> operator-(Vector<T, N> & rv) const{
			return (*this) + (rv * -1);
		}
	};
};


namespace TUL{
	template<class T, int N=2>
	class Point{
		std::array<T, N> p;
	public:
		Point(T v1=0, T v2=0, T v3=0, T v4=0, T v5=0, T v6=0){
			p[0] = v1;
			if(N==1) return;
			p[1] = v2;
			if(N==2) return;
			p[2] = v3;
			if(N==3) return;
			p[3] = v4;
			if(N==4) return;
			p[4] = v5;
			if(N==5) return;
			p[5] = v6;
		}
		T & operator[](int index){
			return p[index];
		}	
		T & operator[](std::string index){
			if(index == "x")
				return p[0];
			if(index == "y")
				if(N >= 2) return p[1];
			if(index == "z")
				if(N >= 3) return p[2];
			
			ERROR_MSG(_T("Argment is not 'x', 'y' or 'z'."));
			exit(0);
		}
		Vector<T, N> operator-(Point<T, N> rv) const{
			Vector<T, N> result;
			for(int i=0; i<N; ++i){
				result[i] = p[i] - rv[i];
			}
			return result;
		}

		Point<T, N> operator+(Vector<T, N> rv) const{
			Point<T, N> result;
			for(int i=0; i<N; ++i){
				result[i] = p[i] + rv[i];
			}
			return result;
		}
		Point<T, N> operator-(Vector<T, N> rv) const{
			return (*this) + (rv * -1);
		}
	};
};
*/