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

class JSONObject
{
public:
	JSONObject();
	JSONObject(std::map<std::string, std::any> keyValuePairs);
	~JSONObject();
	std::vector<std::string> GetKeys();
	std::any& operator[](std::string key);
	friend std::istream& operator>>(std::istream& in, JSONObject& jo);

private:
	std::map<std::string, std::any> keyValuePairs;
};
