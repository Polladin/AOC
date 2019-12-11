#pragma once

#include <vector>
#include <deque>


class GetPassword
{

public:

  int run_part_1( int first, int last );

private:

  std::deque< int > split_by_digits( int num );

  bool is_valid_password( int num );

};