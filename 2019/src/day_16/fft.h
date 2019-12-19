#pragma once

#include <string>
#include <vector>


class FFT
{

public:
  
  std::vector< int > run_part_1( const std::string & fileName );

  std::vector< long long > run_part_2( const std::string & fileName );

private:

  std::vector< int > prepare_input( const std::string & fileName );

  std::vector< int > make_pattern( int idx, int countDigits );

  std::vector< int > calc_phase_1( const std::vector< int > & digits, const std::vector< std::vector< int > > & mult );

};