#include "../JSONUtility/JSONUtility.h"
#include <iostream>

int main()
{
	std::string firstJsonString
		= "true";
	std::any obj1 = JSONUtility::ParseJsonString(firstJsonString);

	std::cout << "Object 1:" << std::endl;
	std::cout << JSONUtility::StringifyToJson(obj1);
	std::cout << std::endl;

	std::string secondJsonString
		= "3.14";
	std::any obj2 = JSONUtility::ParseJsonString(secondJsonString);

	std::cout << "Object 2:" << std::endl;
	std::cout << JSONUtility::StringifyToJson(obj2);
	std::cout << std::endl;

	std::string thirdJsonString
		= "null";
	std::any obj3 = JSONUtility::ParseJsonString(thirdJsonString);

	std::cout << "Object 3:" << std::endl;
	std::cout << JSONUtility::StringifyToJson(obj3);
	std::cout << std::endl;

	std::string fourthJsonString
		= "[]";
	std::any obj4 = JSONUtility::ParseJsonString(fourthJsonString);

	std::cout << "Object 4:" << std::endl;
	std::cout << JSONUtility::StringifyToJson(obj4);
	std::cout << std::endl;

	std::string fifthJsonString
		= "{}";
	std::any obj5 = JSONUtility::ParseJsonString(fifthJsonString);

	std::cout << "Object 5:" << std::endl;
	std::cout << JSONUtility::StringifyToJson(obj5);
	std::cout << std::endl;

	std::string sixthJsonString
		= "\"Hello, world!\"";
	std::any obj6 = JSONUtility::ParseJsonString(sixthJsonString);

	std::cout << "Object 6:" << std::endl;
	std::cout << JSONUtility::StringifyToJson(obj6);
	std::cout << std::endl;

	std::string seventhJsonString
		= std::string("{ \"number\":3.67,\"boolean\" : true,\"null\" : null,\"string\"") +
		" : \"Hello, world!\",\"object\" : {\"subkey\":1},\"array\" : [true,0.1,null] }";
	std::any obj7 = JSONUtility::ParseJsonString(seventhJsonString);

	std::cout << "Object 7:" << std::endl;
	std::cout << JSONUtility::StringifyToJson(obj7);
	std::cout << std::endl;

	std::string eightthJsonString
		= "[\"sdzfsfs\", 1, true]";
	std::any obj8 = JSONUtility::ParseJsonString(eightthJsonString);

	std::cout << "Object 8:" << std::endl;
	std::cout << JSONUtility::StringifyToJson(obj8);
	std::cout << std::endl;
}