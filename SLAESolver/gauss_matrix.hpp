#pragma once
#include <vector>
#include "matrix_manager.hpp"

template<class Real>
class GaussMatrix
{
   int n_ = 0;
   std::vector<std::vector<Real>> gauss_matrix_;
public:
   void MemoryAllocation(std::string file_name)
   {
      MatrixManager<GaussMatrix<Real>> matrix_manager;
      matrix_manager.Read(*this, file_name);
   }

   void step_view(std::vector<Real>& b)
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
      for (int i = 0; i < n_ - 1; i++)
      {
         Real max = abs(gauss_matrix_[i][i]);
         int row_number = i;
         for (int j = i + 1; j < n_; j++)
         {
            if (max < abs(gauss_matrix_[j][i]))
            {
               max = abs(gauss_matrix_[j][i]);
               row_number = j;
            }
         }
         if (row_number != i)
         {
            std::swap(gauss_matrix_[i], gauss_matrix_[row_number]);
            std::swap(b[i], b[row_number]);
         }
         if (abs(gauss_matrix_[i][i]) > eps)
         {
            for (int j = i + 1; j < n_; j++)
            {
               Real coef = gauss_matrix_[j][i] / gauss_matrix_[i][i];
               gauss_matrix_[j][i] = 0.;
               b[j] -= coef * b[i];

               for (int k = i + 1; k < n_; k++)
               {
                  gauss_matrix_[j][k] -= coef * gauss_matrix_[i][k];
               }
            }
         }
      }
   }

   void setN(int n)
   {
      this->n_ = n;
   }

   int& getN()
   {
      return this->n_;
   }

   void setMatrix(std::vector<std::vector<Real>>& gauss_matrix)
   {
      this->gauss_matrix_ = gauss_matrix;
   }

   std::vector<std::vector<Real>>& getMatrix()
   {
      return this->gauss_matrix_;
   }
};
