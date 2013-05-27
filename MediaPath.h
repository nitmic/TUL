#pragma once
#include <vector>
#include "tString.h"

class MediaPath{
private:
	std::vector<tString> paths;
public:
	void regist(tString path);
	tString find(tString filename);
	void registFromFile(tString filepath);
};