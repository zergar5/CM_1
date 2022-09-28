#pragma once
#include <vector>

template<typename RealSum>
class SolveSlae
{
public:
   template<class V>
   static void CalcY(std::vector<int>& ia, V& al, V& vec_b, V& vec_y)
   {
      const int n = vec_b.size();

      for (int i = 0; i < n; i++)
      {
         RealSum sum_l = 0;
         const int i0 = ia[i];
         const int i1 = ia[i + 1];
         int j = i - (i1 - i0);

         for (int k = i0; k < i1; k++, j++)
         {
            sum_l += al[k] * vec_y[j];
         }
         vec_y[i] = vec_b[i] - sum_l;
      }
   }

   template<class V>
   static void CalcZ(V& di, V& vec_y, V& vec_z)
   {
      const int n = vec_y.size();

      for (int i = 0; i < n; i++)
      {
         vec_z[i] = vec_y[i] / di[i];
      }
   }

   template<class V>
   static void CalcX(std::vector<int>& ia, V& au, V& vec_z, V& vec_x)
   {
      const int n = vec_z.size();

      for (int i = n - 1; i >= 0; --i)
      {
         const int i0 = ia[i];
         const int i1 = ia[i + 1];
         int j = i - (i1 - i0);
         for (int k = i0; k < i1; ++k, ++j)
         {
            vec_x[j] -= vec_z[i] * au[k];
         }
      }
   }

   template<class M, class V>
   static void CalcX(M& matrix, V& b, V& x)
   {
      auto n = matrix.getN();
      x.resize(n);
      auto& g_matrix = matrix.getMatrix();

      for (int i = n - 1; i >= 0; --i)
      {
         RealSum sum = 0;
         for (int j = i + 1; j < n; ++j)
         {
            sum += g_matrix[i][j] * x[j];
         }
         x[i] = (b[i] - sum) / g_matrix[i][i];
      }
   }

   template<class M, class V>
   V Solve(M& matrix, V& vec)
   {
      auto& y = vec;
      auto& z = y;
      auto& x = z;
      auto& ia = matrix.getIA();
      auto& al = matrix.getAL();
      CalcY(ia, al, vec, y);
      auto& di = matrix.getDI();
      CalcZ(di, y, z);
      auto& au = matrix.getAU();
      CalcX(ia, au, z, x);
      return x;
   }
};
