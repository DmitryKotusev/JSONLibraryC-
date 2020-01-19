#pragma once
#include "pch.h"
#include "framework.h"
#include <map>
#include <string>
#include <any>
#include <utility>
#include <vector>

class JSONObject
{
public:
	JSONObject();
	~JSONObject();
	std::vector<std::string> GetKeys();
	std::any operator[](std::string key);

private:
	std::map<std::string, std::any> keyValuePairs;
};
