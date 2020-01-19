#include "JSONUtility.h"

std::any JSONUtility::ParseJsonString(std::string jsonString)
{
	std::any currentNode;
	size_t i = 0;
	bool isNodeInited = false;

	for (; i < jsonString.length(); i++)
	{
		if (IsSymbolEmpty(jsonString[i]))
		{
			continue;
		}

		if (jsonString[i] == '{')
		{
			currentNode = std::any(GetJsonObject(jsonString, ++i));
			isNodeInited = true;
			break;
		}

		if (jsonString[i] == '[')
		{
			currentNode = std::any(GetVector(jsonString, ++i));
			isNodeInited = true;
			break;
		}

		if (jsonString[i] == 't')
		{
			currentNode = std::any(GetBoolean(jsonString, ++i, true));
			isNodeInited = true;
			break;
		}

		if (jsonString[i] == 'f')
		{
			currentNode = std::any(GetBoolean(jsonString, ++i, false));
			isNodeInited = true;
			break;
		}

		if (isdigit(jsonString[i]))
		{
			currentNode = std::any(GetNumber(jsonString, i));
			isNodeInited = true;
			break;
		}

		if (jsonString[i] == quotationMark)
		{
			currentNode = std::any(GetString(jsonString, ++i));
			isNodeInited = true;
			break;
		}

		if (jsonString[i] == 'n')
		{
			currentNode = std::any(GetNull(jsonString, ++i));
			isNodeInited = true;
			break;
		}

		// EXCEPTION!!!
		char exceptionMessage[80];
		sprintf_s(exceptionMessage, 80,
			"Unexpected token %c in JSON at position %d",
			jsonString[i],
			(int)i);
		throw exceptionMessage;
	}

	for (; i < jsonString.length(); i++)
	{
		if (IsSymbolEmpty(jsonString[i]))
		{
			continue;
		}

		// EXCEPTION!!!
		char exceptionMessage[80];
		sprintf_s(exceptionMessage, 80,
			"Unexpected token %c in JSON at position %d",
			jsonString[i],
			(int)i);
		throw exceptionMessage;
	}

	if (!isNodeInited)
	{
		throw "Invalid JSON, empty string";
	}
	
	return currentNode;
}

bool JSONUtility::GetBoolean(std::string jsonString, size_t& startIndex, bool isTrue)
{
	if (isTrue)
	{
		if (jsonString[startIndex] == 'r'
			&& jsonString[++startIndex] == 'u'
			&& jsonString[++startIndex] == 'e')
		{
			++startIndex;
			return true;
		}
		else
		{
			// EXCEPTION!!!
			char exceptionMessage[80];
			sprintf_s(exceptionMessage, 80,
				"Unexpected token %c in JSON at position %d",
				jsonString[startIndex],
				(int)startIndex);
			throw exceptionMessage;
		}
	}
	else
	{
		if (jsonString[startIndex] == 'a'
			&& jsonString[++startIndex] == 'l'
			&& jsonString[++startIndex] == 's'
			&& jsonString[++startIndex] == 'e')
		{
			++startIndex;
			return false;
		}
		else
		{
			// EXCEPTION!!!
			char exceptionMessage[80];
			sprintf_s(exceptionMessage, 80,
				"Unexpected token %c in JSON at position %d",
				jsonString[startIndex],
				(int)startIndex);
			throw exceptionMessage;
		}
	}

	return false;
}

double JSONUtility::GetNumber(std::string jsonString, size_t& startIndex)
{
	size_t index = startIndex;
	bool isDotFaced = false;
	for (; index < jsonString.size(); index++)
	{
		if (isdigit(jsonString[index]))
		{
			continue;
		}

		if (jsonString[index] == '.' && !isDotFaced)
		{
			++index;
			if (index >= jsonString.size())
			{
				char exceptionMessage[80];
				sprintf_s(exceptionMessage, 80,
					"Unexpected end of json input");
				throw exceptionMessage;
			}
			else if (!isdigit(jsonString[index]))
			{
				// EXCEPTION!!!
				char exceptionMessage[80];
				sprintf_s(exceptionMessage, 80,
					"Unexpected token %c in JSON at position %d",
					jsonString[index],
					(int)index);
				throw exceptionMessage;
			}
			isDotFaced = true;
			continue;
		}

		break;
	}

	std::string numderSubstring = jsonString.substr(startIndex,
		index - startIndex);

	startIndex = index;
	double number = std::stod(numderSubstring);

	return number;
}

