
#include <limits>
#include <queue>
#include <map>
#include <iterator>

#include "task_22.h"


Task22::Task22( unsigned long i_depth, const t_position & i_target_pos, size_t max_x, size_t max_y )
    : depth{ i_depth }
    , target_pos{ i_target_pos }
{

    fill_field( max_x, max_y );


}

void Task22::fill_field(std::size_t max_x, std::size_t max_y)
{
    field_calc = t_field_calc( max_x, std::vector<long>( max_y, 0 ) );
    field_score = t_field_score( max_x, std::vector<int>( max_y, 0 ) );

    for ( std::size_t i = 0; i < max_x; ++i )
    {
        for ( std::size_t j = 0; j < max_y; ++j )
        {
            if ( i == 0 && j == 0 )
                field_calc[ i ][ j ] = depth % 20183;
            else if ( i == target_pos.first && j == target_pos.second )
                field_calc[ i ][ j ] = depth % 20183;
            else if ( j == 0 )
                field_calc[ i ][ j ] = ( i * 16807 + depth ) % 20183;
            else if ( i == 0 )
                field_calc[ i ][ j ] = ( j * 48271 + depth ) % 20183;
            else
                field_calc[ i ][ j ] = ( field_calc[ i - 1][ j ] * field_calc[ i ][ j - 1 ] + depth ) % 20183;

            field_score[ i ][ j ] = field_calc[ i ][ j ] % 3;
        }
    }
}

long Task22::get_score( std::size_t max_x, std::size_t max_y )
{
    long res = 0;

    for ( std::size_t i = 0; i <= max_x; ++i )
        for ( std::size_t j = 0; j <= max_y; ++j )
            res += field_score[ i ][ j ];

    return res;
}

#include <iostream>
#include <iomanip>

 std::map<Task22::NextHop::TOOL_TYPES, char> TOOLS_TO_CHARS = {  { Task22::NextHop::TOOL_TYPES::T, 'T' }
                                                               , { Task22::NextHop::TOOL_TYPES::G, 'G' } 
                                                               , { Task22::NextHop::TOOL_TYPES::N, 'N' } };

 std::map<Task22::NextHop::TOOL_TYPES, size_t> TOOLS_TO_CHARS_IDX = {  { Task22::NextHop::TOOL_TYPES::T, 0 }
                                                                     , { Task22::NextHop::TOOL_TYPES::G, 1 }
                                                                     , { Task22::NextHop::TOOL_TYPES::N, 2 } };

 bool is_tool_fir_for_place( size_t i_tool, int place )
 {
     auto tool = static_cast<Task22::NextHop::TOOL_TYPES>( i_tool );

     switch ( tool )
     {
     case Task22::NextHop::TOOL_TYPES::T:
         return place == 0 || place == 2;
     case Task22::NextHop::TOOL_TYPES::G:
         return place == 0 || place == 1;
     case Task22::NextHop::TOOL_TYPES::N:
         return place == 1 || place == 2;
     }

     throw std::string( "Tools not available!" );
 }

int Task22::get_min_path()
{
    auto min_path = std::vector<t_field_score>(3, t_field_score( field_score.size(), std::vector<int>( field_score[0].size(), std::numeric_limits<int>::max() ) ) ); // std::numeric_limits<int>::max() )
    auto field_tool = std::vector<std::vector<char>>( field_score.size(), std::vector<char>( field_score[ 0 ].size(), 'O' ) );

    min_path[ 0 ][ 0 ][ 0 ] = 0;
    min_path[ 1 ][ 0 ][ 0 ] = 7;
    min_path[ 2 ][ 0 ][ 0 ] = 7;

    auto priorityQueueComparator = []( const auto &lhs, const auto &rhs ){ return lhs.length > rhs.length; };
    std::priority_queue < NextHop, std::vector<NextHop>, decltype(priorityQueueComparator) > prQueue( priorityQueueComparator );

    prQueue.push( NextHop( 0, { 0, 0 }, { NextHop::TOOL_TYPES::T }, 0, 0 ) );

    while ( !prQueue.empty() )
    {
        auto currHop = prQueue.top();
        prQueue.pop();

        // Try to change tools
        for ( size_t i = 0; i < 3; ++i )
        {
            if ( min_path[ i ][ currHop.pos.first ][ currHop.pos.second ] > currHop.length + 7 )
            {
                // Is tool not fit for a place
                if ( !is_tool_fir_for_place( i, field_score[ currHop.pos.first ][ currHop.pos.second ] ) )
                    continue;
                
                min_path[ i ][ currHop.pos.first ][ currHop.pos.second ] = currHop.length + 7;
                prQueue.push( NextHop( currHop.length + 7, currHop.pos, { static_cast<NextHop::TOOL_TYPES>( i ) }, currHop.switchTools + 7, currHop.movement ) );
            }
        }


        if ( min_path[ TOOLS_TO_CHARS_IDX[ currHop.tools ] ][ currHop.pos.first ][ currHop.pos.second ] < currHop.length )
            continue;

        if ( currHop.pos.first == target_pos.first && currHop.pos.second == target_pos.second )
            std::cout << "Switch : " << currHop.switchTools << " Move : " << currHop.movement << " Toolset : " << static_cast<int>( currHop.tools ) << std::endl;

        // Get neighbor cells
        std::vector<t_position> neighborCells = get_neighbor_cells( currHop.pos );

        // Calc for neighbor cells min length
        std::vector<NextHop> nextHops = get_next_hops( currHop, neighborCells );

        // Update min path
        for ( const auto & hop : nextHops )
        {
            // Change for current tool
            if ( min_path[ TOOLS_TO_CHARS_IDX[ hop.tools ] ][ hop.pos.first ][ hop.pos.second ] > hop.length )
            {
                min_path[ TOOLS_TO_CHARS_IDX[ hop.tools ] ][ hop.pos.first ][ hop.pos.second ] = hop.length;
                prQueue.push( hop );
            }
        }
    }

    return min_path[ 0 ][ target_pos.first ][ target_pos.second ];
}

