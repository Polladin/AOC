
#include "get_password.h"

int GetPassword::run_part_1( int first, int last )
{
  int res = 0;

  for ( int num = first; num <= last; ++num )
    res += is_valid_password( num ) ? 1 : 0;

  return res;
}


std::deque< int > GetPassword::split_by_digits( int num )
{
  std::deque< int > res;

  for (; num > 0; num /= 10)
    res.push_front( num % 10 );

  return res;
}


bool GetPassword::is_valid_password( int num )
{
  std::deque< int > spNum = split_by_digits( num );

  int prevDigit{ -1 };
  bool isDouble{ false };
  int doubledCount{ 0 };

  for ( auto _digit : spNum )
  {
    // Decreasing
    if ( _digit < prevDigit )
      return false;

    // Doubled
    if ( _digit == prevDigit )
    {
      doubledCount += ( doubledCount == 0 ) ? 2 : 1;
    }
    else
    {
      if ( doubledCount == 2 )
        isDouble = true;

      doubledCount = 0;
    }
    
    prevDigit = _digit;
  }

  if ( doubledCount == 2 )
  {
    isDouble = true;
  }
  

  return isDouble;
}
