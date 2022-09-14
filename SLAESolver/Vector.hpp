#pragma once
#include "VectorManager.hpp"
#include <vector>
#include <string>

template<typename real>
class Vector
{
   int n;

   std::vector<real> vec;

public:
   Vector()
   {
      this->n = 0;
      this->vec = std::vector<real>();
   }

   void MemoryAllocation(std::string fileNameForSize, std::string fileName)
   {
      VectorManager<std::vector<real>> vector_manager;
      vector_manager.Reader(this, fileNameForSize, fileName);
   }

   void setSize(int n)
   {
      this->n = n;
   }

   int getSize()
   {
      return this->n;
   }

   void setVector(std::vector<real>& ia)
   {
      this->vec = std::move(ia);
   }

   std::vector<real> getVector()
   {
      return this->vec;
   }
};
