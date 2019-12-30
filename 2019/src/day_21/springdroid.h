#pragma once

#include <string>
#include <queue>


class Springdroid
{

public:

  int run_part_1( const std::string & fileName );
  int run_part_2( const std::string & fileName );

private:

  void push_to_input( const std::string & str, std::queue< long long > & input );

};