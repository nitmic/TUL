#pragma once
#include "tString.h"

/*
*@function ERROR_MSG
*�@Error���b�Z�[�W�\���BDebug���p�Bassert�ł�������
*�@�ˑ��@TUL::tString, Windows.h
*/

namespace TUL{
	namespace Error{
		enum{
			MAXSIZE = 256
		};
		void printf(const tString msg, const long line, const std::string file);
	};
};

#define ERROR_MSG(msg)	TUL::Error::printf(msg, __LINE__, __FILE__)

