#pragma once

#include <string>
#include <vector>
#include <memory>


class ShuffleMovements
{
public:

    // deal into new stack,
    virtual long long new_stack ( long long pos, long long size ) = 0;

    // To cut N cards
    virtual long long cut       ( long long pos, long long C, long long size ) = 0;

    // To deal with increment N
    virtual long long increment ( long long pos, long long C, long long size ) = 0;
};


class SlamShuffle
{    
private:

  enum class Shuffels
  {
      CUT = 0
    , DEAL_WITH
    , DEAL_INTO
  };


  using t_action = std::pair< Shuffels, long long >;

  using t_suffels = std::vector< t_action >;

  using t_lcf = std::pair< long long, long long >;

public:

    long long task_1( const std::string & fileName, long long initPos, long long size );

    long long task_2( const std::string & fileName, long long initPos, long long size );

    long long test( long long initVal, long long a, long long size );

    t_lcf pow_lcf( t_lcf f, long long k, long long size );

//    long long test2();

private:

    t_lcf apply_action( const t_lcf & a, const t_action & action, long long size );

    t_lcf calc_lcf( const t_lcf & a, const t_lcf & b, long long size );

    long long apply( const t_action & action, long long pos, long long size );

    t_suffels prepare_input( const std::string & fileName );

private:

    std::shared_ptr< ShuffleMovements > m_shuffle;

};

