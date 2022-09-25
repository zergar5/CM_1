#include <iostream>
#include "solve.hpp"
#include "solve_gilbert.hpp"
#include "solve_gauss.hpp"
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
         << u8"2. Разложение матрицы Гильберта" << std::endl
         << u8"3. Метод Гаусса" << std::endl
         << u8"4. Выход из программы" << std::endl;
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
               solve<float>();
               break;
            }
            case 2:
            {
               solve<double>();
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
               solve_gilbert<float>();
               break;
            }
            case 2:
            {
               solve_gilbert<double>();
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
      case 3:
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
               solve_gauss<float>();
               break;
            }
            case 2:
            {
               solve_gauss<double>();
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
      default:
      {
         std::cout << u8"Выбран отсутствующий пункт, пожалуйста, выберите из списка" << std::endl;
         break;
      }
      }
   }
}
