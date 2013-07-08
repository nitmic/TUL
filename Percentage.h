#pragma once

/*
*@class Percent
*@o—ˆ‘¹‚È‚¢
*/

class Percent{
public:
	Percent(double p=0) : m_Percent(p){};
	Percent operator+=(const Percent & p){
		return m_Percent += p.m_Percent;
	}
	Percent operator-=(const Percent & p){
		return m_Percent -= p.m_Percent;
	}
	Percent operator*=(const double p){
		return m_Percent *= p;
	}
	bool operator<(const Percent & p){
		return compare(p)==-1;
	}
	bool operator<=(const Percent & p){
		return compare(p)<=0;
	}
	bool operator>(const Percent & p){
		return compare(p)==1;
	}
	bool operator>=(const Percent & p){
		return compare(p)>=0;
	}
	bool operator==(const Percent & p){
		return compare(p)==0;
	}
private:
	int compare(const Percent & p){
		if(p.m_Percent < m_Percent){
			return 1;
		}else if(p.m_Percent > m_Percent){
			return -1;
		}else{
			return 0;
		}
	}
	double m_Percent;
};
