#pragma once

#include <string>
#include <vector>


class Cards
{

private:

  enum class Shuffels
  {
      CUT = 0
    , DEAL_WITH
    , DEAL_INTO
  };


  using t_suffels = std::vector< std::pair< Shuffels, long long > >;

public:

  int run_part_1( const std::string & fileName, int countCards );

  long long run_part_2( const std::string & fileName, long long pos, long long countCards );

private:

  t_suffels prepare_input( const std::string & fileName );

  std::vector< int > make_shuffle( Shuffels type, int val, const std::vector< int > & table );

  long long make_shuffle_back( Shuffels type, long long val, long long pos, long long size );

  std::vector< int > cut( int val, const std::vector< int > & table );
  std::vector< int > deal_with( int val, const std::vector< int > & table );
  std::vector< int > deal_into( const std::vector< int > & table );

  long long cut_back( long long val, long long pos, long long size );
  long long deal_with_back( long long val, long long pos, long long size );
  long long deal_into_back( long long pos, long long size );
};