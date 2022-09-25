#pragma once
#include <vector>
#include "matrix_manager.hpp"

template<class Real>
class gauss_matrix
{
   int n_ = 0;
   std::vector<std::vector<Real>> gauss_matrix_;
public:
   void memory_allocation(std::string file_name)
   {
      matrix_manager<gauss_matrix<Real>> matrix_manager;
      matrix_manager.reader(*this, file_name);
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

   void set_n(int n)
   {
      this->n_ = n;
   }

   int& get_n()
   {
      return this->n_;
   }

   void set_matrix(std::vector<std::vector<Real>>& gauss_matrix)
   {
      this->gauss_matrix_ = gauss_matrix;
   }

   std::vector<std::vector<Real>>& get_matrix()
   {
      return this->gauss_matrix_;
   }
};
