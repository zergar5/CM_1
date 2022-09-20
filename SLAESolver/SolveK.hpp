#pragma once
#include "Matrixk.hpp"
#include "SolveSLAE.hpp"
#include "VectorManager.hpp"
#include <iostream>

template <typename real>
void SolveK()
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

         std::cout << u8"Введите k" << std::endl;
         int k = 0;
         std::cin >> k;

         MatrixK<real> matrix_k = MatrixK<real>();
         matrix_k.setK(k);
         try
         {
            matrix_k.MemoryAllocation(matrix_file_name + ".txt");
         }
         catch (const char* msg)
         {
            std::cout << msg << std::endl;
            return;
         }

         std::vector<real> vector_b;
         VectorManager<std::vector<real>> vector_manager;
         try
         {
            vector_manager.Reader(vector_b, matrix_file_name + ".txt", vector_file_name + ".txt");
         }
         catch (const char* msg)
         {
            std::cout << msg << std::endl;
            return;
         }
         vector_b[0] += pow(10.0, -k);

         std::vector<real> vector_x;

         matrix_k.LDUDecomposition<float>();

         SolveSLAE<float> solve_slae;
         vector_x = solve_slae.Solve(matrix_k, vector_b);

         if (typeid(real) == typeid(float))
         {
            vector_manager.Writer(vector_x, "outputK" + std::to_string(k) + ".txt", 7);
         }
         else
         {
            vector_manager.Writer(vector_x, "outputK" + std::to_string(k) + ".txt", 15);
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

         std::cout << u8"Введите k" << std::endl;
         int k = 0;
         std::cin >> k;

         MatrixK<real> matrix_k = MatrixK<real>();
         matrix_k.setK(k);
         try
         {
            matrix_k.MemoryAllocation(matrix_file_name + ".txt");
         }
         catch (const char* msg)
         {
            std::cout << msg << std::endl;
            return;
         }

         std::vector<real> vector_b;
         VectorManager<std::vector<real>> vector_manager;
         try
         {
            vector_manager.Reader(vector_b, matrix_file_name + ".txt", vector_file_name + ".txt");
         }
         catch (const char* msg)
         {
            std::cout << msg << std::endl;
            return;
         }
         vector_b[0] += pow(10.0, -k);

         std::vector<real> vector_x;

         matrix_k.LDUDecomposition<double>();

         SolveSLAE<double> solve_slae;
         vector_x = solve_slae.Solve(matrix_k, vector_b);

         if (typeid(real) == typeid(float))
         {
            vector_manager.Writer(vector_x, "outputK" + std::to_string(k) + ".txt", 7);
         }
         else
         {
            vector_manager.Writer(vector_x, "outputK" + std::to_string(k) + ".txt", 15);
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