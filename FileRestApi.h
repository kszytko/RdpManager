#pragma once
#include "RestApi.h"
#include <fstream>


class FileRestApi : public RestApi
{
public:
	FileRestApi(std::string _filename) : filename(_filename) {
	};

private:
	std::string filename;
	std::ifstream ifs;


public:
	bool GetRequest()  override;
	nlohmann::json GetParsedResponse() const;

};