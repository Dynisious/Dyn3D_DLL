// Dyn3D_DLL_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
TEST_CLASS(Matrix_Test) {
public:
	TEST_METHOD(TestMethodName) {
		int vals[] = {
			1,1,1,
			1,1,1,
			1,1,1 
		}
		Matrix<int, 3, 3> expectedValue;
		for (Index_t i = 0; i < expectedValue[i]; i++)
			expectedValue[i] = 0;
		Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
	}
}


int main() {
	return 0;
}

