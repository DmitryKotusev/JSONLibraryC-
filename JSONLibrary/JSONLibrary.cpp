#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestingJSONLibrary
{
	TEST_CLASS(UnitTestJSONStringInit)
	{
	public:
		TEST_METHOD(InitWithSimpleString1)
		{
			std::any parseResult = JSONUtility::ParseJsonString("\"Hello, world!\"");
			if (std::string* str = std::any_cast<std::string>(&parseResult))
			{
				Assert::AreEqual("Hello, world!", str->c_str());
			}
			else
			{
				Assert::Fail(L"Parse error");
			}
		}

		TEST_METHOD(InitWithSimpleString2)
		{
			std::any parseResult = JSONUtility::ParseJsonString("\"Hello, world!\"");
			if (std::string* str = std::any_cast<std::string>(&parseResult))
			{
				Assert::AreNotEqual("Hello, WOrld!", str->c_str());
			}
			else
			{
				Assert::Fail(L"Parse error");
			}
		}

		TEST_METHOD(InitWithSimpleBoolean1)
		{
			std::any parseResult = JSONUtility::ParseJsonString("	true ");
			if (bool* boolean = std::any_cast<bool>(&parseResult))
			{
				Assert::AreEqual(true, *boolean);
			}
			else
			{
				Assert::Fail(L"Parse error");
			}
		}

		TEST_METHOD(InitWithSimpleBoolean2)
		{
			std::any parseResult = JSONUtility::ParseJsonString("false ");
			if (bool* boolean = std::any_cast<bool>(&parseResult))
			{
				Assert::AreEqual(false, *boolean);
			}
			else
			{
				Assert::Fail(L"Parse error");
			}
		}

		TEST_METHOD(InitWithSimpleBoolean3)
		{
			try
			{
				std::any parseResult = JSONUtility::ParseJsonString("fAlse ");
				Assert::Fail(L"Invalid JSON string parsed successfully");
			}
			catch (const char* msg)
			{
				Assert::AreEqual("Unexpected token A in JSON at position 1", msg);
			}
		}

		TEST_METHOD(InitWithSimpleNumber1)
		{
			std::any parseResult = JSONUtility::ParseJsonString("3.14 ");
			if (double* number = std::any_cast<double>(&parseResult))
			{
				Assert::AreEqual(3.14, *number, 0.001);
			}
			else
			{
				Assert::Fail(L"Parse error");
			}
		}

		TEST_METHOD(InitWithSimpleNumber2)
		{
			std::any parseResult = JSONUtility::ParseJsonString("	 910.296 ");
			if (double* number = std::any_cast<double>(&parseResult))
			{
				Assert::AreEqual(910.296, *number, 0.001);
			}
			else
			{
				Assert::Fail(L"Parse error");
			}
		}

		TEST_METHOD(InitWithSimpleNumber3)
		{
			std::any parseResult = JSONUtility::ParseJsonString("		101 ");
			if (double* number = std::any_cast<double>(&parseResult))
			{
				Assert::AreEqual(101, *number, 0.001);
			}
			else
			{
				Assert::Fail(L"Parse error");
			}
		}

		TEST_METHOD(InitWithSimpleNumber4)
		{
			try
			{
				std::any parseResult = JSONUtility::ParseJsonString("  .456 ");
				Assert::Fail(L"Invalid JSON string parsed successfully");
			}
			catch (const char* msg)
			{
				Assert::AreEqual("Unexpected token . in JSON at position 2", msg);
			}
		}

		TEST_METHOD(InitWithSimpleNumber5)
		{
			std::any parseResult = JSONUtility::ParseJsonString("3.14");
			if (double* number = std::any_cast<double>(&parseResult))
			{
				Assert::AreEqual(3.14, *number, 0.001);
			}
			else
			{
				Assert::Fail(L"Parse error");
			}
		}

		TEST_METHOD(InitWithNull1)
		{
			std::any parseResult = JSONUtility::ParseJsonString("		null ");
			if (void** nullPtr = std::any_cast<void*>(&parseResult))
			{
				Assert::IsNull<void>(*nullPtr);
			}
			else
			{
				Assert::Fail(L"Parse error");
			}
		}

		TEST_METHOD(InitWithNull2)
		{
			try
			{
				std::any parseResult = JSONUtility::ParseJsonString("		nullable ");
				Assert::Fail(L"Invalid JSON string parsed successfully");
			}
			catch (const char* msg)
			{
				Assert::AreEqual("Unexpected token a in JSON at position 6", msg);
			}
		}
	};

	TEST_CLASS(UnitTestJSONStringInitForArray)
	{
	public:

		TEST_METHOD(CheckEmptyArray)
		{
			std::any parseResult = JSONUtility::ParseJsonString("[]");
			std::vector<std::any>* arr;
			if (!(arr = std::any_cast<std::vector<std::any>>(&parseResult)))
			{
				Assert::Fail(L"Parse error");
			}

			if (arr->size() > 0) {
				Assert::Fail(L"Array not empty");
			}
		}
		TEST_METHOD(CheckStringValue)
		{
			std::any parseResult = JSONUtility::ParseJsonString("[\n\"sdzfsfs\",  1 , true\n  ]	");
			std::vector<std::any>* arr;
			if (!(arr = std::any_cast<std::vector<std::any>>(&parseResult)))
			{
				Assert::Fail(L"Parse error");
			}

			if (arr->size() < 3) {
				Assert::Fail(L"Array too small");
				return;
			}
			if (std::string* str = std::any_cast<std::string>(&((*arr)[0])))
			{
				Assert::AreEqual("sdzfsfs", str->c_str());
			}
			else
			{
				Assert::Fail(L"Parse error");
			}
		}

		TEST_METHOD(CheckNumberValue)
		{
			std::any parseResult = JSONUtility::ParseJsonString("[\n\"sdzfsfs\",  1 , true\n  ]	");
			std::vector<std::any>* arr;
			if (!(arr = std::any_cast<std::vector<std::any>>(&parseResult)))
			{
				Assert::Fail(L"Parse error");
			}

			if (arr->size() < 3) {
				Assert::Fail(L"Array too small");
				return;
			}
			if (double* number = std::any_cast<double>(&((*arr)[1])))
			{
				Assert::AreEqual(1, *number, 0.001);
			}
			else
			{
				Assert::Fail(L"Parse error");
			}
		}

		TEST_METHOD(CheckBooleanValue)
		{
			std::any parseResult = JSONUtility::ParseJsonString("[\n\"sdzfsfs\",  1 , true\n  ]	");
			std::vector<std::any>* arr;
			if (!(arr = std::any_cast<std::vector<std::any>>(&parseResult)))
			{
				Assert::Fail(L"Parse error");
			}

			if (arr->size() < 3) {
				Assert::Fail(L"Array too small");
				return;
			}
			if (bool* boolean = std::any_cast<bool>(&((*arr)[2])))
			{
				Assert::AreEqual(true, *boolean);
			}
			else
			{
				Assert::Fail(L"Parse error");
			}
		}

		TEST_METHOD(CheckNullValue)
		{
			std::any parseResult = JSONUtility::ParseJsonString("[\n\"sdzfsfs\",  1 , true\n ,null ]	");
			std::vector<std::any>* arr;
			if (!(arr = std::any_cast<std::vector<std::any>>(&parseResult)))
			{
				Assert::Fail(L"Parse error");
			}

			if (arr->size() < 4) {
				Assert::Fail(L"Array too small");
				return;
			}
			if (void** nullPtr = std::any_cast<void*>(&((*arr)[3])))
			{
				Assert::IsNull(*nullPtr);
			}
			else
			{
				Assert::Fail(L"Parse error");
			}
		}

		TEST_METHOD(CheckObjectValue)
		{
			std::any parseResult = JSONUtility::ParseJsonString("[\n\"sdzfsfs\",  1 , true\n ,null , {\"key\"  \n: false} ]	");
			std::vector<std::any>* arr;
			if (!(arr = std::any_cast<std::vector<std::any>>(&parseResult)))
			{
				Assert::Fail(L"Parse error");
			}

			if (arr->size() < 5) {
				Assert::Fail(L"Array too small");
				return;
			}
			if (JSONObject* subObject = std::any_cast<JSONObject>(&((*arr)[4])))
			{
				if (bool* boolean = std::any_cast<bool>(&((*subObject)["key"])))
				{
					Assert::IsFalse(*boolean);
				}
				else
				{
					Assert::Fail(L"Parse error");
				}
			}
			else
			{
				Assert::Fail(L"Parse error");
			}
		}

		TEST_METHOD(CheckInvalidArray1)
		{
			try
			{
				std::any parseResult = JSONUtility::ParseJsonString("[\n\"sdzfsfs\",  1, , true\n  ]	");
				Assert::Fail(L"Invalid JSON string parsed successfully");
			}
			catch (const char* msg)
			{
				Assert::AreEqual("Unexpected token , in JSON at position 17", msg);
			}
		}

		TEST_METHOD(CheckInvalidArray2)
		{
			try
			{
				std::any parseResult = JSONUtility::ParseJsonString("[\n\"sdzfsfs\",  1,$ , true\n  ]	");
				Assert::Fail(L"Invalid JSON string parsed successfully");
			}
			catch (const char* msg)
			{
				Assert::AreEqual("Unexpected token $ in JSON at position 16", msg);
			}
		}

		TEST_METHOD(CheckInvalidArray3)
		{
			try
			{
				std::any parseResult = JSONUtility::ParseJsonString("[\n\"sdzfsfs\",  1, true\n  	");
				Assert::Fail(L"Invalid JSON string parsed successfully");
			}
			catch (const char* msg)
			{
				Assert::AreEqual("Unexpected end of json input", msg);
			}
		}
	};

	TEST_CLASS(UnitTestJSONStringInitComplexStructures)
	{
	private:
		const char* jsonString
			= "{\"number\": 3.67 , \"boolean\"	\n: true,\"null\":null,\"string\":\"Hello, world!\",	\n\"object\":{\"subkey\":1},\"array\":[true,0.1,null]  \n}";
	public:

		TEST_METHOD(CheckEmptyObject)
		{
			std::any parseResult = JSONUtility::ParseJsonString("{}");
			JSONObject* jsonObject;
			if (!(jsonObject = std::any_cast<JSONObject>(&parseResult)))
			{
				Assert::Fail(L"Parse error");
			}

			std::vector<std::string> parsedKeys = jsonObject->GetKeys();

			Assert::IsTrue(parsedKeys.size() == 0, L"Object not empty");
		}
		TEST_METHOD(CheckKeys)
		{
			std::any parseResult = JSONUtility::ParseJsonString(jsonString);
			JSONObject* jsonObject;
			if (!(jsonObject = std::any_cast<JSONObject>(&parseResult)))
			{
				Assert::Fail(L"Parse error");
			}

			std::vector<std::string> originKeys{
				"number",
				"boolean",
				"null",
				"string",
				"object",
				"array"
			};

			std::sort(originKeys.begin(), originKeys.end());

			std::vector<std::string> parsedKeys = jsonObject->GetKeys();

			std::function< bool(const std::string&, const std::string&) > comparator = [](const std::string& left, const std::string& right) {
				return std::equal(left.begin(), left.end(), right.begin(), [](const char& l, const char& r) {
					return (::toupper(l) == ::toupper(r));
					});
			};

			bool result = std::equal(originKeys.begin(), originKeys.end(), parsedKeys.begin(), comparator);

			Assert::IsTrue(result);
		}

		TEST_METHOD(CheckInvalidObject1)
		{
			try
			{
				std::any parseResult
					= JSONUtility::ParseJsonString("{\"number\": 3.67 , \"boolean\"	\n: true,");
				Assert::Fail(L"Invalid JSON string parsed successfully");
			}
			catch (const char* msg)
			{
				Assert::AreEqual("Unexpected end of json input", msg);
			}
		}

		TEST_METHOD(CheckInvalidObject2)
		{
			try
			{
				std::any parseResult
					= JSONUtility::ParseJsonString("{\"number\": 3.67 , \"boolean\"	\n: true, 56.7");
				Assert::Fail(L"Invalid JSON string parsed successfully");
			}
			catch (const char* msg)
			{
				Assert::AreEqual("Unexpected token 5 in JSON at position 37", msg);
			}
		}

		TEST_METHOD(CheckNumberKey)
		{
			std::any parseResult = JSONUtility::ParseJsonString(jsonString);
			JSONObject* jsonObject;
			if (!(jsonObject = std::any_cast<JSONObject>(&parseResult)))
			{
				Assert::Fail(L"Parse error");
			}

			if (double* number = std::any_cast<double>(&((*jsonObject)["number"])))
			{
				Assert::AreEqual(3.67, *number, 0.001);
			}
			else
			{
				Assert::Fail(L"Parse error");
			}
		}

		TEST_METHOD(CheckArrayKey)
		{
			std::any parseResult = JSONUtility::ParseJsonString(jsonString);
			JSONObject* jsonObject;
			if (!(jsonObject = std::any_cast<JSONObject>(&parseResult)))
			{
				Assert::Fail(L"Parse error");
			}

			if (std::vector<std::any>* arr = std::any_cast<std::vector<std::any>>(&((*jsonObject)["array"])))
			{
				if (arr->size() < 3) {
					Assert::Fail(L"Array too small");
				}

				if (bool* boolean = std::any_cast<bool>(&((*arr)[0])))
				{
					Assert::IsTrue(*boolean);
				}
				else
				{
					Assert::Fail(L"Parse error");
				}
			}
			else
			{
				Assert::Fail(L"Parse error");
			}
		}

		TEST_METHOD(CheckObjectKey)
		{
			std::any parseResult = JSONUtility::ParseJsonString(jsonString);
			JSONObject* jsonObject;
			if (!(jsonObject = std::any_cast<JSONObject>(&parseResult)))
			{
				Assert::Fail(L"Parse error");
			}

			if (JSONObject* subObject = std::any_cast<JSONObject>(&((*jsonObject)["object"])))
			{
				if (double* number = std::any_cast<double>(&((*subObject)["subkey"])))
				{
					Assert::AreEqual(1, *number, 0.001);
				}
				else
				{
					Assert::Fail(L"Parse error");
				}
			}
			else
			{
				Assert::Fail(L"Parse error");
			}
		}
	};
}
