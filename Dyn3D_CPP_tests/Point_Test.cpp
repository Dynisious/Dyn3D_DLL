
#include "stdafx.h"
#include "CppUnitTest.h"
#include <exception>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Dyn3D_CPP_tests {
	TEST_CLASS(Point_Test) {
public:

	TEST_METHOD(Point_Functions) {
		Point<double> expectedValues, actualValue, leftHand, rightHand;

		Assert::AreEqual(0.0, Point<double>::dot(leftHand, rightHand), L"Dot product failed.");

		expectedValues.set(0, 0, 1);
		Assert::AreEqual(1.0, expectedValues.magnituid(), L"Magnituid failed.");

		try {
			(Point<double>)(Matrix<double, 1, 4>)expectedValues;
		} catch (std::exception) {
			Assert::Fail(L"Cast has failed.");
		}

		Assert::IsTrue(expectedValues == expectedValues.unit(), L"Unit function failed.");

		Assert::AreEqual(1.0, expectedValues.magnituid(), L"Magnituid failed.");

		Assert::AreEqual(expectedValues.x(), expectedValues[0], L"\"X\" failed.");

		Assert::AreEqual(expectedValues.y(), expectedValues[1], L"\"X\" failed.");

		Assert::AreEqual(expectedValues.z(), expectedValues[2], L"\"X\" failed.");

		Assert::AreEqual(expectedValues.I(), expectedValues[3], L"\"X\" failed.");
	}

	};
}
