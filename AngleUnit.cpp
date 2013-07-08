#include "AngleUnit.h"

namespace TUL{
	Degree::operator Radian(){
		return Radian(deg * PI / 180);
	}
	Degree Degree::normalize() const {
		int code = deg<0 ? -1 : 1;
		double norm;
		for(int i=0;;i++){
			norm = deg - code*i*360;
			if(0 <= norm && norm < 360) break;
		}
		return Degree(norm);
	}

	Radian::operator Degree(){
		return Degree(rad * 180 / PI);
	}
	Radian Radian::normalize() const {
		int code = rad<0 ? -1 : 1;
		double norm;
		for(int i=0;;i++){
			norm = rad - code*i*2*PI;
			if(0 <= norm && norm < 2*PI) break;
		}
		return Radian(norm);
	}
};