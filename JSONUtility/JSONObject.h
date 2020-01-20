#pragma once
#include "pch.h"
#include "framework.h"
#include <map>
#include <string>
#include <any>
#include <utility>
#include <vector>
#include <istream>
#include <ostream>
#include <unordered_map>

class JSONObject
{
public:
	JSONObject();
	JSONObject(std::map<std::string, std::any> keyValuePairs, bool isFast = false);
	~JSONObject();
	std::vector<std::string> GetKeys();
	std::any& operator[](std::string key);
	friend std::istream& operator>>(std::istream& in, JSONObject& obj);
	friend std::ostream& operator<<(std::ostream& os, const JSONObject& obj);
	void ChangeOrganizationType(bool isFast);

private:
	bool isFast = false;
	std::map<std::string, std::any> keyValuePairsSlow;
	std::unordered_map<std::string, std::any> keyValuePairsFast;
};
