#include "JSONObject.h"
#include "JSONUtility.h"

JSONObject::JSONObject()
{
}

JSONObject::JSONObject(std::map<std::string, std::any> keyValuePairs, bool isFast)
{
	this->isFast = isFast;
	if (this->isFast)
	{
		for (std::map<std::string, std::any>::iterator it = keyValuePairs.begin();
			it != keyValuePairs.end(); ++it) {
			this->keyValuePairsFast.insert(*it);
		}
	}
	else
	{
		this->keyValuePairsSlow = keyValuePairs;
	}
}

JSONObject::~JSONObject()
{
}


std::vector<std::string> JSONObject::GetKeys()
{
	std::vector<std::string> keys;
	for (std::map<std::string, std::any>::iterator it = keyValuePairsSlow.begin();
		it != keyValuePairsSlow.end(); ++it) {
		keys.push_back(it->first);
	}

	return keys;
}

std::any& JSONObject::operator[](std::string key)
{
	if (isFast)
	{
		return keyValuePairsFast[key];
	}
	return keyValuePairsSlow[key];
}

void JSONObject::ChangeOrganizationType(bool isFast)
{
	if (this->isFast == isFast)
	{
		return;
	}

	if (isFast)
	{
		for (std::map<std::string, std::any>::iterator it = this->keyValuePairsSlow.begin();
			it != this->keyValuePairsSlow.end(); ++it) {
			this->keyValuePairsFast.insert(*it);
		}
	}
	else
	{
		for (std::unordered_map<std::string, std::any>::iterator it = this->keyValuePairsFast.begin();
			it != this->keyValuePairsFast.end(); ++it) {
			this->keyValuePairsSlow.insert(*it);
		}
	}
}

std::istream& operator>>(std::istream& in, JSONObject& obj)
{
	std::string jsonString = "";
	std::getline(in, jsonString);
	std::any parseResult = JSONUtility::ParseJsonString(jsonString);
	if (JSONObject* jsonObject = std::any_cast<JSONObject>(&parseResult))
	{
		obj.keyValuePairsSlow = jsonObject->keyValuePairsSlow;
	}
	return in;
}

std::ostream& operator<<(std::ostream& os, const JSONObject& obj)
{
	std::string jsonString = JSONUtility::StringifyToJson(obj);

	os << jsonString;

	return os;
}
