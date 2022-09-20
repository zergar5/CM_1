#include <iostream>
#include "Solve.hpp"
#include "SolveK.hpp"
#include "SolveGilbert.hpp"
#include <Windows.h>

int main()
{
   SetConsoleOutputCP(CP_UTF8);

   while (true)
   {
   exit:
      int m = 0;
      std::cout << u8"Выберите способ решения: " << std::endl
         << u8"1. Разложение профильной матрицы" << std::endl
         << u8"2. Разложение профильной матрицы с k" << std::endl
         << u8"3. Разложение матрицы Гильберта" << std::endl
         //<< u8"4. Метод Гаусса" << std::endl
         << u8"5. Выход из программы" << std::endl;
      std::cin >> m;

      switch (m)
      {
      case 1:
      {
         while (true)
         {
            int p = 0;
            std::cout << u8"Выберите точность: " << std::endl
               << u8"1. float" << std::endl
               << u8"2. double" << std::endl
               << u8"3. Выход в меню выбора способа" << std::endl;
            std::cin >> p;
            switch (p)
            {
            case 1:
            {
               Solve<float>();
               break;
            }
            case 2:
            {
               Solve<double>();
               break;
            }
            case 3:
               goto exit;
            default:
            {
               std::cout << u8"Выбран отсутствующий пункт, пожалуйста, выберите из списка" << std::endl;
               break;
            }
            }
         }
      }
      case 2:
      {
         while (true)
         {
            int p = 0;
            std::cout << u8"Выберите точность: " << std::endl
               << u8"1. float" << std::endl
               << u8"2. double" << std::endl
               << u8"3. Выход в меню выбора способа" << std::endl;
            std::cin >> p;
            switch (p)
            {
            case 1:
            {
               SolveK<float>();
               break;
            }
            case 2:
            {
               SolveK<double>();
               break;
            }
            case 3:
               goto exit;
            default:
            {
               std::cout << u8"Выбран отсутствующий пункт, пожалуйста, выберите из списка" << std::endl;
               break;
            }
            }
         }
      }
      case 3:
         while (true)
         {
            int p = 0;
            std::cout << u8"Выберите точность: " << std::endl
               << u8"1. float" << std::endl
               << u8"2. double" << std::endl
               << u8"3. Выход в меню выбора способа" << std::endl;
            std::cin >> p;
            switch (p)
            {
            case 1:
            {
               SolveGilbert<float>();
               break;
            }
            case 2:
            {
               SolveGilbert<double>();
               break;
            }
            case 3:
               goto exit;
            default:
            {
               std::cout << u8"Выбран отсутствующий пункт, пожалуйста, выберите из списка" << std::endl;
               break;
            }
            }
         }
      case 4:
      {
         break;
      }
      default:
      {
         std::cout << u8"Выбран отсутствующий пункт, пожалуйста, выберите из списка" << std::endl;
         break;
      }
      }
   }
}
