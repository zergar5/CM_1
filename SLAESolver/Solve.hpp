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

         matrix<Real> profile_matrix = matrix<Real>();
         try
         {
            profile_matrix.memory_allocation(matrix_file_name + ".txt");
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

         std::vector<Real> vector_x;

         profile_matrix.ldu_decomposition<float>();

         solve_slae<float> solve_slae;
         vector_x = solve_slae.solve(profile_matrix, vector_b);

         if (typeid(Real) == typeid(float))
         {
            vector_manager.writer(vector_x, "output.txt", 7);
         }
         else
         {
            vector_manager.writer(vector_x, "output.txt", 15);
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

         matrix<Real> profile_matrix = matrix<Real>();
         try
         {
            profile_matrix.memory_allocation(matrix_file_name + ".txt");
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

         std::vector<Real> vector_x;

         profile_matrix.ldu_decomposition<double>();

         solve_slae<double> solve_slae;
         vector_x = solve_slae.solve(profile_matrix, vector_b);

         if (typeid(Real) == typeid(float))
         {
            vector_manager.writer(vector_x, "output.txt", 7);
         }
         else
         {
            vector_manager.writer(vector_x, "output.txt", 15);
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
