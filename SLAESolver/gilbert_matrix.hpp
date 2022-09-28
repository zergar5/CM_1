#pragma once
#include "matrix.hpp"

template<class Real>
class GilbertMatrix : public Matrix<Real>
{
   int k_;
   std::vector<std::vector<double>> gilbert_matrix_;
public:
   GilbertMatrix() : Matrix<Real>()
   {
      gilbert_matrix_ = std::vector<std::vector<double>>(20, std::vector<double>(20));
   }

   void Generate()
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

   std::vector<Real> GenerateVectorFk()
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

   void ConvertToProf()
   {
      GilbertMatrix::n_ = k_;
      GilbertMatrix::di_.resize(GilbertMatrix::n_);
      GilbertMatrix::ia_.resize(GilbertMatrix::n_ + 1);
      GilbertMatrix::al_.resize((GilbertMatrix::n_ - 1) * GilbertMatrix::n_ / 2);
      GilbertMatrix::au_.resize((GilbertMatrix::n_ - 1) * GilbertMatrix::n_ / 2);

      GilbertMatrix::ia_[0] = 0;

      for (int i = 0; i < GilbertMatrix::n_; i++)
      {
         GilbertMatrix::ia_[i + 1] = GilbertMatrix::ia_[i] + i;
         GilbertMatrix::di_[i] = gilbert_matrix_[i][i];
         for (int j = 0; j < i; j++)
         {
            GilbertMatrix::al_[GilbertMatrix::ia_[i] + j] = gilbert_matrix_[i][j];
            GilbertMatrix::au_[GilbertMatrix::ia_[i] + j] = gilbert_matrix_[j][i];
         }
      }
   }

   void setK(int k)
   {
      this->k_ = k;
   }

   int& getK()
   {
      return this->k_;
   }
};
