#pragma once
#include "gauss_matrix.hpp"
#include "solve_slae.hpp"
#include "vector_manager.hpp"
#include <iostream>

template <typename Real>
void solve_gauss()
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
         std::cout << u8"Введите имя файла матрицы без txt" << std::endl;
         std::string matrix_file_name;
         std::cin >> matrix_file_name;

         std::cout << u8"Введите имя файла вектора без txt" << std::endl;
         std::string vector_file_name;
         std::cin >> vector_file_name;

         gauss_matrix<Real> g_matrix = gauss_matrix<Real>();
         try
         {
            g_matrix.memory_allocation(matrix_file_name + ".txt");
         }
         catch (const char* msg)
         {
            std::cout << msg << std::endl;
            return;
         }

         std::vector<Real> vector_b;
         vector_manager<std::vector<Real>> vector_manager;
         try
         {
            vector_manager.reader(vector_b, matrix_file_name + ".txt", vector_file_name + ".txt");
         }
         catch (const char* msg)
         {
            std::cout << msg << std::endl;
            return;
         }
         g_matrix.step_view(vector_b);

         std::vector<Real> vector_x;
         vector_x.resize(g_matrix.get_n());

         solve_slae<float> solve_slae;
         solve_slae.calc_x(g_matrix, vector_b, vector_x);

         if (typeid(Real) == typeid(float))
         {
            vector_manager.writer(vector_x, "gaussoutput.txt", 7);
         }
         else
         {
            vector_manager.writer(vector_x, "gaussoutput.txt", 15);
         }
         break;
      }
      case 2:
      {
         std::cout << u8"Введите имя файла матрицы без txt" << std::endl;
         std::string matrix_file_name = "gaussk10";
         std::cin >> matrix_file_name;

         std::cout << u8"Введите имя файла вектора без txt" << std::endl;
         std::string vector_file_name = "gaussFk10";
         std::cin >> vector_file_name;

         gauss_matrix<Real> g_matrix = gauss_matrix<Real>();
         try
         {
            g_matrix.memory_allocation(matrix_file_name + ".txt");
         }
         catch (const char* msg)
         {
            std::cout << msg << std::endl;
            return;
         }

         std::vector<Real> vector_b;
         vector_manager<std::vector<Real>> vector_manager;
         try
         {
            vector_manager.reader(vector_b, matrix_file_name + ".txt", vector_file_name + ".txt");
         }
         catch (const char* msg)
         {
            std::cout << msg << std::endl;
            return;
         }

         g_matrix.step_view(vector_b);

         std::vector<Real> vector_x;
         vector_x.resize(g_matrix.get_n());

         solve_slae<double> solve_slae;
         solve_slae.calc_x(g_matrix, vector_b, vector_x);

         if (typeid(Real) == typeid(float))
         {
            vector_manager.writer(vector_x, "gaussoutput.txt", 7);
         }
         else
         {
            vector_manager.writer(vector_x, "gaussoutput.txt", 15);
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
