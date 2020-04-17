#include "pch.h"
#include "CppUnitTest.h"
#include "../Class String 2.0/Class String.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestClassString
{
	TEST_CLASS(UnitTestClassString)
	{
	public:

		TEST_METHOD(TestCreationString)
		{
			String string = "Hello, world!";
		}

		TEST_METHOD(TestCopyConstructor)
		{
			String string = "Hello, world!";
			String copy_string = string;
		}

		TEST_METHOD(TestAccessByIndex)
		{
			String string = "Hello, world!";

			Assert::AreEqual('r', string[9]);
		}

		TEST_METHOD(TestEqualOperator)
		{
			String string1 = "Hello, world!";
			String string2 = string1;
			String string3 = "World, Hello!";

			Assert::IsTrue(string1 == string2);
			Assert::IsFalse(string2 == string3);
		}
	};
}
