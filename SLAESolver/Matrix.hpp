#pragma once
#include "profile_matrix_manager.hpp"
#include <vector>
#include <string>

template<typename Real>
class Matrix
{
protected:
   int n_;

   std::vector<int> ia_;
   std::vector<Real> di_;
   std::vector<Real> al_;
   std::vector<Real> au_;
public:
   Matrix()
   {
      this->n_ = 0;
      this->ia_ = std::vector<int>();
      this->di_ = std::vector<Real>();
      this->al_ = std::vector<Real>();
      this->au_ = std::vector<Real>();
   }

   virtual void MemoryAllocation(std::string file_name)
   {
      profile_matrix_manager<Matrix<Real>> matrix;
      matrix.Read(*this, file_name);
   }

   template<typename RealSum>
   void LDUDecomposition()
   {
      Real eps = 0;
      if (typeid(Real) == typeid(float))
      {
         eps = FLT_EPSILON;
      }
      else
      {
         eps = DBL_EPSILON;
      }
      for (auto element : di_)
      {
         if (abs(element) < eps)
         {
            throw std::exception(u8"Матрица не разложима");
         }
      }
      for (int i = 0; i < n_; i++)
      {
         const int i0 = ia_[i];
         const int i1 = ia_[i + 1];
         int j = i - (i1 - i0);
         RealSum sum_d = 0;

         for (int ij = i0; ij < i1; ij++, j++)
         {
            RealSum sum_l = 0;
            RealSum sum_u = 0;

            const int j0 = ia_[j];
            const int j1 = ia_[j + 1];

            int ik = i0;
            int kk = i - (i1 - i0);
            int kj = j0;

            const int column_i = ij - i0;
            const int column_j = j1 - j0;
            const int column_ij = column_i - column_j;

            if (column_ij < 0)
               kj -= column_ij;
            else
            {
               ik += column_ij;
               kk += column_ij;
            }

            for (; ik < ij; ik++, kk++, kj++)
            {
               sum_l += al_[ik] * au_[kj] * di_[kk];
               sum_u += al_[kj] * au_[ik] * di_[kk];
            }
            al_[ij] = (al_[ij] - sum_l) / di_[j];
            au_[ij] = (au_[ij] - sum_u) / di_[j];
            sum_d += al_[ij] * au_[ij] * di_[j];
         }
         if (abs(di_[i] - sum_d) < eps)
         {
            throw std::exception(u8"Матрица не разложима");
         }
         di_[i] -= sum_d;
      }
   }

   void setSize(int n)
   {
      this->n_ = n;
   }

   int& getSize()
   {
      return this->n_;
   }

   void setIA(std::vector<int>& ia)
   {
      this->ia_ = ia;
   }

   std::vector<int>& getIA()
   {
      return this->ia_;
   }

   void setDI(std::vector<Real>& di)
   {
      this->di_ = di;
   }

   std::vector<Real>& getDI()
   {
      return this->di_;
   }

   void setAL(std::vector<Real>& al)
   {
      this->al_ = al;
   }

   std::vector<Real>& getAL()
   {
      return this->al_;
   }

   void setAU(std::vector<Real>& au)
   {
      this->au_ = au;
   }

   std::vector<Real>& getAU()
   {
      return this->au_;
   }
};
