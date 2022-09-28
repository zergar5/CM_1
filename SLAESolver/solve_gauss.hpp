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

         GaussMatrix<Real> g_matrix = GaussMatrix<Real>();
         try
         {
            g_matrix.MemoryAllocation(matrix_file_name + ".txt");
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
         g_matrix.step_view(vector_b);

         std::vector<Real> vector_x;
         vector_x.resize(g_matrix.getN());

         SolveSlae<float> solve_slae;
         solve_slae.CalcX(g_matrix, vector_b, vector_x);

         if (typeid(Real) == typeid(float))
         {
            vector_manager.Write(vector_x, "gaussoutput.txt", 7);
         }
         else
         {
            vector_manager.Write(vector_x, "gaussoutput.txt", 15);
         }
         break;
      }
      case 2:
      {
         std::cout << u8"������� ��� ����� ������� ��� txt" << std::endl;
         std::string matrix_file_name = "gaussk10";
         std::cin >> matrix_file_name;

         std::cout << u8"������� ��� ����� ������� ��� txt" << std::endl;
         std::string vector_file_name = "gaussFk10";
         std::cin >> vector_file_name;

         GaussMatrix<Real> g_matrix = GaussMatrix<Real>();
         try
         {
            g_matrix.MemoryAllocation(matrix_file_name + ".txt");
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

         g_matrix.step_view(vector_b);

         std::vector<Real> vector_x;
         vector_x.resize(g_matrix.getN());

         SolveSlae<double> solve_slae;
         solve_slae.CalcX(g_matrix, vector_b, vector_x);

         if (typeid(Real) == typeid(float))
         {
            vector_manager.Write(vector_x, "gaussoutput.txt", 7);
         }
         else
         {
            vector_manager.Write(vector_x, "gaussoutput.txt", 15);
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