std::vector<Task22::t_position> Task22::get_neighbor_cells( const t_position & currentPos )
{
    std::vector<std::pair<int, int>> searchMatrix;
    std::vector<t_position> neighborCells;


    if ( currentPos.first > 0 )
        searchMatrix.emplace_back(-1, 0);
    if ( currentPos.first + 1 < field_score.size() )
        searchMatrix.emplace_back( 1, 0 );
    if ( currentPos.second > 0 )
        searchMatrix.emplace_back( 0,-1 );
    if ( currentPos.second + 1 < field_score[0].size() )
        searchMatrix.emplace_back( 0, 1 );

    for ( const auto & offset : searchMatrix )
    {
        neighborCells.emplace_back( currentPos.first + offset.first, currentPos.second + offset.second );
    }

    return neighborCells;
}

std::vector<Task22::NextHop> Task22::get_next_hops( const NextHop & currentHop, const std::vector<t_position>& neighborsPos )
{
    std::vector<NextHop> neighborsHops;

    auto comparePairs = []( const auto & lhs, const auto & rhs )
    { 
        if ( lhs.first == rhs.first ) return lhs.second < rhs.second; 
        else return lhs.first < rhs.first; 
    };

    // 0 - G, T (rocky)
    // 1 - G, N (wet)
    // 2 - T, N (narrow)
    std::map<std::pair<int, int>, NextHop::TOOL_TYPES, decltype( comparePairs )> NEXT_TOOL( comparePairs );
    NEXT_TOOL = {  { { 0, 1 }, NextHop::TOOL_TYPES::G }
                 , { { 0, 2 }, NextHop::TOOL_TYPES::T } 
                 , { { 1, 0 }, NextHop::TOOL_TYPES::G } 
                 , { { 1, 2 }, NextHop::TOOL_TYPES::N } 
                 , { { 2, 0 }, NextHop::TOOL_TYPES::T } 
                 , { { 2, 1 }, NextHop::TOOL_TYPES::N } };

    for ( const auto & neighPos : neighborsPos )
    {
        // Calc min way to next hop
        if ( field_score[ currentHop.pos.first ][ currentHop.pos.second ] != field_score[ neighPos.first ][ neighPos.second ] )
        {
            // Is fit for tool
            auto currentCellType = field_score[ currentHop.pos.first ][ currentHop.pos.second ];
            auto nextCellType = field_score[ neighPos.first ][ neighPos.second ];

            if ( currentHop.tools == NEXT_TOOL[ std::make_pair( currentCellType, nextCellType )] )
            {
                // Current tool fit to next type place
                neighborsHops.push_back( NextHop( currentHop.length + 1, neighPos, currentHop.tools, currentHop.switchTools, currentHop.movement + 1 ) );
            }
            else
            {
                // Need to change tools
                neighborsHops.push_back( NextHop( currentHop.length + 1 + 7, neighPos, NEXT_TOOL[ std::make_pair( currentCellType, nextCellType ) ], currentHop.switchTools + 7, currentHop.movement + 1 ) );
            }
        }
        else
        {
            // Next place the same type
            neighborsHops.push_back( NextHop( currentHop.length + 1, neighPos, currentHop.tools, currentHop.switchTools, currentHop.movement + 1 ) );
        }
    }

    return neighborsHops;
}

void Task22::set_score( std::vector<std::string> initScore )
{
    field_score = t_field_score( initScore[0].size(), std::vector<int>( initScore.size(), 0 ) );

    for ( size_t i = 0; i < initScore.size(); ++i )
    {
        for ( size_t j = 0; j < initScore[ 0 ].size(); ++j )
        {
            field_score[ j ][ i ] = initScore[ i ][ j ] - '0';
        }
    }

    for ( size_t j = 0; j < field_score[ 0 ].size(); ++j )
    {
        for ( size_t i = 0; i < field_score.size(); ++i )
        {
            std::cout << field_score[ i ][ j ] << ' ';
        }
        std::cout << std::endl;
    }
}
