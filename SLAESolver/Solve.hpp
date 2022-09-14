#pragma once
#include "Matrix.hpp"
#include "SolveSLAE.hpp"
#include "VectorManager.hpp"
#include <iostream>

template <typename real>
void Solve()
{
   while (true)
   {
      Matrix<real> profile_matrix = Matrix<real>();
      try
      {
         profile_matrix.MemoryAllocation("matrixk^0.txt");
      }
      catch (const char* msg)
      {
         std::cout << msg << std::endl;
         return;
      }

      std::vector<real> vector_b;
      VectorManager<std::vector<real>> vector_manager;
      vector_manager.Reader(vector_b, "profile_matrix.txt", "vector.txt");
      std::vector<real> vector_x;

      int p = 0;
      std::cout << u8"Выберите точность суммы: " << std::endl
         << u8"1. float" << std::endl
         << u8"2. double" << std::endl
         << u8"3. Вернуться на этам выбора точности" << std::endl;
      std::cin >> p;
      int n = 0;
      switch (p)
      {
         case 1:
            {
            profile_matrix.LDUDecomposition<float>();
            SolveSLAE<float> solve_slae;
            vector_x = solve_slae.Solve(profile_matrix, vector_b);
            n = 7;
            break;
            }
         case 2:
            {
            profile_matrix.LDUDecomposition<double>();
            SolveSLAE<double> solve_slae;
            vector_x = solve_slae.Solve(profile_matrix, vector_b);
            n = 15;
            break;
            }
         case 3:
            return;
         default:
            {
            std::cout << u8"Выбрать отсутствующий пункт, пожалуйста, выберите из списка" << std::endl;
            break;
            }
      }
      vector_manager.Writer(vector_x, "output.txt", n);
   }
}
