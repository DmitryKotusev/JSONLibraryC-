#pragma once
#include "pch.h"
#include "framework.h"
#include <map>
#include <string>
#include <any>
#include <ctype.h>
#include "JSONObject.h"

static class JSONUtility
{
private:
    static const char newline = '\n';
    static const char tab = '\t';
    static const char backspace = '\b';
    static const char backslash = '\\';
    static const char nullChar = '\0';
    static const char spaceChar = ' ';
    static const char quotationMark = '"';

    static bool IsSymbolEmpty(char symbol) {
        return symbol == newline
            || symbol == tab
            || symbol == spaceChar;
    }

    static bool IsCorrectSymbolForString(char symbol)
    {
        return symbol != newline
            && symbol != nullChar;
    }

    static std::string GetTabOffset(size_t tabCount)
    {
        std::string resultString = "";

        for (size_t i = 0; i < tabCount; i++)
        {
            resultString += tab;
        }

        return resultString;
    }

    static JSONObject GetJsonObject(std::string jsonString, size_t& startIndex);

    static bool GetBoolean(std::string jsonString, size_t& startIndex, bool isTrue);

    static double GetNumber(std::string jsonString, size_t& startIndex);

    static std::string GetString(std::string jsonString, size_t& startIndex);

    static void* GetNull(std::string jsonString, size_t& startIndex);

    static std::vector<std::any> GetVector(std::string jsonString, size_t& startIndex);

    static void BypassColon(std::string jsonString, size_t& startIndex);

    static void Bypass—omma(std::string jsonString, size_t& startIndex, char additionalStopSymbol);

    static std::string StringifyBool(bool boolean);

    static std::string StringifyString(std::string str);

    static std::string StringifyNumber(double number);

    static std::string StringifyNull();

    static std::string StringifyVector(std::vector<std::any> arr, size_t tabCount = 0);

    static std::string StringifyJSONObject(JSONObject obj, size_t tabCount = 0);
public:
	static std::any ParseJsonString(std::string jsonString);

    static std::string StringifyToJson(std::any input);
};

