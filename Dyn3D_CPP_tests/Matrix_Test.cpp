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
		Matrix<int, 3, 3> expectedValue, rightHand(vals), leftHand(vals), result;

		for (Index_t i = 0; i < expectedValue.Length; i++)
			expectedValue[i] = 0;
		result = leftHand - rightHand;
		Assert::IsTrue(expectedValue == result, L"Subtraction failed.");

		for (Index_t i = 0; i < expectedValue.Length; i++)
			expectedValue[i] = 2;
		result = leftHand + rightHand;
		Assert::IsTrue(expectedValue == result, L"Addition failed.");

		for (Index_t i = 0; i < expectedValue.Length; i++) {
			expectedValue[i] = 1;
			leftHand[i] = 2;
		}
		result = leftHand / 2;
		Assert::IsTrue(expectedValue == result, L"Scalar division failed.");

		result = expectedValue * 2;
		Assert::IsTrue(leftHand == result, L"Scalar multiplication failed.");
	}

	};
}