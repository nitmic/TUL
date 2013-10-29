#include "Error.h"
#include <Windows.h>

namespace TUL{
	void Error::printf(const TUL::tString msg, const long line, const std::string file){
		toStringStream ostr;
		ostr << __T("file = ") << to_tstring(file) << __T("line = ") << line << __T(" msg = ") << msg;

		MessageBox(NULL, ostr.str().c_str(), __T("Error"), MB_OK);
	}
};