std::string JSONUtility::GetString(std::string jsonString, size_t& startIndex)
{
	std::string resultString = "";

	size_t index = startIndex;
	for (; index < jsonString.size(); index++)
	{
		if (!IsCorrectSymbolForString(jsonString[index]))
		{
			// EXCEPTION!!!
			char exceptionMessage[80];
			sprintf_s(exceptionMessage, 80,
				"Unexpected token %c in JSON at position %d",
				jsonString[index],
				(int)index);
			throw exceptionMessage;
		}

		if (jsonString[index] == quotationMark)
		{
			startIndex = index + 1;
			break;
		}

		resultString += jsonString[index];
	}

	if (index >= jsonString.size())
	{
		// EXCEPTION!!!
		// Unexpected end of JSON
		char exceptionMessage[80];
		sprintf_s(exceptionMessage, 80,
			"Unexpected end of json input");
		throw exceptionMessage;
	}

	return resultString;
}

void* JSONUtility::GetNull(std::string jsonString, size_t& startIndex)
{
	if (jsonString[startIndex] == 'u'
		&& jsonString[++startIndex] == 'l'
		&& jsonString[++startIndex] == 'l')
	{
		++startIndex;
	}
	else
	{
		// EXCEPTION!!!
		char exceptionMessage[80];
		sprintf_s(exceptionMessage, 80,
			"Unexpected token %c in JSON at position %d",
			jsonString[startIndex],
			(int)startIndex);
		throw exceptionMessage;
	}
	return nullptr;
}

std::vector<std::any> JSONUtility::GetVector(std::string jsonString, size_t& startIndex)
{
	std::vector<std::any> resultVector;

	size_t index = startIndex;

	while (true)
	{
		std::any currentNode;
		for (; index < jsonString.length(); index++)
		{
			if (IsSymbolEmpty(jsonString[index]))
			{
				continue;
			}

			if (jsonString[index] == '{')
			{
				currentNode = std::any(GetJsonObject(jsonString, ++index));
				resultVector.push_back(currentNode);
				BypassСomma(jsonString, index, ']');
				break;
			}

			if (jsonString[index] == '[')
			{
				currentNode = std::any(GetVector(jsonString, ++index));
				resultVector.push_back(currentNode);
				BypassСomma(jsonString, index, ']');
				break;
			}

			if (jsonString[index] == 't')
			{
				currentNode = std::any(GetBoolean(jsonString, ++index, true));
				resultVector.push_back(currentNode);
				BypassСomma(jsonString, index, ']');
				break;
			}

			if (jsonString[index] == 'f')
			{
				currentNode = std::any(GetBoolean(jsonString, ++index, false));
				resultVector.push_back(currentNode);
				BypassСomma(jsonString, index, ']');
				break;
			}

			if (isdigit(jsonString[index]))
			{
				currentNode = std::any(GetNumber(jsonString, index));
				resultVector.push_back(currentNode);
				BypassСomma(jsonString, index, ']');
				break;
			}

			if (jsonString[index] == quotationMark)
			{
				currentNode = std::any(GetString(jsonString, ++index));
				resultVector.push_back(currentNode);
				BypassСomma(jsonString, index, ']');
				break;
			}

			if (jsonString[index] == 'n')
			{
				currentNode = std::any(GetNull(jsonString, ++index));
				resultVector.push_back(currentNode);
				BypassСomma(jsonString, index, ']');
				break;
			}

			if (jsonString[index] == ']')
			{
				break;
			}

			// EXCEPTION!!!
			char exceptionMessage[80];
			sprintf_s(exceptionMessage, 80,
				"Unexpected token %c in JSON at position %d",
				jsonString[index],
				(int)index);
			throw exceptionMessage;
		}

		if (index >= jsonString.size())
		{
			// EXCEPTION!!!
			// Unexpected end of JSON
			char exceptionMessage[80];
			sprintf_s(exceptionMessage, 80,
				"Unexpected end of json input");
			throw exceptionMessage;
		}

		if (jsonString[index] == ']')
		{
			break;
		}
	}

	startIndex = index + 1;

	return resultVector;
}

void JSONUtility::BypassColon(std::string jsonString, size_t& startIndex)
{
	size_t index = startIndex;

	for (; index < jsonString.length(); index++)
	{
		if (IsSymbolEmpty(jsonString[index]))
		{
			continue;
		}

		if (jsonString[index] == ':')
		{
			break;
		}
	}

	if (index >= jsonString.size())
	{
		// EXCEPTION!!!
		// Unexpected end of JSON
		char exceptionMessage[80];
		sprintf_s(exceptionMessage, 80,
			"Unexpected end of json input");
		throw exceptionMessage;
	}

	startIndex = index + 1;
}

void JSONUtility::BypassСomma(std::string jsonString, size_t& startIndex, char additionalStopSymbol)
{
	size_t index = startIndex;

	for (; index < jsonString.length(); index++)
	{
		if (IsSymbolEmpty(jsonString[index]))
		{
			continue;
		}

		if (jsonString[index] == ',')
		{
			break;
		}

		if (jsonString[index] == additionalStopSymbol)
		{
			startIndex = index;
			return;
		}
	}

	startIndex = index + 1;
}

