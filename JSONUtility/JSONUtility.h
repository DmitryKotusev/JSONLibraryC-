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

    static JSONObject GetJsonObject(std::string jsonString, size_t& startIndex);

    static bool GetBoolean(std::string jsonString, size_t& startIndex, bool isTrue);

    static double GetNumber(std::string jsonString, size_t& startIndex);

    static std::string GetString(std::string jsonString, size_t& startIndex);

    static void* GetNull(std::string jsonString, size_t& startIndex);

    static std::vector<std::any> GetVector(std::string jsonString, size_t& startIndex);

    static void BypassColon(std::string jsonString, size_t& startIndex);

    static void Bypass—omma(std::string jsonString, size_t& startIndex, char additionalStopSymbol);
public:
	static std::any ParseJsonString(std::string jsonString);
};

