
#include "garden_groups.h"

#include <queue>

#include "common/file_reader.h"
#include "common/common.h"

#define FOR(a,b) for(int a {0}; a<b; ++a)

namespace
{

using Field = std::vector< std::string >;
using Visited = std::vector< std::vector< bool > >;

struct GardenPlot
{
    char name;
    int area { 0 };
    int fence { 0 };
};

int get_fence_count( const t_coord & pos, const Field & field )
{
    static const std::vector< t_coord > offsets = { { 1, 0 }, { -1, 0 }, { 0, 1 }, {  0, -1 } };

    int result { 0 };
    char currentPlotName = field[ pos.y ][ pos.x ];

    for ( const auto offset_ : offsets )
    {
        int xIndex { pos.x + offset_.x };
        int yIndex { pos.y + offset_.y };

        if ( xIndex < 0 || yIndex < 0
             || xIndex >= field[ 0 ].size() || yIndex >= field.size() )
        {
            ++result;
            continue;
        }

        if ( field[ pos.y + offset_.y ][ pos.x + offset_.x ] != currentPlotName )
        {
            ++result;
        }
    }

    return result;
}

bool is_same_plot(const t_coord & pos, char plotName, const Field & field)
{
    if ( pos.x < 0 || pos.y < 0
         || pos.x >= field[ 0 ].size() || pos.y >= field.size() )
    {
        return false;
    }

    return field[ pos.y ][ pos.x ] == plotName;
}

int get_fence_angles( const t_coord & currentPos, const t_coord & neighbourPos, const Field & field )
{
    const char currentPlotName = field[ currentPos.y ][ currentPos.x ];
    const bool isXLineCheck = currentPos.x == neighbourPos.x;

    int result { 0 };

    for ( const auto & offset_ : { -1, 1 } )
    {
        t_coord nextNeighbourPos { neighbourPos.x + (isXLineCheck ? offset_ : 0),
                                   neighbourPos.y + (!isXLineCheck ? offset_ : 0)};
        t_coord nextCurrentPos { currentPos.x + (isXLineCheck ? offset_ : 0),
                                 currentPos.y + (!isXLineCheck ? offset_ : 0)};

        const bool lineNotBroken =     is_same_plot( nextCurrentPos, currentPlotName, field )
                                   &&  !is_same_plot( nextNeighbourPos, currentPlotName, field );

        if ( !lineNotBroken )
        {
            ++result;
        }
    }

    return result;
}

int get_fence_count_2( const t_coord & pos, const Field & field )
{
    static const std::vector< t_coord > offsets = { { 1, 0 }, { -1, 0 }, { 0, 1 }, {  0, -1 } };

    int result { 0 };
    char currentPlotName = field[ pos.y ][ pos.x ];

    for ( const auto offset_ : offsets )
    {
        int xIndex { pos.x + offset_.x };
        int yIndex { pos.y + offset_.y };

        if ( is_same_plot( { xIndex, yIndex }, currentPlotName, field ) )
        {
            continue;
        }

        result += get_fence_angles( pos, { xIndex, yIndex }, field );
    }

    return result;
}

std::vector< t_coord > get_next_plots( const t_coord & pos, const Field & field, const Visited & visited )
{
    static const std::vector< t_coord > offsets = { { 1, 0 }, { -1, 0 }, { 0, 1 }, {  0, -1 } };

    std::vector< t_coord > result;
    char currentPlotName = field[ pos.y ][ pos.x ];

    for ( const auto offset_ : offsets )
    {
        int xIndex { pos.x + offset_.x };
        int yIndex { pos.y + offset_.y };

        if ( xIndex < 0 || yIndex < 0
             || xIndex >= field[ 0 ].size() || yIndex >= field.size() )
        {
            continue;
        }

        if (    !visited[ pos.y + offset_.y ][ pos.x + offset_.x ]
             && field[ pos.y + offset_.y ][ pos.x + offset_.x ] == currentPlotName )
        {
            result.emplace_back( pos.x + offset_.x, pos.y + offset_.y );
        }
    }

    return result;
}

GardenPlot get_plot_info( const t_coord & startPos, const Field & field, Visited & visited )
{
    std::queue< t_coord > queue;

    queue.push( startPos );
    visited[ startPos.y ][ startPos.x ] = true;

    GardenPlot gardenPlot;
    gardenPlot.name = field[ startPos.y ][ startPos.x ];

    while( !queue.empty() )
    {
        t_coord currentPos = queue.front();
        queue.pop();

        gardenPlot.fence += get_fence_count_2( currentPos, field );
        ++gardenPlot.area;

        for ( const t_coord & nextPos_ : get_next_plots( currentPos, field, visited ) )
        {
            queue.push( nextPos_ );
            visited[ nextPos_.y ][ nextPos_.x ] = true;
        }
    }

    return gardenPlot;
}

}// namespace

long long GardenGroups::task_1( const std::string & filename )
{
    Field field = FileReader::read_file( filename );

    std::vector< GardenPlot > gardenPlots;
    Visited visited ( field.size(), std::vector< bool >( field[ 0 ].size(), false ) );

    FOR( yIndex, field.size() )
    {
        FOR( xIndex, field[ 0 ].size() )
        {
            if ( !visited[ yIndex ][ xIndex ] )
            {
                gardenPlots.push_back( get_plot_info( { xIndex, yIndex }, field, visited ) );
            }
        }
    }

    long long result { 0 };

    for ( const auto & plotInfo_ : gardenPlots )
    {
//        std::cout << plotInfo_.name << " fence: " << plotInfo_.fence << " area: " << plotInfo_.area << "\n";
        result += plotInfo_.area * plotInfo_.fence / 2;
    }

    return result;
}

long long GardenGroups::task_2( const std::string & filename )
{

}
