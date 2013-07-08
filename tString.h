#pragma once
#include <string>
#include <tchar.h>
#include <iostream>

#define TSTRING_TYPE _TCHAR

/*
*@typedef tString
*　汎用的な文字の型用に。TSTRING_TYPEを必要に応じて変更
*/


typedef std::basic_string<TSTRING_TYPE> tString;

typedef std::basic_fstream<TSTRING_TYPE> tfStream;
typedef std::basic_ofstream<TSTRING_TYPE> tofStream;
typedef std::basic_ifstream<TSTRING_TYPE> tifStream;
typedef std::basic_stringstream<TSTRING_TYPE> tStringStream;
typedef std::basic_ostringstream<TSTRING_TYPE> toStringStream;
typedef std::basic_istringstream<TSTRING_TYPE> tiStringStream;
