#include "rope_bridge.h"

#include <vector>
#include <set>

#include "common/file_reader.h"
#include "common/common.h"

struct Point
{
    int row;
    int col;
};

using t_movement = std::pair< char, int >;
using t_input = std::vector< t_movement >;

using t_point = std::pair< int, int >;


t_input prepare_input( const std::string & filename )
{
    std::vector< std::string > sInput = FileReader::read_file( filename );

    t_input res;

    for ( const auto & _line : sInput )
    {
        std::vector< std::string > params = common::split_line( _line, ' ' );

        res.emplace_back( params[ 0 ][ 0 ], std::stoi( params[ 1 ] ) );
    }

    return res;
}

void move_t( const Point & H, Point & T )
{
    if (    std::abs( H.col - T.col ) <= 1
         && std::abs( H.row - T.row ) <= 1 )
    {
        return;
    }

    if ( H.row != T.row )
        T.row = T.row + ( H.row < T.row ? -1 : 1 );

    if( H.col != T.col )
        T.col = T.col + ( H.col < T.col ? -1 : 1 );
}

void movement( const t_movement & move, std::vector< Point > & points, std::set< t_coord, PointCmp > & visitedPointsByT )
{
    Point & H = points[ 0 ];

    switch( move.first )
    {
    case 'R': H.col += 1; break;
    case 'L': H.col -= 1; break;
    case 'U': H.row += 1; break;
    case 'D': H.row -= 1; break;

    default: throw "Wrong input";
    }

    for ( std::size_t idx = 1; idx < points.size(); ++idx )
        move_t( points[ idx - 1 ], points[ idx ] );

    visitedPointsByT.insert( t_coord{ points.back().row, points.back().col } );
}

int calc( const t_input & input, int ropeLength )
{
    std::set< t_coord, PointCmp > visitedPointsByT;

    std::vector< Point > points( ropeLength, Point{ 0, 0 } );

    for ( const auto & _move : input )
        for ( int repite = 0; repite < _move.second; ++repite )
            movement( _move, points, visitedPointsByT );

    return visitedPointsByT.size();
}

long long RopeBridge::task_1( const std::string & filename )
{
    t_input input = prepare_input( filename );

    return calc( input, 2 );
}

long long RopeBridge::task_2( const std::string & filename )
{
    t_input input = prepare_input( filename );

    return calc( input, 10 );
}
