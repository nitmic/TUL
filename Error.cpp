#include "Error.h"
#include <Windows.h>
#include <sstream>

namespace TUL{
	void Error::printf(const tString msg, const long line, const std::string file){
		toStringStream ostr;
		const tString tFile(file.begin(), file.end());
		ostr << __T("file = ") << tFile << __T("line = ") << line << __T(" msg = ") << msg;

		MessageBox(NULL, ostr.str().c_str(), __T("Error"), MB_OK);
	}
};