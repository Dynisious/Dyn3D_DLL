
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Dyn3D_CPP_tests {
	TEST_CLASS(Matrix_Test) {
public:

	TEST_METHOD(Matrix_Arithmatic) {
		int vals[] = {
			1,1,1,
			1,1,1,
			1,1,1
		};
		Matrix<int, 3, 3> expectedValue, rightHand(vals), leftHand(vals), actualValue;

		for (Index_t i = 0; i < expectedValue.Length; i++)
			expectedValue[i] = 0;
		actualValue = leftHand - rightHand;
		Assert::IsTrue(expectedValue == actualValue, L"Subtraction failed.");

		for (Index_t i = 0; i < expectedValue.Length; i++)
			expectedValue[i] = 2;
		actualValue = leftHand + rightHand;
		Assert::IsTrue(expectedValue == actualValue, L"Addition failed.");

		for (Index_t i = 0; i < expectedValue.Length; i++) {
			expectedValue[i] = 1;
			leftHand[i] = 2;
		}
		actualValue = leftHand / 2;
		Assert::IsTrue(expectedValue == actualValue, L"Scalar division failed.");

		actualValue = expectedValue * 2;
		Assert::IsTrue(leftHand == actualValue, L"Scalar multiplication failed.");

		Assert::IsTrue(1 == expectedValue.get(0, 0), L"Get failed.");

		expectedValue.set(0, 1, 0);
		Assert::IsTrue(0 == expectedValue.get(0, 1), L"Set failed.");

		expectedValue.set(0, 2, 0);
		Assert::IsTrue(expectedValue.invert().get(0, 0) == -1.0, L"Invert failed.");

		for (int i = 0; i < expectedValue.Length; i++)
			expectedValue[i] = 0;
		actualValue.clear();
		Assert::IsTrue(expectedValue == actualValue, L"Clear failed.");
	}

	};
}
