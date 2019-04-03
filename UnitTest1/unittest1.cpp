#include "CppUnitTest.h"
#include "../15/Field.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestGetElementIndex)
		{
			Field field;
			field.setPosition(50.f, 50.f);
			field.SetSize(sf::Vector2i(500, 500));
			Assert::AreEqual(field.GetElementIndex(sf::Vector2i(59, 60)), -1, L"Left boundary failed");
			Assert::AreEqual(field.GetElementIndex(sf::Vector2i(59, 59)), -1, L"Top boundary failed");
			Assert::AreEqual(field.GetElementIndex(sf::Vector2i(60, 60)), 0, L"Cell index 0 failed");
			Assert::AreEqual(field.GetElementIndex(sf::Vector2i(120 + 60, 60)), 1);
			Assert::AreEqual(field.GetElementIndex(sf::Vector2i(120 + 120 + 60, 60)), 2);
			Assert::AreEqual(field.GetElementIndex(sf::Vector2i(120 + 120 + 120 + 60, 60)), 3);
			Assert::AreEqual(field.GetElementIndex(sf::Vector2i(120 + 120 + 120 + 120 + 60, 60)), -1, L"Right boundary failed");
			Assert::AreEqual(field.GetElementIndex(sf::Vector2i(60, 120 + 60)), 4);
		}

		TEST_METHOD(TestGetElementPosition)
		{
			Field field;
			field.setPosition(50.f, 50.f);
			field.SetSize(sf::Vector2i(500, 500));
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