JSONObject JSONUtility::GetJsonObject(std::string jsonString, size_t& startIndex)
{
	JSONObject resultObject;

	size_t index = startIndex;

	while (true)
	{
		for (; index < jsonString.length(); index++)
		{
			if (IsSymbolEmpty(jsonString[index]))
			{
				continue;
			}

			if (jsonString[index] == '"')
			{
				std::string key = GetString(jsonString, ++index);
				BypassColon(jsonString, index);

				size_t valueIndex = index;
				std::any value;
				for (valueIndex; valueIndex < jsonString.length(); valueIndex++)
				{
					if (IsSymbolEmpty(jsonString[valueIndex]))
					{
						continue;
					}

					if (jsonString[valueIndex] == '{')
					{
						value = std::any(GetJsonObject(jsonString, ++valueIndex));
						resultObject[key] = value;
						BypassСomma(jsonString, valueIndex, '}');
						break;
					}

					if (jsonString[valueIndex] == '[')
					{
						value = std::any(GetVector(jsonString, ++valueIndex));
						resultObject[key] = value;
						BypassСomma(jsonString, valueIndex, '}');
						break;
					}

					if (jsonString[valueIndex] == 't')
					{
						value = std::any(GetBoolean(jsonString, ++valueIndex, true));
						resultObject[key] = value;
						BypassСomma(jsonString, valueIndex, '}');
						break;
					}

					if (jsonString[valueIndex] == 'f')
					{
						value = std::any(GetBoolean(jsonString, ++valueIndex, false));
						resultObject[key] = value;
						BypassСomma(jsonString, valueIndex, '}');
						break;
					}

					if (isdigit(jsonString[valueIndex]))
					{
						value = std::any(GetNumber(jsonString, valueIndex));
						resultObject[key] = value;
						BypassСomma(jsonString, valueIndex, '}');
						break;
					}

					if (jsonString[valueIndex] == quotationMark)
					{
						value = std::any(GetString(jsonString, ++valueIndex));
						resultObject[key] = value;
						BypassСomma(jsonString, valueIndex, '}');
						break;
					}

					if (jsonString[valueIndex] == 'n')
					{
						value = std::any(GetNull(jsonString, ++valueIndex));
						resultObject[key] = value;
						BypassСomma(jsonString, valueIndex, '}');
						break;
					}

					// EXCEPTION!!!
					char exceptionMessage[80];
					sprintf_s(exceptionMessage, 80,
						"Unexpected token %c in JSON at position %d",
						jsonString[valueIndex],
						(int)valueIndex);
					throw exceptionMessage;
				}

				if (valueIndex >= jsonString.size())
				{
					// EXCEPTION!!!
					// Unexpected end of JSON
					char exceptionMessage[80];
					sprintf_s(exceptionMessage, 80,
						"Unexpected end of json input");
					throw exceptionMessage;
				}

				index = valueIndex;

				break;
			}

			if (jsonString[index] == '}')
			{
				break;
			}

			// EXCEPTION!!!
			char exceptionMessage[80];
			sprintf_s(exceptionMessage, 80,
				"Unexpected token %c in JSON at position %d",
				jsonString[index],
				(int)index);
			throw exceptionMessage;
		}

		if (index >= jsonString.size())
		{
			// EXCEPTION!!!
			// Unexpected end of JSON
			char exceptionMessage[80];
			sprintf_s(exceptionMessage, 80,
				"Unexpected end of json input");
			throw exceptionMessage;
		}

		if (jsonString[index] == '}')
		{
			break;
		}
	}

	startIndex = index + 1;

	return resultObject;
}

///////////////////////////////////////////////////////////////////////////////

std::string JSONUtility::StringifyToJson(std::any input)
{
	std::string resultString = "";
	if (bool* boolean = std::any_cast<bool>(&input))
	{
		resultString += StringifyBool(*boolean);
	}
	else if (std::string* str = std::any_cast<std::string>(&input))
	{
		resultString += StringifyString(*str);
	}
	else if (double* number = std::any_cast<double>(&input))
	{
		resultString += StringifyNumber(*number);
	}
	else if (int* number = std::any_cast<int>(&input))
	{
		resultString += StringifyNumber(*number);
	}
	else if (std::vector<std::any>* arr = std::any_cast<std::vector<std::any>>(&input))
	{
		resultString += StringifyVector(*arr);
	}
	else if (JSONObject* obj = std::any_cast<JSONObject>(&input))
	{
		resultString += StringifyJsonObject(*obj);
	}
	else if (void** nullPtr = std::any_cast<void*>(&input))
	{
		if (*nullPtr != nullptr)
		{
			throw "Incorrect input";
		}
		resultString += StringifyNull();
	}
	else
	{
		throw "Incorrect input";
	}

	return resultString;
}

