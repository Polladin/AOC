
#include "guard_gallivant.h"

#include <vector>
#include <set>
#include <algorithm>

#include "common/file_reader.h"
#include "common/common.h"

#define FOR(a,b) for(int a {0}; a<static_cast<int>(b); ++a)

namespace
{

enum class Direction
{
    UP, RIGHT, DOWN, LEFT,

    LAST_ELEM
};


struct Cell
{
    char val;
    std::set< Direction > directions;
};

using Field = std::vector< std::string >;
using FieldExtra = std::vector< std::vector< Cell > >;

int get_x_size( const Field & field )
{
    return field[ 0 ].size();
}

int get_y_size( const Field & field )
{
    return field.size();
}

char get_field_val( const Field & field, size_t x, size_t y )
{
    return field[ y ][ x ];
}

void set_field_val( char value, Field & field, size_t x, size_t y )
{
    field[ y ][ x ] = value;
}

FieldExtra create_field_extra( const Field & field )
{
    FieldExtra result;

    result.resize( get_y_size( field ) );

    FOR ( yIndex, get_y_size( field ) )
    {
        result[ yIndex ].resize( field[ yIndex ].size() );

        FOR ( xIndex, get_x_size( field ) )
        {
            result[ yIndex ][ xIndex ].val = field[ yIndex ][ xIndex ];
        }
    }

    return result;
}

t_coord extract_start_position( Field & field )
{
    FOR( yIndex, get_y_size( field ) )
    {
        FOR( xIndex, get_x_size( field ) )
        {
            if ( get_field_val( field, xIndex, yIndex ) == '^' )
            {
                set_field_val( 'X', field, xIndex, yIndex );
                return { xIndex, yIndex };
            }
        }
    }

    throw "Start position not found";
}

t_coord get_next_position( const t_coord & position, Direction direction )
{
    switch (direction)
    {
    case Direction::UP:
        return { position.x, position.y - 1 };

    case Direction::DOWN:
        return { position.x, position.y + 1 };

    case Direction::RIGHT:
        return { position.x + 1, position.y };

    case Direction::LEFT:
        return { position.x - 1, position.y };
    }

    throw "Unknown direction type";
}

Direction get_next_direction( Direction direction )
{
    int nextDirectionInt = static_cast< int >( direction ) + 1;
    static const int lastDirectionInt = static_cast< int >( Direction::LAST_ELEM );

    return  static_cast< Direction >( nextDirectionInt % lastDirectionInt );
}

bool is_out_of_map( const Field & field, t_coord position )
{
    return     position.x < 0
            || position.y < 0
            || position.x >= get_x_size( field )
            || position.y >= get_y_size( field );
}

bool is_out_of_map( const FieldExtra & field, t_coord position )
{
    return     position.x < 0
            || position.y < 0
            || position.x >= static_cast< int >( field[ 0 ].size() )
            || position.y >= static_cast< int >( field.size() );
}

void walk_through_map( Field & field, t_coord position, Direction direction )
{
    t_coord nextPposition = get_next_position( position, direction );

    for (; !is_out_of_map( field, nextPposition ); nextPposition = get_next_position( position, direction ) )
    {
        if ( get_field_val( field, nextPposition.x, nextPposition.y ) == '#' )
        {
            direction = get_next_direction( direction );
            continue;
        }

        set_field_val( 'X', field, nextPposition.x, nextPposition.y );

        position = nextPposition;
    }
}

std::vector< t_coord > get_positions_for_obstacles( const Field & field )
{
    std::vector< t_coord > result;

    FOR( yIndex, get_y_size( field ) )
    {
        FOR( xIndex, get_x_size( field ) )
        {
            if ( get_field_val( field, xIndex, yIndex ) == 'X' )
            {
                result.emplace_back( xIndex, yIndex );
            }
        }
    }

    return result;
}

bool is_loop( FieldExtra & field, t_coord position, Direction direction )
{
    t_coord nextPposition = get_next_position( position, direction );

    for (; !is_out_of_map( field, nextPposition ); nextPposition = get_next_position( position, direction ) )
    {
        if ( field[ nextPposition.y ][ nextPposition.x ].val  == '#' )
        {
            direction = get_next_direction( direction );
            continue;
        }

        field[ nextPposition.y ][ nextPposition.x ].val = 'X';
        auto isDirectionInserted = field[ nextPposition.y ][ nextPposition.x ].directions.insert( direction );

        if ( !isDirectionInserted.second )
        {
            return true;
        }

        position = nextPposition;
    }

    return false;
}

long long get_visited_positions( const Field & field )
{
    long long result { 0 };

    FOR( yIndex, get_y_size( field ) )
    {
        FOR( xIndex, get_x_size( field ) )
        {
            result += ( get_field_val( field, xIndex, yIndex ) == 'X' ) ? 1 : 0;
        }
    }

    return result;
}

void remove_position( std::vector< t_coord > & positions, const t_coord & positionToRemove )
{
    FOR ( idx, positions.size() )
    {
        if (    positions[ idx ].x == positionToRemove.x
             && positions[ idx ].y == positionToRemove.y )
        {
            positions.erase( positions.begin() + idx );
            break;
        }
    }
}

}// namespace

long long GuardGallivant::task_1( const std::string & filename )
{
    Field field = FileReader::read_file( filename );

    t_coord startPosition = extract_start_position( field );

    walk_through_map( field, startPosition, Direction::UP );

    return get_visited_positions( field );
}

long long GuardGallivant::task_2( const std::string & filename )
{
    Field field = FileReader::read_file( filename );
    FieldExtra fieldExtra = create_field_extra( field );

    t_coord startPosition = extract_start_position( field );

    walk_through_map( field, startPosition, Direction::UP );

    std::vector< t_coord > obstaclePositions = get_positions_for_obstacles( field );

    remove_position( obstaclePositions, startPosition );

    long long result { 0 };

    for ( const t_coord & position : obstaclePositions )
    {
        FieldExtra fieldWithObstacle { fieldExtra };
        fieldWithObstacle[ position.y ][ position.x ].val = '#';

        result += is_loop( fieldWithObstacle, startPosition, Direction::UP ) ? 1 : 0;
    }

    return result;
}
