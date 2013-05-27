#include "MediaPath.h"
#include "Error.h"
#include <boost\filesystem.hpp>

void MediaPath::regist(tString path){
	paths.push_back(path);
}

tString MediaPath::find(tString filename){
	for(auto it=paths.begin();it!=paths.end();it++){
		boost::system::error_code error;
		const auto path = boost::filesystem::absolute(filename, *it);
		const bool result = boost::filesystem::exists(path, error);
		if(result && !error){
			return path.c_str();
		}
	}
	ERROR_MSG(_T("MediaPath::find : file is not found"));
	exit(1);
}

void MediaPath::registFromFile(tString filepath){
	tifStream ifs(filepath);
	tString str;
	if(!ifs){
		ERROR_MSG(_T("MediaPath::registFromFile : file is not found"));
		return;
	}
	while(!ifs.eof()){
		std::getline(ifs,str);
		paths.push_back(str);
	}
}