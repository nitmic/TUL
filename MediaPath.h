#pragma once
#include <vector>
#include "tString.h"

/*
*@class MediaPath
*�@�����̃f�B���N�g���ɂ܂������ăt�@�C����T������Ƃ���
*�@�ˑ��@TUL::tString, boost::filesystem, TUL::Error
*/

class MediaPath{
private:
	std::vector<tString> paths;
public:
	void regist(tString path);
	tString find(tString filename);
	void registFromFile(tString filepath);
};