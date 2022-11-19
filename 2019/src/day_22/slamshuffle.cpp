#include "slamshuffle.h"

#include <iostream>
#include <unordered_map>
#include <set>

#include "common/file_reader.h"
#include "common/common.h"


const static std::string DEAL_INTO_STR = "deal into new stack";
const static std::string DEAL_WITH_STR = "deal with increment";
const static std::string CUT_STR       = "cut";

class ShuffleTask1 : public ShuffleMovements
{
public:
    // deal into new stack,
    virtual long long new_stack ( long long pos, long long size );

    // To cut N cards
    virtual long long cut       ( long long pos, long long C, long long size );

    // To deal with increment N
    virtual long long increment ( long long pos, long long C, long long size );
};


class ShuffleTask2 : public ShuffleMovements
{
public:
    // deal into new stack,
    virtual long long new_stack ( long long pos, long long size );

    // To cut N cards
    virtual long long cut       ( long long pos, long long C, long long size );

    // To deal with increment N
    virtual long long increment ( long long pos, long long C, long long size );
};


enum class ShuffleType
{
      TASK_1
    , TASK_2
};


static std::shared_ptr< ShuffleMovements > get_shuffle_movements( ShuffleType type )
{
    switch( type )
    {
        case ShuffleType::TASK_1 : return std::make_shared< ShuffleTask1 >();

        case ShuffleType::TASK_2 : return std::make_shared< ShuffleTask2 >();
    }

    throw "The type is not supported";
}


// ---------------------- SlamShuffle ------------------------------------------

SlamShuffle::t_suffels SlamShuffle::prepare_input( const std::string & fileName )
{
  t_suffels res;

  std::vector< std::string > lines = FileReader::read_file( fileName );

  for ( const auto & _line : lines )
  {
    // deal into new stack
    if ( _line.find( DEAL_INTO_STR ) != std::string::npos )
    {
      res.emplace_back( Shuffels::DEAL_INTO, 0 );
    }
    // deal with increment 7
    else if ( _line.find( DEAL_WITH_STR ) != std::string::npos )
    {
      res.emplace_back( Shuffels::DEAL_WITH, std::stoll( _line.substr( DEAL_WITH_STR.size() ) ) );
    }
    // cut -2
    else if ( _line.find( CUT_STR ) != std::string::npos )
    {
      res.emplace_back( Shuffels::CUT, std::stoll( _line.substr( CUT_STR.size() ) ) );
    }
  }

  //for ( const auto _el : res )
  //{
  //  std::cout << "Type: " << static_cast<int>( _el.first ) << " val : " << _el.second << "\n";
  //}

  return res;
}

long long SlamShuffle::task_1( const std::string & fileName, long long initPos, long long size )
{
    m_shuffle = get_shuffle_movements( ShuffleType::TASK_1 );

    t_suffels input = prepare_input( fileName );

//    long long pos = initPos;

//    for ( const auto & _action : input )
//        pos = apply( _action, pos, size );

    t_lcf modificatioin { 1, 0 };

    for ( const auto & _action : input )
        modificatioin = apply_action( modificatioin, _action, size );

    const long long pos = ( initPos * modificatioin.first + modificatioin.second ) % size;

    return pos;
}

long long SlamShuffle::task_2(const std::string &fileName, long long initPos, long long size)
{
//    m_shuffle = get_shuffle_movements( ShuffleType::TASK_2 );

//    t_suffels input = prepare_input( fileName );

//    std::reverse( input.begin(), input.end() );

//    long long pos = initPos;
//    std::set< long long > oldPositions;

//    for ( long long i = 0; i < 101741582076661; ++i )
//    {
////        long long startPos = pos;

//        if ( oldPositions.find( pos ) != oldPositions.end() )
//            std::cout << "Cycle\n";

//        oldPositions.insert( pos );

//        for ( const auto & _action : input )
//            pos = apply( _action, pos, size );

////        std::cout << "Pos: " << startPos << " -> " << pos << "\n";
//    }

//    return pos;

    m_shuffle = get_shuffle_movements( ShuffleType::TASK_1 );

    t_suffels input = prepare_input( fileName );

    t_lcf modificatioin { 1, 0 };

    for ( const auto & _action : input )
        modificatioin = apply_action( modificatioin, _action, size );

    std::cout << "a: " << modificatioin.first << " b: " << modificatioin.second << std::endl;

    modificatioin = pow_lcf( modificatioin, 101741582076661ll, size );

    std::cout << "a: " << modificatioin.first << " b: " << modificatioin.second << std::endl;

//    test( initPos - modificatioin.second, modificatioin.first, size );

    return 0;

}

