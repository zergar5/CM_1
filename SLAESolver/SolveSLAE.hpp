#pragma once
#include <vector>

template<typename realSum>
class SolveSLAE
{
public:
   template<class V>
   static void CalcY(std::vector<int>& ia, V& al, V& vec_b, V& vec_y)
   {
      int n = vec_b.size();

      for (int i = 0; i < n; i++)
      {
         realSum sum_l = 0;
         int i0 = ia[i];
         int i1 = ia[i + 1];
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
      int n = vec_y.size();

      for (int i = 0; i < n; i++)
      {
         vec_z[i] = vec_y[i] / di[i];
      }
   }

   template<class V>
   static void CalcX(std::vector<int>& ia, V& au, V& vec_z, V& vec_x)
   {
      int n = vec_z.size();

      for (int i = n - 1; i >= 0; i--)
      {
         int i0 = ia[i];
         int i1 = ia[i + 1];
         int j = i - (i1 - i0);
         for (int k = i0; k < i1; k++, j++)
         {
            vec_x[j] -= vec_z[i] * au[k];
         }
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
