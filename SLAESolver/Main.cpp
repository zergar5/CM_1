#include <iostream>
#include "Solve.hpp"
#include <Windows.h>

int main()
{
   SetConsoleOutputCP(CP_UTF8);

   while (true)
   {
      int p = 0;
      std::cout << u8"Выберите точность: " << std::endl
         << u8"1. float" << std::endl
         << u8"2. double" << std::endl
         << u8"3. Выход из программы" << std::endl;
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
            return 0;
         default:
            {
            std::cout << u8"Выбран отсутствующий пункт, пожалуйста, выберите из списка" << std::endl;
            break;
            }
      }
   }
}
