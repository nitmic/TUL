#pragma once
#include "tString.h"
namespace TUL{
	namespace Error{
		enum{
			MAXSIZE = 256
		};
		void printf(const tString msg, const long line, const std::string file);
	};
};

#define ERROR_MSG(msg)	TUL::Error::printf(msg, __LINE__, __FILE__)

