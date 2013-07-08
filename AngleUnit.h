#pragma once

namespace TUL{
	static double PI = 3.141592;
	class Radian;

	class Degree{
	public:
		Degree(double deg):deg(deg){};
		operator Radian();
		Degree normalize() const;
		double getRaw() const {return deg;};
		Degree operator+(Degree & other) const {
			return Degree(deg + other.getRaw());
		}
		Degree operator-(Degree & other) const {
			return Degree(deg - other.getRaw());
		}
		Degree operator*(double other) const {
			return Degree(deg * other);
		}
		Degree operator/(double other) const {
			return Degree(deg / other);
		}
		Degree& operator+=(Degree & other){
			deg += other.getRaw();
			return *this;
		}
		Degree& operator-=(Degree & other){
			deg -= other.getRaw();
			return *this;
		}
		Degree& operator*=(double other){
			deg *= other;
			return *this;
		}
		Degree& operator/=(double other){
			deg /= other;
			return *this;
		}
	private:
		double deg;
	};


	class Radian{
	public:
		Radian(double rad):rad(rad){};
		operator Degree();
		Radian normalize() const;
		double getRaw() const {return rad;};
		Radian operator+(Radian & other) const {
			return Radian(rad + other.getRaw());
		}
		Radian operator-(Radian & other) const {
			return Radian(rad - other.getRaw());
		}
		Radian operator*(double other) const {
			return Radian(rad * other);
		}
		Radian operator/(double other) const {
			return Radian(rad / other);
		}
		Radian& operator+=(Radian & other){
			rad += other.getRaw();
			return *this;
		}
		Radian& operator-=(Radian & other){
			rad -= other.getRaw();
			return *this;
		}
		Radian& operator*=(double other){
			rad *= other;
			return *this;
		}
		Radian& operator/=(double other){
			rad /= other;
			return *this;
		}
		
	private:
		double rad;

	};
};