long long SlamShuffle::test( long long initVal, long long a, long long size )
{
    long long sum = initVal;
    long long k = 0;

    while ( sum % a != 0 )
    {
        sum += size;
        ++k;
    }

    std::cout << "sum: " << sum << " k: " << k << " res: " << sum / a << "\n";

    return sum;
}

SlamShuffle::t_lcf SlamShuffle::pow_lcf( t_lcf f, long long k, long long size )
{
    t_lcf g ( 1, 0 );

    while ( k > 0 )
    {
        if ( k % 2 == 1 )
            g = calc_lcf( g, f, size );

        k = k / 2;

        f = calc_lcf( f, f, size );
    }

    return g;

//    function pow_compose(f: lcf, k: int64) → lcf:
//        g := lcf(1, 0)
//        while k > 0:
//            if k is odd:
//                g := compose(g, f)
//            k := ⌊k/2⌋
//            f := compose(f, f)
//        return g
}

//long long SlamShuffle::test2()
//{
//    const long long inverse = 75713548004544ll;

//    const long long res = ( ( 119315717514047ll + 2020 - 5113249733551 ) * inverse ) % 119315717514047;

//    std::cout << "Result task 2 : " << res << "\n";
//}

SlamShuffle::t_lcf SlamShuffle::apply_action( const t_lcf & a, const t_action & action, long long size )
{
    switch ( action.first )
    {
        case Shuffels::CUT       : return calc_lcf( a, t_lcf( 1, size - action.second ), size );

        case Shuffels::DEAL_INTO : return calc_lcf( a, t_lcf( -1, size - 1 ), size );

        case Shuffels::DEAL_WITH : return calc_lcf( a, t_lcf( action.second, 0 ), size );
    }

    throw "Wrong Shuffle";
}

SlamShuffle::t_lcf SlamShuffle::calc_lcf( const t_lcf & a, const t_lcf & b, long long size )
{
    t_lcf result;

//    std::cout << "First: " << a.first << " * " << b.first << " = " << ( a.first * b.first ) << "\n";
//    std::cout << "Second: " << a.second << " * " << b.first << " + " << b.second << " = " << ( a.second * b.first + b.second ) << "\n";

    result.first  = ( a.first * b.first ) % size;
    result.second = ( a.second * b.first + b.second ) % size;

    return result;
}

long long SlamShuffle::apply( const std::pair< Shuffels, long long > & action, long long pos, long long size )
{
    switch ( action.first )
    {
        case Shuffels::CUT       : return m_shuffle->cut( pos, action.second, size );

        case Shuffels::DEAL_INTO : return m_shuffle->new_stack( pos, size );

        case Shuffels::DEAL_WITH : return m_shuffle->increment( pos, action.second, size );
    }

    throw "Wrong Shuffle";
}


// -------------------- Shuffle Movements -----------------------------

long long ShuffleTask1::new_stack( long long pos, long long size )
{
    return size - 1 - pos;
}

long long ShuffleTask1::cut( long long pos, long long C, long long size )
{
    return ( size - C + pos ) % size;
}

long long ShuffleTask1::increment( long long pos, long long C, long long size )
{
    return ( pos * C ) % size;
}



long long ShuffleTask2::new_stack(long long pos, long long size)
{
    return size - 1 - pos;
}

long long ShuffleTask2::cut(long long pos, long long C, long long size)
{
    return ( size + pos + C ) % size;
}

long long ShuffleTask2::increment(long long pos, long long C, long long size)
{
    long long n { 0 };

    while ( ( size * n + pos ) % C != 0 )
        ++n;

    return ( size * n + pos ) / C;
}
