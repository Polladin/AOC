
#include <iostream>

#include "day_2/computer.h"

#include <array>
#include <limits>


int main()
{
  std::cout << "Day 7: Amplification Circuit\n\n";

  std::vector< long long > out;
  long long res{ std::numeric_limits< long long >::min() };
  std::array< int, 5 > config{ 5, 6, 7, 8, 9 };
  std::array< int, 5 > resConfig;

  std::array< Computer, 5 > cmp;

  while ( true )
  {
    out = std::vector< long long >{ 0 };
    bool isHalted = false;
    bool isInitialized = false;

    // Initialization
    for ( int ampl = 0; ampl < 5; ++ampl )
      cmp[ ampl ].prepare_day_7_part_1( INPUT_FILES "/day_7/part_1.txt" );

    // Main loop
    while ( !isHalted )
    {
      for ( int ampl = 0; ampl < 5; ++ampl )
      {
        std::queue< long long > in;

        // Prepare config input
        if ( !isInitialized )
          in.push( config[ ampl ] );

        for ( auto _val : out )
          in.push( _val );

        isHalted = cmp[ ampl ].run_day_7_part_1( in, out );

      }

      isInitialized = true;
    }

    if ( out[ 0 ] > res )
    {
      res = out[ 0 ];
      resConfig = config;
    }

    if ( !std::next_permutation( config.begin(), config.end() ) )
      break;
  }

  std::cout << "Res : " << res << std::endl;
  for ( auto _val : resConfig )
    std::cout << _val << ", ";
  std::cout << "\n";

  std::cout << "\nThe End\n";
  std::cin.get();
  return 0;
}