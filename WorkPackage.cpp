#pragma once
#include <string>
#include <iostream>
#include "WorkPackage.h"
#include"json.hpp"

using namespace nlohmann;

WorkPackage::WorkPackage(const json& object) {
	if (object.at("_type") == "WorkPackage") {
		id = getSizeT(object.at("id"));
		subject = getString(object.at("subject"));
		description = getString(object.at("description").at("raw"));
		startDate = getString(object.at("startDate"));
		dueDate = getString(object.at("dueDate"));
		estimatedTime = getString(object.at("estimatedTime"));
		createdAt = getString(object.at("createdAt"));
		updatedAt = getString(object.at("updatedAt"));
		type = getString(object.at("_links").at("type").at("title"));
		priority = getString(object.at("_links").at("priority").at("title"));
		project = getString(object.at("_links").at("project").at("title"));
		status = getString(object.at("_links").at("status").at("title"));
		parentName = getString(object.at("_links").at("parent").at("title"));
		parentID = getHrefID(object.at("_links").at("parent").at("href"));

		try {
			loginName = getString(object.at("customField11"));
			lanIP = getString(object.at("customField12"));
			wanIP = getString(object.at("customField13"));
			teamViewerID = getSizeT(object.at("customField14"));
			machineNumber = getSizeT(object.at("customField15"));
		}
		catch (std::exception& e) {
			
		}

	}
}

size_t WorkPackage::getHrefID(const json& el) const {
	std::string href = getString(el);
	if (href.empty())
		return 0;
	return std::stoi(href.substr(href.find_last_of('/') + 1));
}

std::string WorkPackage::getString(const json& el) const {
	if (!el.is_null() && el.type() == json::value_t::string)
		return el.get<std::string>();
	return std::string();
}

size_t WorkPackage::getSizeT(const json& el) const {
	if (!el.is_null() && el.type() == json::value_t::number_unsigned)
		return el.get<size_t>();
	return 0;
}

void WorkPackage::print() const {
	std::cout << type << "\n"
		<< " id           :  " << id << "\n"
		<< " subject      :  " << subject << "\n"
		<< " description  :  " << description << "\n"
		<< " startDate    :  " << startDate << "\n"
		<< " dueDate      :  " << dueDate << "\n"
		<< " estimatedTime:  " << estimatedTime << "\n"
		<< " cretedAt     :  " << createdAt << "\n"
		<< " updatedAt    :  " << updatedAt << "\n"
		<< " priority     :  " << priority << "\n"
		<< " project      :  " << project << "\n"
		<< " startDate    :  " << startDate << "\n"
		<< " parentID     :  " << parentID << "\n"
		<< " parentName   :  " << parentName << "\n";
}

bool WorkPackage::isType(const json& object, const std::string& type) {
	try {
		auto& objectType = object.at("_links").at("type").at("title");
		if (!objectType.is_null() && objectType.type() == json::value_t::string)
			return objectType.get<std::string>() == type;
	}
	catch (std::out_of_range& e) {
		std::cerr << e.what();
	}
	return false;
}
