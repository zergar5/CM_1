#include "CppUnitTest.h"
#include "../SLAESolver/SolveSLAE.hpp"
#include "../SLAESolver/Matrix.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(SolveSLAETest)
	{
	public:
		TEST_METHOD(CalcYTest)
		{
			std::vector<float> L = { 2, 3, 6, 4, 7, 9, 5, 8, 10, 11 };
			std::vector<int> ia = { 0, 0, 1, 3, 6, 10 };
			std::vector<float> yActual = { 1, 2, 3, 4, 5 };

			std::vector<float> b = { 1, 4, 18, 49, 100 };

			auto y = SolveSLAE<float>::CalcY<std::vector<float>>(ia, L, b);

			for (int i = 0; i < y.size(); i++)
			{
				Assert::AreEqual(y[i], yActual[i]);
			}
		}

		TEST_METHOD(CalcZTest)
		{
			std::vector<float> D = { 1, 2, 3, 4, 5 };
			std::vector<float> zActual = { 1, 2, 3, 4, 5 };

			std::vector<float> y = { 1, 4, 9, 16, 25 };

			auto z = SolveSLAE<float>::CalcZ<std::vector<float>>(D, y);

			for (int i = 0; i < z.size(); i++)
			{
				Assert::AreEqual(z[i], zActual[i]);
			}
		}

		TEST_METHOD(CalcXTest)
		{
			std::vector<float> U = { 2, 3, 6, 4, 7, 9, 5, 8, 10, 11 };
			std::vector<int> ia = { 0, 0, 1, 3, 6, 10 };
			std::vector<float> xActual = { 1, 2, 3, 4, 5 };

			std::vector<float> z = { 55, 88, 89, 59, 5 };

			auto x = SolveSLAE<float>::CalcX<std::vector<float>>(ia, U, z);

			for (int i = 0; i < x.size(); i++)
			{
				Assert::AreEqual(x[i], xActual[i]);
			}
		}
	};
	TEST_CLASS(MatrixTest)
	{
		TEST_METHOD(LDUDecompositionTest)
		{
			Matrix<float> matrixA;
			int n = 5;
			matrixA.setSize(n);

			std::vector<int> ia = { 0, 0, 1, 3, 5, 7 };
			matrixA.setIA( ia );

			std::vector<float> di = { 1, 2, 3, 4, 5 };
			matrixA.setDI(di);

			std::vector<float> al = { 6, 8, 0, 10, 0, 12, 0 };
			matrixA.setAL(al);

			std::vector<float> au = { 7, 9, 0, 11, 0, 13, 0, };
			matrixA.setAU(au);

			matrixA.LDUDecomposition<float>();

			Matrix<float> matrixLDU;
			matrixLDU.setSize(n);

			di = { 1, -40, 6.6f, -24.75f, 11.4462776f };

			al = { 6, 8, 1.4f, -0.25f, -2.04545498f, 1.81818223f, -1.13131309f };

			au = { 7, 9, 1.35f, -0.275f, -2.33333373f, 1.96969748f, -1.07438016f };

			auto D = matrixA.getDI();

			for (int i = 0; i < n; i++)
			{
				Assert::AreEqual(D[i], di[i], 10e-6f);
			}

			auto L = matrixA.getAL();

			for (int i = 0; i < ia[n]; i++)
			{
				Assert::AreEqual(L[i], al[i], 10e-6f);
			}

			auto U = matrixA.getAU();

			for (int i = 0; i < ia[n]; i++)
			{
				Assert::AreEqual(au[i], U[i], 10e-6f);
			}
		}

		TEST_METHOD(LDUZeroOnDiagonalExceptionTest)
		{
			Matrix<float> matrixA;
			int n = 5;
			matrixA.setSize(n);

			std::vector<int> ia = { 0, 0, 1, 2, 3, 4 };
			matrixA.setIA(ia);

			std::vector<float> di = { 0, 1, 1, 1, 1 };
			matrixA.setDI(di);

			std::vector<float> al = { 1, 1, 1, 1 };
			matrixA.setAL(al);

			std::vector<float> au = { 1, 1, 1, 1 };
			matrixA.setAU(au);

			auto a = [&] { matrixA.LDUDecomposition<float>(); };

			Assert::ExpectException<std::exception>(a);
		}

		TEST_METHOD(LDUZeroSumExceptionTest)
		{
			Matrix<float> matrixA;
			int n = 5;
			matrixA.setSize(n);

			std::vector<int> ia = { 0, 0, 1, 2, 3, 4 };
			matrixA.setIA(ia);

			std::vector<float> di = { 1, 1, 1, 1, 1 };
			matrixA.setDI(di);

			std::vector<float> al = { 1, 1, 1, 1 };
			matrixA.setAL(al);

			std::vector<float> au = { 1, 1, 1, 1 };
			matrixA.setAU(au);

			auto a = [&] { matrixA.LDUDecomposition<float>(); };

			Assert::ExpectException<std::exception>(a);
		}
	};
}
