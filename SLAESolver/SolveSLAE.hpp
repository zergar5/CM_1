#pragma once
#include <vector>

template<typename realSum>
class SolveSLAE
{
public:
   template<class V>
   static V CalcY(std::vector<int>& ia, V& al, V vec_b)
   {
      int n = vec_b.size();
      V y;
      y.resize(n);

      for (int i = 0; i < n; i++)
      {
         realSum sum_l = 0;
         int current_row_amount = ia[i];
         int next_row_amount = ia[i + 1];
         int j = i - (next_row_amount - current_row_amount);

         for (int k = current_row_amount; k < next_row_amount; k++, j++)
         {
            sum_l += al[k] * y[j];
         }
         y[i] = vec_b[i] - sum_l;
      }
      return y;
   }

   template<class V>
   static V CalcZ(V& di, V vec_y)
   {
      int n = vec_y.size();
      V z;
      z.resize(n);

      for (int i = 0; i < n; i++)
      {
         z[i] = vec_y[i] / di[i];
      }
      return z;
   }

   template<class V>
   static V CalcX(std::vector<int>& ia, V& au, V vec_z)
   {
      int n = vec_z.size();
      V x;
      x.resize(n);

      for (int i = n - 1; i >= 0; i--)
      {
         int current_row_amount = ia[i];
         int next_row_amount = ia[i + 1];
         int j = i - (next_row_amount - current_row_amount);
         realSum xi = vec_z[i]; //чтобы перезаписать x5 = z5 и чтобы сохранить для умножения
         for (int k = current_row_amount; k < next_row_amount; k++, j++)
         {
            vec_z[j] -= xi * au[k]; // обходим с конца по столбцам
         }
         x[i] = vec_z[i];
      }
      return x;
   }

   template<class M, class V>
   V Solve(M &matrix, V &vec)
   {
      auto ia = matrix.getIA();
      auto al = matrix.getAL();
      auto y = CalcY(ia, al, vec);
      auto di = matrix.getDI();
      auto z = CalcZ(di, y);
      auto au = matrix.getAU();
      auto x = CalcX(ia, au, z);
      return x;
   }
};
