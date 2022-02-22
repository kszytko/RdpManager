#pragma once
#include <string>
#include"json.hpp"

using namespace nlohmann;

class WorkPackage {
public:
	WorkPackage(const json&);

protected:
	size_t getHrefID(const json&) const;
	std::string getString(const json&) const;
	size_t getSizeT(const json&) const;

public:
	virtual void print() const;

public:	
	static bool isType(const json& object, const std::string& type);

public:
	size_t	id;
	std::string type;
	std::string subject;
	std::string description;
	std::string startDate;
	std::string dueDate;
	std::string estimatedTime;
	std::string createdAt;
	std::string updatedAt;

	std::string priority;
	std::string project;
	std::string status;
	std::string parentName;
	size_t parentID;

	std::string loginName = "";
	std::string lanIP = "";
	std::string wanIP = "";
	size_t teamViewerID = 0;
	size_t machineNumber = 0;
};
