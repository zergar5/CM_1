#pragma once
#include "Matrix.hpp"
#include "MatrixManager.hpp"
#include <vector>
#include <string>

template<class real>
class MatrixK : public Matrix<real>
{
   int _k;
public:
   MatrixK() : Matrix<real>()
   {
      this->_k = 0;
   }

   void MemoryAllocation(std::string fileName) override
   {
      MatrixManager<Matrix<real>> matrix;
      matrix.Reader(*this, fileName);
      MatrixK::di[0] = MatrixK::di[0] + pow(10, -_k);
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