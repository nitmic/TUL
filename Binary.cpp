/*#include "Binary.h"
#include "Error.h"
Binary::Binary(const int v){
	if(v!=0 && v!=1) ERROR_MSG(_T("Argment is not 0 or 1."));
	m_v = v;
};

void Binary::reverse(){
	m_v = ~(*this);
}

int Binary::operator~(){
	return m_v==0 ? 1 : 0;
}

Binary::operator int(){
	return int(m_v);
}*/