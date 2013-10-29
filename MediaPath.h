#pragma once
#include <vector>
#include "tString.hpp"

/*
*@class MediaPath
*　複数のディレクトリにまたがってファイルを探索するときに
*　依存　TUL::tString, boost::filesystem, TUL::Error
*/

class MediaPath{
private:
	std::vector<TUL::tString> paths;
public:
	void regist(TUL::tString path);
	TUL::tString find(TUL::tString filename);
	void registFromFile(TUL::tString filepath);
};