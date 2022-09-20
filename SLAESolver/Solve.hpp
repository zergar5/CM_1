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
      int p = 0;
      std::cout << u8"�������� �������� �����: " << std::endl
         << u8"1. float" << std::endl
         << u8"2. double" << std::endl
         << u8"3. ��������� �� ���� ������ ��������" << std::endl;
      std::cin >> p;

      switch (p)
      {
      case 1:
      {
         std::cout << u8"������� ��� ����� ������� ��� txt" << std::endl;
         std::string matrix_file_name;
         std::cin >> matrix_file_name;

         std::cout << u8"������� ��� ����� ������� ��� txt" << std::endl;
         std::string vector_file_name;
         std::cin >> vector_file_name;

         Matrix<real> profile_matrix = Matrix<real>();
         try
         {
            profile_matrix.MemoryAllocation(matrix_file_name + ".txt");
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

         std::vector<real> vector_x;

         profile_matrix.LDUDecomposition<float>();

         SolveSLAE<float> solve_slae;
         vector_x = solve_slae.Solve(profile_matrix, vector_b);

         if (typeid(real) == typeid(float))
         {
            vector_manager.Writer(vector_x, "output.txt", 7);
         }
         else
         {
            vector_manager.Writer(vector_x, "outputK.txt", 15);
         }

         break;
      }
      case 2:
      {
         std::cout << u8"������� ��� ����� ������� ��� txt" << std::endl;
         std::string matrix_file_name;
         std::cin >> matrix_file_name;

         std::cout << u8"������� ��� ����� ������� ��� txt" << std::endl;
         std::string vector_file_name;
         std::cin >> vector_file_name;

         Matrix<real> profile_matrix = Matrix<real>();
         try
         {
            profile_matrix.MemoryAllocation(matrix_file_name + ".txt");
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

         std::vector<real> vector_x;

         profile_matrix.LDUDecomposition<double>();

         SolveSLAE<double> solve_slae;
         vector_x = solve_slae.Solve(profile_matrix, vector_b);

         if (typeid(real) == typeid(float))
         {
            vector_manager.Writer(vector_x, "output.txt", 7);
         }
         else
         {
            vector_manager.Writer(vector_x, "output.txt", 15);
         }

         break;
      }
      case 3:
         return;
      default:
      {
         std::cout << u8"������� ������������� �����, ����������, �������� �� ������" << std::endl;
         break;
      }
      }
   }
}
