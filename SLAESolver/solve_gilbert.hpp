#pragma once
#include "gilbert_matrix.hpp"
#include "solve_slae.hpp"
#include "vector_manager.hpp"
#include <iostream>

template <typename Real>
void solve_gilbert()
{
   while (true)
   {
      int p = 0;

      std::cout << u8"Выберите точность суммы: " << std::endl
         << u8"1. float" << std::endl
         << u8"2. double" << std::endl
         << u8"3. Вернуться на этам выбора точности" << std::endl;
      std::cin >> p;

      switch (p)
      {
      case 1:
      {
         std::cout << u8"Введите k" << std::endl;
         int k = 0;
         std::cin >> k;

         if (k == 0)
         {
            std::cout << u8"k не может быть ниже 1" << std::endl;
            break;
         }

         GilbertMatrix<Real> g_matrix = GilbertMatrix<Real>();
         g_matrix.setK(k);
         try
         {
            g_matrix.Generate();
         }
         catch (const char* msg)
         {
            std::cout << msg << std::endl;
            return;
         }

         std::vector<Real> vector_b = g_matrix.GenerateVectorFk();
         g_matrix.ConvertToProf();

         std::vector<Real> vector_x;

         g_matrix.LDUDecomposition<float>();

         SolveSlae<float> solve_slae;
         vector_x = solve_slae.Solve(g_matrix, vector_b);

         VectorManager<std::vector<Real>> vector_manager;
         if (typeid(Real) == typeid(float))
         {
            vector_manager.Write(vector_x, "outputGilbert" + std::to_string(k) + ".txt", 7);
         }
         else
         {
            vector_manager.Write(vector_x, "outputGilbert" + std::to_string(k) + ".txt", 15);
         }
         break;
      }
      case 2:
      {
         std::cout << u8"Введите k" << std::endl;
         int k = 0;
         std::cin >> k;

         if (k == 0)
         {
            std::cout << u8"k не может быть ниже 1" << std::endl;
            break;
         }

         GilbertMatrix<Real> g_matrix = GilbertMatrix<Real>();
         g_matrix.setK(k);
         try
         {
            g_matrix.Generate();
         }
         catch (const char* msg)
         {
            std::cout << msg << std::endl;
            return;
         }

         std::vector<Real> vector_b = g_matrix.GenerateVectorFk();
         g_matrix.ConvertToProf();

         std::vector<Real> vector_x;

         g_matrix.LDUDecomposition<double>();

         SolveSlae<double> solve_slae;
         vector_x = solve_slae.Solve(g_matrix, vector_b);

         VectorManager<std::vector<Real>> vector_manager;
         if (typeid(Real) == typeid(float))
         {
            vector_manager.Write(vector_x, "outputGilbert" + std::to_string(k) + ".txt", 7);
         }
         else
         {
            vector_manager.Write(vector_x, "outputGilbert" + std::to_string(k) + ".txt", 15);
         }
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
   }
}