std::string JSONUtility::StringifyBool(bool boolean)
{
	if (boolean)
	{
		return "true";
	}
	return "false";
}

std::string JSONUtility::StringifyString(std::string str)
{
	return "\"" + str + "\"";
}

std::string JSONUtility::StringifyNumber(double number)
{
	return std::to_string(number);
}

std::string JSONUtility::StringifyNull()
{
	return "null";
}

std::string JSONUtility::StringifyVector(std::vector<std::any> arr, size_t tabCount)
{
	std::string resultString = "";

	resultString += GetTabOffset(tabCount) + "[" + newline;

	for (size_t i = 0; i < arr.size(); i++)
	{
		std::string commaStr = ",";
		if (i == arr.size() - 1)
		{
			commaStr = "";
		}

		if (bool* boolean = std::any_cast<bool>(&(arr[i])))
		{
			resultString
				+= GetTabOffset(tabCount) + tab + StringifyBool(*boolean) + commaStr + newline;
		}
		else if (std::string* str = std::any_cast<std::string>(&(arr[i])))
		{
			resultString
				+= GetTabOffset(tabCount) + tab + StringifyString(*str) + commaStr + newline;
		}
		else if (double* number = std::any_cast<double>(&(arr[i])))
		{
			resultString
				+= GetTabOffset(tabCount) + tab + StringifyNumber(*number) + commaStr + newline;
		}
		else if (int* number = std::any_cast<int>(&(arr[i])))
		{
			resultString
				+= GetTabOffset(tabCount) + tab + StringifyNumber(*number) + commaStr + newline;
		}
		else if (std::vector<std::any>* subArr = std::any_cast<std::vector<std::any>>(&(arr[i])))
		{
			resultString
				+= StringifyVector(*subArr, tabCount + 1) + commaStr + newline;
		}
		else if (JSONObject* obj = std::any_cast<JSONObject>(&(arr[i])))
		{
			resultString
				+= StringifyJsonObject(*obj, tabCount + 1) + commaStr + newline;
		}
		else if (void** nullPtr = std::any_cast<void*>(&(arr[i])))
		{
			if (*nullPtr != nullptr)
			{
				throw "Incorrect input";
			}
			resultString
				+= GetTabOffset(tabCount) + tab + StringifyNull() + commaStr + newline;
		}
		else
		{
			throw "Incorrect input";
		}
	}

	resultString += GetTabOffset(tabCount) + "]";

	return resultString;
}

std::string JSONUtility::StringifyJsonObject(JSONObject obj, size_t tabCount)
{
	std::string resultString = "";

	resultString += GetTabOffset(tabCount) + "{" + newline;

	std::vector<std::string> keys = obj.GetKeys();

	for (size_t i = 0; i < keys.size(); i++)
	{
		std::string commaStr = ",";
		if (i == keys.size() - 1)
		{
			commaStr = "";
		}

		resultString
			+= GetTabOffset(tabCount) + tab + StringifyString(keys[i]) + ": ";

		if (bool* boolean = std::any_cast<bool>(&(obj[keys[i]])))
		{
			resultString
				+= StringifyBool(*boolean) + commaStr + newline;
		}
		else if (std::string* str = std::any_cast<std::string>(&(obj[keys[i]])))
		{
			resultString
				+= StringifyString(*str) + commaStr + newline;
		}
		else if (double* number = std::any_cast<double>(&(obj[keys[i]])))
		{
			resultString
				+= StringifyNumber(*number) + commaStr + newline;
		}
		else if (int* number = std::any_cast<int>(&(obj[keys[i]])))
		{
			resultString
				+= StringifyNumber(*number) + commaStr + newline;
		}
		else if (std::vector<std::any>* arr = std::any_cast<std::vector<std::any>>(&(obj[keys[i]])))
		{
			resultString += newline;
			resultString
				+= StringifyVector(*arr, tabCount + 1) + commaStr + newline;
		}
		else if (JSONObject* subObj = std::any_cast<JSONObject>(&(obj[keys[i]])))
		{
			resultString += newline;
			resultString
				+= StringifyJsonObject(*subObj, tabCount + 1) + commaStr + newline;
		}
		else if (void** nullPtr = std::any_cast<void*>(&(obj[keys[i]])))
		{
			if (*nullPtr != nullptr)
			{
				throw "Incorrect input";
			}
			resultString
				+= StringifyNull() + commaStr + newline;
		}
		else
		{
			throw "Incorrect input";
		}
	}

	resultString += GetTabOffset(tabCount) + "}";

	return resultString;
}
