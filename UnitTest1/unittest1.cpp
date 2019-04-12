#include "CppUnitTest.h"
#include "../15/Field.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestCheckElements)
		{
			Field field;
			Assert::AreEqual(field.Check(), true);
		}

		TEST_METHOD(TestGetElementPosition)
		{
			Field field;
			field.setPosition(50.f, 50.f);

			Assert::AreEqual(10.f, field.GetElementPosition(0).x, L"Element 0 coordinate X failed");
			Assert::AreEqual(130.f, field.GetElementPosition(1).x, L"Element 1 coordinate X failed");
			Assert::AreEqual(250.f, field.GetElementPosition(2).x, L"Element 2 coordinate X failed");
			Assert::AreEqual(370.f, field.GetElementPosition(3).x, L"Element 3 coordinate X failed");

			Assert::AreEqual(10.f, field.GetElementPosition(0).y, L"Element 0 coordinate Y failed");
			Assert::AreEqual(10.f, field.GetElementPosition(1).y, L"Element 1 coordinate Y failed");
			Assert::AreEqual(10.f, field.GetElementPosition(2).y, L"Element 2 coordinate Y failed");
			Assert::AreEqual(10.f, field.GetElementPosition(3).y, L"Element 3 coordinate Y failed");
		}
	};
}