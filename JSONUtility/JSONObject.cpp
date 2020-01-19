#include "JSONObject.h"

JSONObject::JSONObject()
{
	// keyValuePairs = std::map<std::string, std::any>();
}

JSONObject::~JSONObject()
{
	//std::vector<std::string> keys = GetKeys();

	//for (size_t i = 0; i < keys.size(); i++)
	//{
	//	if (std::string* str = std::any_cast<std::string>(&(keyValuePairs[keys[i]]))) {

	//	}
	//}
}

std::vector<std::string> JSONObject::GetKeys()
{
	std::vector<std::string> keys;
	for (std::map<std::string, std::any>::iterator it = keyValuePairs.begin();
		it != keyValuePairs.end(); ++it) {
		keys.push_back(it->first);
	}

	return keys;
}

std::any& JSONObject::operator[](std::string key)
{
	return keyValuePairs[key];
}
