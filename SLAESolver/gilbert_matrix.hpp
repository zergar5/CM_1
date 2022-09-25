#pragma once
#include "matrix.hpp"

template<class Real>
class gilbert_matrix : public matrix<Real>
{
   int k_;
   std::vector<std::vector<double>> gilbert_matrix_;
public:
   gilbert_matrix() : matrix<Real>()
   {
      gilbert_matrix_ = std::vector<std::vector<double>>(20, std::vector<double>(20));
   }

   void generate()
   {
      for (int i = 0; i < k_; i++)
      {
         gilbert_matrix_[i][i] = 1. / (2. * (static_cast<double>(i) + 1.) - 1.);
         for (int j = 0; j < i; j++)
         {
            gilbert_matrix_[i][j] = 1. / (static_cast<double>(i) + 1. + static_cast<double>(j));
            gilbert_matrix_[j][i] = gilbert_matrix_[i][j];
         }
      }
   }

   std::vector<Real> generate_vector_fk()
   {
      std::vector<Real> vec_b;
      vec_b.resize(k_);
      for (int i = 0; i < k_; i++)
      {
         for (int j = 0; j < k_; j++)
         {
            vec_b[i] += gilbert_matrix_[i][j] * (static_cast<double>(j) + 1.);
         }
      }
      return vec_b;
   }

   void convert_to_prof()
   {
      gilbert_matrix::n_ = k_;
      gilbert_matrix::di_.resize(gilbert_matrix::n_);
      gilbert_matrix::ia_.resize(gilbert_matrix::n_ + 1);
      gilbert_matrix::al_.resize((gilbert_matrix::n_ - 1) * gilbert_matrix::n_ / 2);
      gilbert_matrix::au_.resize((gilbert_matrix::n_ - 1) * gilbert_matrix::n_ / 2);

      gilbert_matrix::ia_[0] = 0;

      for (int i = 0; i < gilbert_matrix::n_; i++)
      {
         gilbert_matrix::ia_[i + 1] = gilbert_matrix::ia_[i] + i;
         gilbert_matrix::di_[i] = gilbert_matrix_[i][i];
         for (int j = 0; j < i; j++)
         {
            gilbert_matrix::al_[gilbert_matrix::ia_[i] + j] = gilbert_matrix_[i][j];
            gilbert_matrix::au_[gilbert_matrix::ia_[i] + j] = gilbert_matrix_[j][i];
         }
      }
   }

   void set_k(int k)
   {
      this->k_ = k;
   }

   int& get_k()
   {
      return this->k_;
   }
};
