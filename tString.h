#pragma once
#include <string>
#include <tchar.h>
#include <iostream>

#define DEFAULT_TSTRING_TYPE _TCHAR

typedef std::basic_string<DEFAULT_TSTRING_TYPE> tString;

typedef std::basic_fstream<DEFAULT_TSTRING_TYPE> tfStream;
typedef std::basic_ofstream<DEFAULT_TSTRING_TYPE> tofStream;
typedef std::basic_ifstream<DEFAULT_TSTRING_TYPE> tifStream;
typedef std::basic_stringstream<DEFAULT_TSTRING_TYPE> tStringStream;
typedef std::basic_ostringstream<DEFAULT_TSTRING_TYPE> toStringStream;
typedef std::basic_istringstream<DEFAULT_TSTRING_TYPE> tiStringStream;
