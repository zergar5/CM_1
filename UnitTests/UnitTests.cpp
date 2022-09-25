#include "CppUnitTest.h"
#include "../SLAESolver/solve_slae.hpp"
#include "../SLAESolver/matrix.hpp"
#include "../SLAESolver/gilbert_matrix.hpp"

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

         auto& y = b;
         solve_slae<float>::calc_y<std::vector<float>>(ia, L, b, y);

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

         auto& z = y;
         solve_slae<float>::calc_z<std::vector<float>>(D, y, z);

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

         auto& x = z;

         solve_slae<float>::calc_x<std::vector<float>>(ia, U, z, x);

         for (int i = 0; i < x.size(); i++)
         {
            Assert::AreEqual(x[i], xActual[i]);
         }
      }
   };

   TEST_CLASS(MatrixDecompositionTest)
   {
      TEST_METHOD(LDUDecompositionTest)
      {
         matrix<float> matrixA;
         int n = 5;
         matrixA.set_size(n);

         std::vector<int> ia = { 0, 0, 1, 3, 5, 7 };
         matrixA.set_ia(ia);

         std::vector<float> di = { 1, 2, 3, 4, 5 };
         matrixA.set_di(di);

         std::vector<float> al = { 6, 8, 0, 10, 0, 12, 0 };
         matrixA.set_al(al);

         std::vector<float> au = { 7, 9, 0, 11, 0, 13, 0, };
         matrixA.set_au(au);

         matrixA.ldu_decomposition<float>();

         matrix<float> matrixLDU;
         matrixLDU.set_size(n);

         di = { 1, -40, 6.6f, -24.75f, 11.4462776f };

         al = { 6, 8, 1.4f, -0.25f, -2.04545498f, 1.81818223f, -1.13131309f };

         au = { 7, 9, 1.35f, -0.275f, -2.33333373f, 1.96969748f, -1.07438016f };

         auto D = matrixA.get_di();

         for (int i = 0; i < n; i++)
         {
            Assert::AreEqual(D[i], di[i], 10e-6f);
         }

         auto L = matrixA.get_al();

         for (int i = 0; i < ia[n]; i++)
         {
            Assert::AreEqual(L[i], al[i], 10e-6f);
         }

         auto U = matrixA.get_au();

         for (int i = 0; i < ia[n]; i++)
         {
            Assert::AreEqual(au[i], U[i], 10e-6f);
         }
      }

      TEST_METHOD(LDUZeroOnDiagonalExceptionTest)
      {
         matrix<float> matrixA;
         int n = 5;
         matrixA.set_size(n);

         std::vector<int> ia = { 0, 0, 1, 2, 3, 4 };
         matrixA.set_ia(ia);

         std::vector<float> di = { 0, 1, 1, 1, 1 };
         matrixA.set_di(di);

         std::vector<float> al = { 1, 1, 1, 1 };
         matrixA.set_al(al);

         std::vector<float> au = { 1, 1, 1, 1 };
         matrixA.set_au(au);

         auto a = [&] { matrixA.ldu_decomposition<float>(); };

         Assert::ExpectException<std::exception>(a);
      }

      TEST_METHOD(LDUZeroSumExceptionTest)
      {
         matrix<float> matrixA;
         int n = 5;
         matrixA.set_size(n);

         std::vector<int> ia = { 0, 0, 1, 2, 3, 4 };
         matrixA.set_ia(ia);

         std::vector<float> di = { 1, 1, 1, 1, 1 };
         matrixA.set_di(di);

         std::vector<float> al = { 1, 1, 1, 1 };
         matrixA.set_al(al);

         std::vector<float> au = { 1, 1, 1, 1 };
         matrixA.set_au(au);

         auto a = [&] { matrixA.ldu_decomposition<float>(); };

         Assert::ExpectException<std::exception>(a);
      }
   };

   TEST_CLASS(GilbertMatrixTest)
   {
      TEST_METHOD(ConvertToProfTest)
      {
         gilbert_matrix<float> gilbert_matrix;
         int k = 3;
         gilbert_matrix.set_k(k);
         gilbert_matrix.generate();
         gilbert_matrix.convert_to_prof();

         auto ia = gilbert_matrix.get_ia();
         auto di = gilbert_matrix.get_di();
         auto al = gilbert_matrix.get_al();
         auto au = gilbert_matrix.get_au();

         std::vector<int> actual_ia = { 0, 0, 1, 3 };

         std::vector<float> actual_di = { (float)1, (float)1 / 3, (float)1 / 5 };

         std::vector<float> actual_al = { (float)1 / 2, (float)1 / 3, (float)1 / 4 };
         std::vector<float> actual_au = { (float)1 / 2, (float)1 / 3, (float)1 / 4 };


         for (int i = 0; i < k + 1; i++)
         {
            Assert::AreEqual(ia[i], actual_ia[i]);
         }

         for (int i = 0; i < k; i++)
         {
            Assert::AreEqual(di[i], actual_di[i]);
         }

         for (int i = 0; i < k; i++)
         {
            Assert::AreEqual(al[i], actual_al[i]);
         }

         for (int i = 0; i < k; i++)
         {
            Assert::AreEqual(au[i], actual_au[i]);
         }
      }
   };
}
