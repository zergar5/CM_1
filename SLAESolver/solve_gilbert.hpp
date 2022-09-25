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

         gilbert_matrix<Real> g_matrix = gilbert_matrix<Real>();
         g_matrix.set_k(k);
         try
         {
            g_matrix.generate();
         }
         catch (const char* msg)
         {
            std::cout << msg << std::endl;
            return;
         }

         std::vector<Real> vector_b = g_matrix.generate_vector_fk();
         g_matrix.convert_to_prof();

         std::vector<Real> vector_x;

         g_matrix.ldu_decomposition<float>();

         solve_slae<float> solve_slae;
         vector_x = solve_slae.solve(g_matrix, vector_b);

         vector_manager<std::vector<Real>> vector_manager;
         if (typeid(Real) == typeid(float))
         {
            vector_manager.writer(vector_x, "outputGilbert" + std::to_string(k) + ".txt", 7);
         }
         else
         {
            vector_manager.writer(vector_x, "outputGilbert" + std::to_string(k) + ".txt", 15);
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

         gilbert_matrix<Real> g_matrix = gilbert_matrix<Real>();
         g_matrix.set_k(k);
         try
         {
            g_matrix.generate();
         }
         catch (const char* msg)
         {
            std::cout << msg << std::endl;
            return;
         }

         std::vector<Real> vector_b = g_matrix.generate_vector_fk();
         g_matrix.convert_to_prof();

         std::vector<Real> vector_x;

         g_matrix.ldu_decomposition<double>();

         solve_slae<double> solve_slae;
         vector_x = solve_slae.solve(g_matrix, vector_b);

         vector_manager<std::vector<Real>> vector_manager;
         if (typeid(Real) == typeid(float))
         {
            vector_manager.writer(vector_x, "outputGilbert" + std::to_string(k) + ".txt", 7);
         }
         else
         {
            vector_manager.writer(vector_x, "outputGilbert" + std::to_string(k) + ".txt", 15);
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