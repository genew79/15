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

	};
}