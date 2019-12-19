
#include <iostream>

#include <chrono>

#include "fft.h"


void print_res( const std::vector< long long > & res )
{
  std::cout << "Res : ";
  /*for ( auto _el : res )
    std::cout << _el;*/

  for ( int i = res.size() - 1; i > res.size() - 9; --i )
    std::cout << res[ i ];

  std::cout << "\n";
}

int main()
{
  std::cout << "Day 16: Flawed Frequency Transmission\n\n";

  //print_res( FFT().run_part_1( INPUT_FILES "/day_16/example_2.txt" ) );
  //print_res( FFT().run_part_1( INPUT_FILES "/day_16/example_3.txt" ) );
  //print_res( FFT().run_part_1( INPUT_FILES "/day_16/example_4.txt" ) );

  auto timeStart = std::chrono::steady_clock::now();

  print_res( FFT().run_part_2( INPUT_FILES "/day_16/part_1.txt" ) );

  auto timeStop = std::chrono::steady_clock::now();

  std::cout << "Execute time: " << std::chrono::duration_cast<std::chrono::milliseconds>( timeStop - timeStart ).count() << " ms\n";

  std::cin.get();
  return 0;
}

