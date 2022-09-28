#pragma once
#include "matrix.hpp"
#include "solve_slae.hpp"
#include "vector_manager.hpp"
#include <iostream>

template <typename Real>
void solve()
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

         Matrix<Real> profile_matrix = Matrix<Real>();
         try
         {
            profile_matrix.MemoryAllocation(matrix_file_name + ".txt");
         }
         catch (const char* msg)
         {
            std::cout << msg << std::endl;
            return;
         }

         std::vector<Real> vector_b;
         VectorManager<std::vector<Real>> vector_manager;
         try
         {
            vector_manager.Read(vector_b, matrix_file_name + ".txt", vector_file_name + ".txt");
         }
         catch (const char* msg)
         {
            std::cout << msg << std::endl;
            return;
         }

         std::vector<Real> vector_x;

         profile_matrix.LDUDecomposition<float>();

         SolveSlae<float> solve_slae;
         vector_x = solve_slae.Solve(profile_matrix, vector_b);

         if (typeid(Real) == typeid(float))
         {
            vector_manager.Write(vector_x, "output.txt", 7);
         }
         else
         {
            vector_manager.Write(vector_x, "output.txt", 15);
         }

         break;
      }
      case 2:
      {
         std::cout << u8"Введите имя файла матрицы без txt" << std::endl;
         std::string matrix_file_name;
         std::cin >> matrix_file_name;

         std::cout << u8"Введите имя файла вектора без txt" << std::endl;
         std::string vector_file_name;
         std::cin >> vector_file_name;

         Matrix<Real> profile_matrix = Matrix<Real>();
         try
         {
            profile_matrix.MemoryAllocation(matrix_file_name + ".txt");
         }
         catch (const char* msg)
         {
            std::cout << msg << std::endl;
            return;
         }

         std::vector<Real> vector_b;
         VectorManager<std::vector<Real>> vector_manager;
         try
         {
            vector_manager.Read(vector_b, matrix_file_name + ".txt", vector_file_name + ".txt");
         }
         catch (const char* msg)
         {
            std::cout << msg << std::endl;
            return;
         }

         std::vector<Real> vector_x;

         profile_matrix.LDUDecomposition<double>();

         SolveSlae<double> solve_slae;
         vector_x = solve_slae.Solve(profile_matrix, vector_b);

         if (typeid(Real) == typeid(float))
         {
            vector_manager.Write(vector_x, "output.txt", 7);
         }
         else
         {
            vector_manager.Write(vector_x, "output.txt", 15);
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
