#pragma once
#include <vector>
#include "tString.hpp"

/*
*@class MediaPath
*�@�����̃f�B���N�g���ɂ܂������ăt�@�C����T������Ƃ���
*�@�ˑ��@TUL::tString, boost::filesystem, TUL::Error
*/

class MediaPath{
private:
	std::vector<TUL::tString> paths;
public:
	void regist(TUL::tString path);
	TUL::tString find(TUL::tString filename);
	void registFromFile(TUL::tString filepath);
};