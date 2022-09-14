#pragma once
#include "MatrixManager.hpp"
#include <vector>
#include <string>

template<typename real>
class Matrix
{
   int n;

   std::vector<int> ia;
   std::vector<real> di;
   std::vector<real> al;
   std::vector<real> au;
public:
   Matrix()
   {
      this->n = 0;
      this->ia = std::vector<int>();
      this->di = std::vector<real>();
      this->al = std::vector<real>();
      this->au = std::vector<real>();
   }

   void MemoryAllocation(std::string fileName)
   {
      MatrixManager<Matrix<real>> matrix;
      matrix.Reader(*this, fileName);
   }

   template<typename realSum>
   void LDUDecomposition()
   {
      for (auto element : di)
      {
         if (abs(element) < FLT_EPSILON)
         {
            throw std::exception(u8"Нельзя разложить матрицу в LDU, так как на диагонали присутствует 0");
         }
      }
      for (int i = 0; i < n; i++)
      {
         int current_row_amount = ia[i];
         int next_row_amount = ia[i + 1];
         int j = i - (next_row_amount - current_row_amount); //с какого j начинается i-ия строка/столбец
         realSum sum_d = 0;

         for (int ij = current_row_amount; ij < next_row_amount; ij++, j++)
         {
            realSum sum_l = 0;
            realSum sum_u = 0;

            int current_column_amount = ia[j];
            int next_column_amount = ia[j + 1];

            int ik = current_row_amount;
            int kk = i - (next_row_amount - current_row_amount);
            int kj = current_column_amount;

            int column_i = ij - current_row_amount;
            int column_j = next_column_amount - current_column_amount;
            int column_ij = column_i - column_j;

            if (column_ij < 0)
               kj -= column_ij;
            else
            {
               ik += column_ij;
               kk += column_ij;
            }

            for (; ik < ij; ik++, kk++, kj++) //сумма по l и u
            {
               sum_l += al[ik] * au[kj] * di[kk];
               sum_u += al[kj] * au[ik] * di[kk];
            }
            //эти 3 цикла вроде верные
            al[ij] = (al[ij] - sum_l) / di[j];
            au[ij] = (au[ij] - sum_u) / di[j];
            sum_d += al[ij] * au[ij] * di[j];
         }
         if (abs(di[i] - sum_d) < FLT_EPSILON)
         {
            throw std::exception(u8"Нельзя разложить матрицу в LDU, так как на диагонали присутствует 0");
         }
         di[i] -= sum_d;
      }
   }

   void setSize(int n)
   {
      this->n = n;
   }

   int getSize()
   {
      return this->n;
   }

   void setIA(std::vector<int> &ia)
   {
      this->ia = ia;
   }

   std::vector<int> getIA()
   {
      return this->ia;
   }

   void setDI(std::vector<real> &di)
   {
      this->di = di;
   }

   std::vector<real> getDI()
   {
      return this->di;
   }

   void setAL(std::vector<real> &al)
   {
      this->al = al;
   }

   std::vector<real> getAL()
   {
      return this->al;
   }

   void setAU(std::vector<real> &au)
   {
      this->au = au;
   }

   std::vector<real> getAU()
   {
      return this->au;
   }
};
