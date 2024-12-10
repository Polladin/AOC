
#include "hoof_it.h"

#include <vector>
#include <queue>

#include "common/file_reader.h"
#include "common/common.h"

#define FOR(a,b) for(size_t a {0}; a<b; ++a)

namespace
{
using Field = std::vector< std::string >;
using Visited = std::vector< std::vector< bool > >;

std::vector< t_coord > get_start_positions( const Field & field )
{
    std::vector< t_coord > result;

    FOR( yIndex, field.size() )
        FOR( xIndex, field[ yIndex ].size())
            if ( field[ yIndex ][ xIndex ] == '0' )
                result.emplace_back( xIndex, yIndex );

    return result;
}

std::vector< t_coord > get_next_position( const t_coord & currentPos, const Field & field, const Visited & visited = {} )
{
    static const std::vector< t_coord > offsets { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };

    std::vector< t_coord > result;

    for ( const t_coord & offset_ : offsets )
    {
        const int yOffset_ = offset_.y;
        const int xOffset_ = offset_.x;

        if ( yOffset_ == 0 && xOffset_ == 0 )
        {
            continue;
        }

        const int xPos = currentPos.x + xOffset_;
        const int yPos = currentPos.y + yOffset_;

        if (    xPos < 0 || yPos < 0
             || xPos >= field[ 0 ].size() || yPos >= field.size() )
        {
            continue;
        }

        const int currentVal = field[ currentPos.y ][ currentPos.x ];

        if (    /*visited[ yPos ][ xPos ] == false*/
             /*&&*/ field[ yPos ][ xPos ] == currentVal + 1 )
        {
            result.emplace_back( xPos, yPos );
        }
    }

    return result;
}

int get_trail_score( const t_coord & startPos, const Field & field )
{
    Visited visited( field.size(), std::vector< bool >( field[ 0 ].size(), false ) );

    int result { 0 };
    std::queue< t_coord > queue;

    queue.push( startPos );
    visited[ startPos.y ][ startPos.x ] = true;

    while ( !queue.empty() )
    {
        t_coord currentPos = queue.front();
        queue.pop();

        if ( field[ currentPos.y ][ currentPos.x ] == '9' )
        {
            ++result;
            continue;
        }

        for ( const t_coord & nextPosition_ : get_next_position( currentPos, field, visited ) )
        {
            queue.push( nextPosition_ );
            visited[ nextPosition_.y ][ nextPosition_.x ] = true;
        }
    }

    return result;
}

struct QueueNode
{
    t_coord position;
    Visited visited;
};

}// namespace

long long HoofIt::task_1( const std::string & filename )
{
    Field field = FileReader::read_file( filename );

    std::vector< t_coord > startPositions = get_start_positions( field );

    int result { 0 };

    for ( const t_coord & startPos_ : startPositions )
    {
        result += get_trail_score( startPos_, field );
    }

    return result;
}

long long HoofIt::task_2( const std::string & filename )
{
    Field field = FileReader::read_file( filename );

    std::vector< t_coord > startPositions = get_start_positions( field );

    int result { 0 };

    for ( const t_coord & startPos_ : startPositions )
    {
        result += get_trail_score( startPos_, field );
    }

    return result;
}
