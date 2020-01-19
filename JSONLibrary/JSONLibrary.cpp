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

		TEST_METHOD(InitWithNull1)
		{
			std::any parseResult = JSONUtility::ParseJsonString("		null ");
			if (void** nullPtr = std::any_cast<void *>(&parseResult))
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

		//TEST_METHOD(InitWithArray)
		//{
		//}

		//TEST_METHOD(InitWithObject)
		//{
		//}
	};
}
