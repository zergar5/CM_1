#pragma once
#include "Matrix.hpp"

template<class real>
class GilbertMatrix : public Matrix<real>
{
   int _k;
   std::vector<std::vector<real>> _gilbertMatrix;
public:
   GilbertMatrix() : Matrix<real>()
   {
      _gilbertMatrix = std::vector<std::vector<real>>(20, std::vector<real>(20));
   }

   void Generate()
   {
      for (int i = 0; i < _k; i++)
      {
         _gilbertMatrix[i][i] = (real)1 / (2 * (i + 1) - 1);
         for (int j = 0; j < i; j++)
         {
            _gilbertMatrix[i][j] = (real)1 / (i + 1 + j);
            _gilbertMatrix[j][i] = _gilbertMatrix[i][j];
         }
      }
   }

   std::vector<real> GenerateVectorFk()
   {
      std::vector<real> vec_b;
      vec_b.resize(_k);
      for (int i = 0; i < _k; i++)
      {
         for (int j = 0; j < _k; j++)
         {
            vec_b[i] += _gilbertMatrix[i][j] * (j + 1);
         }
      }
      return vec_b;
   }

   void ConvertToProf()
   {
      GilbertMatrix::n = _k;
      GilbertMatrix::di.resize(GilbertMatrix::n);
      GilbertMatrix::ia.resize(GilbertMatrix::n + 1);
      GilbertMatrix::al.resize((GilbertMatrix::n - 1) * GilbertMatrix::n / 2);
      GilbertMatrix::au.resize((GilbertMatrix::n - 1) * GilbertMatrix::n / 2);

      this->ia[0] = 0;

      for (int i = 0; i < GilbertMatrix::n; i++)
      {
         GilbertMatrix::ia[i + 1] = GilbertMatrix::ia[i] + i;
         GilbertMatrix::di[i] = _gilbertMatrix[i][i];
         for (int j = 0; j < i; j++)
         {
            GilbertMatrix::al[GilbertMatrix::ia[i] + j] = _gilbertMatrix[i][j];
            GilbertMatrix::au[GilbertMatrix::ia[i] + j] = _gilbertMatrix[j][i];
         }
      }
   }

   void setK(int k)
   {
      this->_k = k;
   }

   int& getK()
   {
      return this->_k;
   }
};
