#include "FileRestApi.h"

bool FileRestApi::GetRequest(){
	return true;
};

nlohmann::json FileRestApi::GetParsedResponse() const {
	std::ifstream iff(filename, std::ios::binary);

	return nlohmann::json::parse(iff);

};