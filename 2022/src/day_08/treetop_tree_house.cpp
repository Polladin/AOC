#include "treetop_tree_house.h"

#include <vector>
#include <set>

#include "common/file_reader.h"


enum class GeneratorType
{
      LEFT
    , RIGHT
    , TOP
    , BOTTOM
};

std::set< GeneratorType > allDirections { GeneratorType::LEFT, GeneratorType::RIGHT, GeneratorType::TOP, GeneratorType::BOTTOM };


auto get_generator( bool isRowChanges, int adder, std::size_t stopVal )
{
    return [adder, stopVal, isRowChanges]( std::size_t & row, std::size_t & col )
    {
        std::size_t & idx = isRowChanges ? row : col;

        if ( idx == stopVal )
            return false;

        idx += adder;

        return true;
    };
}

auto get_generator( GeneratorType type, std::size_t maxRow, std::size_t maxCol )
{
    switch ( type )
    {
    case GeneratorType::LEFT   : return get_generator( /* isRowChanges */ false, /* adder */ -1, /* stopVal */ 0          );
    case GeneratorType::RIGHT  : return get_generator( /* isRowChanges */ false, /* adder */  1, /* stopVal */ maxCol - 1 );
    case GeneratorType::TOP    : return get_generator( /* isRowChanges */ true , /* adder */ -1, /* stopVal */ 0          );
    case GeneratorType::BOTTOM : return get_generator( /* isRowChanges */ true , /* adder */  1, /* stopVal */ maxRow - 1 );
    }

    throw "Wrong Generator Type!";
}

bool isObservable( std::size_t row, std::size_t col, const std::vector< std::string > & field, auto generator )
{
    const char height = field[ row ][ col ];

    while( generator( row, col ) )
        if ( field[ row ][ col ] >= height )
            return false;

    return true;
}

bool isObservable( std::size_t row, std::size_t col, const std::vector< std::string > & field )
{
    bool res = false;

    const std::size_t maxRow = field.size();
    const std::size_t maxCol = field[ 0 ].size();

    for ( auto _direction : allDirections )
        res = res || isObservable( row, col, field, get_generator( _direction, maxRow, maxCol ) );

    return res;
}

long long getDistance( std::size_t sRow, std::size_t sCol, const std::vector< std::string > & field, auto generator )
{
    const char height = field[ sRow ][ sCol ];

    std::size_t row = sRow;
    std::size_t col = sCol;

    while( generator( row, col ) )
        if ( field[ row ][ col ] >= height )
            break;

    std::size_t diffRow = sRow > row ? sRow - row : row - sRow;
    std::size_t diffCol = sCol > col ? sCol - col : col - sCol;

    return diffRow + diffCol;
}

long long getDistance( std::size_t row, std::size_t col, const std::vector< std::string > & field )
{
    long long res { 1 };

    const std::size_t maxRow = field.size();
    const std::size_t maxCol = field[ 0 ].size();

    for ( auto _direction : allDirections )
        res *= getDistance( row, col, field, get_generator( _direction, maxRow, maxCol ) );

    return res;
}

long long TreetopTreeHouse::task_1( const std::string & filename )
{
    std::vector< std::string > field = FileReader::read_file( filename );

    long long res = field[ 0 ].size() * 2 + ( field.size() - 2 ) * 2;

    for ( std::size_t row = 1; row + 1 < field.size(); ++row )
        for ( std::size_t col = 1; col + 1 < field[ row ].size(); ++col )
            res += ( isObservable( row, col, field ) ? 1 : 0 );

    return res;
}

long long TreetopTreeHouse::task_2( const std::string & filename )
{
    std::vector< std::string > field = FileReader::read_file( filename );

    long long res { 0 };

    for ( std::size_t row = 0; row < field.size(); ++row )
    {
        for ( std::size_t col = 0; col < field[ row ].size(); ++col )
        {
            res = std::max( res, getDistance( row, col, field ) );
        }
    }

    return res;
}
