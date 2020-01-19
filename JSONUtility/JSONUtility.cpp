#include "JSONUtility.h"

std::any JSONUtility::ParseJsonString(std::string jsonString)
{
	std::any currentNode;
	size_t i = 0;
	for (; i < jsonString.length(); i++)
	{
		if (IsSymbolEmpty(jsonString[i]))
		{
			continue;
		}

		if (jsonString[i] == '{')
		{
			currentNode = std::any(GetJsonObject(jsonString, ++i));
			break;
		}

		if (jsonString[i] == '[')
		{
			currentNode = std::any(GetVector(jsonString, ++i));
			break;
		}

		if (jsonString[i] == 't')
		{
			currentNode = std::any(GetBoolean(jsonString, ++i, true));
			break;
		}

		if (jsonString[i] == 'f')
		{
			currentNode = std::any(GetBoolean(jsonString, ++i, false));
			break;
		}

		if (isdigit(jsonString[i]))
		{
			currentNode = std::any(GetNumber(jsonString, i));
			break;
		}

		if (jsonString[i] == quotationMark)
		{
			currentNode = std::any(GetString(jsonString, ++i));
			break;
		}

		if (jsonString[i] == 'n')
		{
			currentNode = std::any(GetNull(jsonString, ++i));
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

	if (index >= jsonString.size())
	{
		index = jsonString.size() - 1;
	}

	std::string numderSubstring = jsonString.substr(startIndex,
		index - startIndex + 1);

	startIndex = index + 1;
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
				break;
			}

			if (jsonString[index] == '[')
			{
				currentNode = std::any(GetVector(jsonString, ++index));
				break;
			}

			if (jsonString[index] == 't')
			{
				currentNode = std::any(GetBoolean(jsonString, ++index, true));
				break;
			}

			if (jsonString[index] == 'f')
			{
				currentNode = std::any(GetBoolean(jsonString, ++index, false));
				break;
			}

			if (isdigit(jsonString[index]))
			{
				currentNode = std::any(GetNumber(jsonString, index));
				break;
			}

			if (jsonString[index] == quotationMark)
			{
				currentNode = std::any(GetString(jsonString, ++index));
				break;
			}

			if (jsonString[index] == 'n')
			{
				currentNode = std::any(GetNull(jsonString, ++index));
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

		resultVector.push_back(currentNode);
		BypassСomma(jsonString, index, ']');

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

	return std::vector<std::any>();
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
						break;
					}

					if (jsonString[valueIndex] == '[')
					{
						value = std::any(GetVector(jsonString, ++valueIndex));
						break;
					}

					if (jsonString[valueIndex] == 't')
					{
						value = std::any(GetBoolean(jsonString, ++valueIndex, true));
						break;
					}

					if (jsonString[valueIndex] == 'f')
					{
						value = std::any(GetBoolean(jsonString, ++valueIndex, false));
						break;
					}

					if (isdigit(jsonString[valueIndex]))
					{
						value = std::any(GetNumber(jsonString, valueIndex));
						break;
					}

					if (jsonString[valueIndex] == quotationMark)
					{
						value = std::any(GetString(jsonString, ++valueIndex));
						break;
					}

					if (jsonString[valueIndex] == 'n')
					{
						value = std::any(GetNull(jsonString, ++valueIndex));
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

				resultObject[key] = value;

				BypassСomma(jsonString, valueIndex, '}');

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
