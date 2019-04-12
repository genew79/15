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
			Assert::AreEqual(field.GetElementPosition(0).x, 10.f, L"Element 0 coordinate X failed");
			Assert::AreEqual(field.GetElementPosition(1).x, 130.f, L"Element 1 coordinate X failed");
			Assert::AreEqual(field.GetElementPosition(2).x, 250.f, L"Element 2 coordinate X failed");
			Assert::AreEqual(field.GetElementPosition(3).x, 370.f, L"Element 3 coordinate X failed");

			Assert::AreEqual(field.GetElementPosition(0).y, 10.f, L"Element 0 coordinate Y failed");
			Assert::AreEqual(field.GetElementPosition(1).y, 10.f, L"Element 1 coordinate Y failed");
			Assert::AreEqual(field.GetElementPosition(2).y, 10.f, L"Element 2 coordinate Y failed");
			Assert::AreEqual(field.GetElementPosition(3).y, 10.f, L"Element 3 coordinate Y failed");
		}
	};
}