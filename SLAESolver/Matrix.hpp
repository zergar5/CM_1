#pragma once
#include "MatrixManager.hpp"
#include <vector>
#include <string>

template<typename real>
class Matrix
{
protected:
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

   virtual void MemoryAllocation(std::string fileName)
   {
      MatrixManager<Matrix<real>> matrix;
      matrix.Reader(*this, fileName);
   }

   template<typename realSum>
   void LDUDecomposition()
   {
      real eps = 0;
      if (typeid(real) == typeid(float))
      {
         eps = FLT_EPSILON;
      }
      else
      {
         eps = DBL_EPSILON;
      }
      for (auto element : di)
      {
         if (abs(element) < eps)
         {
            throw std::exception(u8"Матрица не разложима");
         }
      }
      for (int i = 0; i < n; i++)
      {
         int i0 = ia[i];
         int i1 = ia[i + 1];
         int j = i - (i1 - i0);
         realSum sum_d = 0;

         for (int ij = i0; ij < i1; ij++, j++)
         {
            realSum sum_l = 0;
            realSum sum_u = 0;

            int j0 = ia[j];
            int j1 = ia[j + 1];

            int ik = i0;
            int kk = i - (i1 - i0);
            int kj = j0;

            int column_i = ij - i0;
            int column_j = j1 - j0;
            int column_ij = column_i - column_j;

            if (column_ij < 0)
               kj -= column_ij;
            else
            {
               ik += column_ij;
               kk += column_ij;
            }

            for (; ik < ij; ik++, kk++, kj++)
            {
               sum_l += al[ik] * au[kj] * di[kk];
               sum_u += al[kj] * au[ik] * di[kk];
            }
            al[ij] = (al[ij] - sum_l) / di[j];
            au[ij] = (au[ij] - sum_u) / di[j];
            sum_d += al[ij] * au[ij] * di[j];
         }
         if (abs(di[i] - sum_d) < eps)
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

   int& getSize()
   {
      return this->n;
   }

   void setIA(std::vector<int>& ia)
   {
      this->ia = ia;
   }

   std::vector<int>& getIA()
   {
      return this->ia;
   }

   void setDI(std::vector<real>& di)
   {
      this->di = di;
   }

   std::vector<real>& getDI()
   {
      return this->di;
   }

   void setAL(std::vector<real>& al)
   {
      this->al = al;
   }

   std::vector<real>& getAL()
   {
      return this->al;
   }

   void setAU(std::vector<real>& au)
   {
      this->au = au;
   }

   std::vector<real>& getAU()
   {
      return this->au;
   }
};
