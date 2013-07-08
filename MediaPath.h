#pragma once
#include <vector>
#include "tString.h"

/*
*@class MediaPath
*　複数のディレクトリにまたがってファイルを探索するときに
*　依存　TUL::tString, boost::filesystem, TUL::Error
*/

class MediaPath{
private:
	std::vector<tString> paths;
public:
	void regist(tString path);
	tString find(tString filename);
	void registFromFile(tString filepath);
};