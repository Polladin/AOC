
#include "pipe_maze.h"

#include "common/file_reader.h"

#include <queue>
#include <set>
#include <map>
#include <iostream>


using Field = std::vector< std::string >;

struct Point
{
    std::size_t row;
    std::size_t col;
};

struct PointLessComparator
{
    bool operator() ( const Point & lhs, const Point & rhs ) const
    {
        return std::tie( lhs.row, lhs.col ) < std::tie( rhs.row, rhs.col );
    }
};


Field prepare_input( const std::string & filename )
{
    // Read the file
    std::vector< std::string > sInput = FileReader::read_file( filename );

    Field result;

    for( const auto & _line : sInput )
    {
        if( !_line.empty() )
        {
            result.push_back( _line );
        }
    }

    return result;
}

Point get_start_point( const Field & field )
{
    for( std::size_t row = 0; row < field.size(); ++row )
    {
        for( std::size_t col = 0; col < field[ row ].size(); ++col )
        {
            if( field[ row ][ col ] == 'S' )
            {
                return { row, col };
            }
        }
    }

    std::abort();
}

struct Node
{
    Point point;
    long long dist;
};

enum class Direction
{
      LEFT
    , RIGHT
    , UP
    , DOWN
};

const std::vector< Direction > ALL_DIRECTIONS = { Direction::LEFT, Direction::RIGHT, Direction::UP, Direction::DOWN };

std::map< Direction, const std::pair< int, int > > OFFSETS =
{
      { Direction::LEFT , { /*row*/  0, /*col*/ -1 } }
    , { Direction::RIGHT, { /*row*/  0, /*col*/  1 } }
    , { Direction::UP   , { /*row*/ -1, /*col*/  0 } }
    , { Direction::DOWN , { /*row*/  1, /*col*/  0 } }
};

bool isSuiteable(char original, char target, const Direction direction)
{
//    | is a vertical pipe connecting north and south.
//    - is a horizontal pipe connecting east and west.
//    L is a 90-degree bend connecting north and east.
//    J is a 90-degree bend connecting north and west.
//    7 is a 90-degree bend connecting south and west.
//    F is a 90-degree bend connecting south and east.
//    . is ground; there is no pipe in this tile.
//    S is the starting position of the animal; there is a pipe on this

    static const std::map< Direction, std::string > NOT_SUITABLE_ORIGIN =
    {
        { Direction::LEFT , "|LF" }
      , { Direction::RIGHT, "|J7" }
      , { Direction::UP   , "-7F" }
      , { Direction::DOWN , "-LJ" }
    };

    static const std::map< Direction, std::string > SUITABLE_TARGET =
    {
        { Direction::LEFT , "-LF" }
      , { Direction::RIGHT, "-J7" }
      , { Direction::UP   , "|7F" }
      , { Direction::DOWN , "|LJ" }
    };

    if ( target == '.' )
    {
        return false;
    }

    if ( NOT_SUITABLE_ORIGIN.find( direction )->second.find( original ) != std::string::npos )
    {
        return false;
    }

    if ( SUITABLE_TARGET.find( direction )->second.find( target ) == std::string::npos )
    {
        return false;
    }

    return true;
}

std::vector< Point > get_next_steps( const Point & point, const Field & field, const std::set< Point, PointLessComparator > & visitedNodes)
{
    const std::vector< std::pair< int, int > > offsets = { {-1, 0}, {-1, 1}, {0, -1}, {0, 1} };

    std::vector< Point > result;

    for( const auto & _direction : ALL_DIRECTIONS )
    {
        const int targetRow = point.row + OFFSETS.find( _direction )->second.first;
        const int targetCol = point.col + OFFSETS.find( _direction )->second.second;

        if (    targetRow >= 0
             && targetCol >= 0
             && targetRow < static_cast< int >( field.size() )
             && targetCol < static_cast< int >( field[ targetRow ].size() ) )
        {
            Point targetPoint { static_cast<size_t>( targetRow )
                              , static_cast<size_t>( targetCol ) };

            if ( visitedNodes.count( targetPoint ) > 0 )
            {
                continue;
            }

            if ( isSuiteable(  field[ point.row ][ point.col ]
                             , field[ targetRow ][ targetCol ]
                             , _direction ) )
            {
                result.emplace_back( targetRow, targetCol );
            }
        }
    }

    return result;
}

long long get_max_dist( const Field & field, std::set< Point, PointLessComparator > & visitedNodes )
{
    long long maxDist { 0 };

    std::queue< Node > nodes;

    nodes.emplace( get_start_point( field ), maxDist );
    visitedNodes.insert( nodes.front().point );

    while( !nodes.empty() )
    {
        Node currentNode = nodes.front();
        nodes.pop();

        maxDist = std::max( currentNode.dist, maxDist );

        std::vector< Point > nextSteps = get_next_steps( currentNode.point, field, visitedNodes );

        for ( const Point & _step : nextSteps )
        {
            nodes.emplace( _step, currentNode.dist + 1 );
            visitedNodes.insert( _step );
        }
    }

    return maxDist;
}

long long PipeMaze::task_1( const std::string & filename )
{
    Field field = prepare_input( filename );

    std::set< Point, PointLessComparator > visitedNodes;

    return get_max_dist( field, visitedNodes );
}

Field get_field_with_loop(const Field & originField, const std::set< Point, PointLessComparator >& visitedNodes)
{
    Field field = std::vector< std::string > ( originField.size(), std::string( originField[ 0 ].size(), '.') );

    for ( const auto & _visitedNode : visitedNodes )
    {
        field[ _visitedNode.row ][ _visitedNode.col ] = originField[ _visitedNode.row ][ _visitedNode.col ];
    }

    return field;
}

long long PipeMaze::task_2( const std::string & filename )
{
    Field field = prepare_input( filename );
    std::set< Point, PointLessComparator > visitedNodes;

    get_max_dist( field, visitedNodes );

    Field fieldWithLoop = get_field_with_loop( field, visitedNodes );

    for ( const auto & _rowStr : fieldWithLoop )
    {
        std::cout << _rowStr << std::endl;
    }

    return 0;
}
