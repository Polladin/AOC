
#include "resonant_collinearity.h"

#include <vector>
#include <map>
#include <set>

#include "common/file_reader.h"
#include "common/common.h"

#define FOR(a,b) for(size_t a {0}; a<b; ++a)


namespace
{
using Field = std::vector< std::string >;
using AntennasMap = std::map< char, std::vector< t_coord > >;
using Antinides = std::set< t_coord, PointCmp >;

AntennasMap get_list_of_antennas( const Field & field )
{
    AntennasMap result;

    FOR( yIndex, field.size() )
        FOR( xIndex, field[ yIndex ].size() )
            if ( field[ yIndex ][ xIndex ] != '.' )
                result[ field[ yIndex ][ xIndex ] ].emplace_back( xIndex, yIndex );

    return result;
}

void add_antinodes_step( const t_coord & lhsNode, const t_coord & rhsNode, Antinides & antinodes )
{
    antinodes.insert( t_coord( 2 * lhsNode.x - rhsNode.x, 2 * lhsNode.y - rhsNode.y ) );
    antinodes.insert( t_coord( 2 * rhsNode.x - lhsNode.x, 2 * rhsNode.y - lhsNode.y ) );
}

void add_antinodes( const std::vector< t_coord > & coords, Antinides & antinodes )
{
    for ( size_t lhsIdx = 0; lhsIdx < coords.size(); ++lhsIdx )
        for ( size_t rhsIdx = lhsIdx + 1; rhsIdx < coords.size(); ++rhsIdx )
            add_antinodes_step( coords[ lhsIdx ], coords[ rhsIdx ], antinodes );
}

bool is_valid( const t_coord & node, const Field & field )
{
    const int maxX = field[ 0 ].size();
    const int maxY = field.size();

    return    node.x >= 0 && node.y >= 0
           && node.x < maxX && node.y < maxY;
}

void validate_antinodes( Antinides & antinodes, const Field & field )
{
    for (auto antinodeIt = antinodes.begin(); antinodeIt != antinodes.end();)
    {
        if ( !is_valid( *antinodeIt, field ))
        {
            antinodeIt = antinodes.erase(antinodeIt);
        }
        else
        {
            ++antinodeIt;
        }
    }
}

void add_antinodes_step_2( const t_coord & lhsNode, const t_coord & rhsNode, Antinides & antinodes, const Field & field )
{
    antinodes.insert( lhsNode );
    antinodes.insert( rhsNode );

    t_coord diffNode { lhsNode.x - rhsNode.x, lhsNode.y - rhsNode.y };

    for ( t_coord nextNode = lhsNode; is_valid( nextNode, field ); nextNode = nextNode + diffNode )
    {
         antinodes.insert( nextNode );
    }

    for ( t_coord nextNode = lhsNode - diffNode; is_valid( nextNode, field ); nextNode = nextNode - diffNode )
    {
         antinodes.insert( nextNode );
    }
}

void add_antinodes_2( const std::vector< t_coord > & coords, Antinides & antinodes, const Field & field )
{
    for ( size_t lhsIdx = 0; lhsIdx < coords.size(); ++lhsIdx )
        for ( size_t rhsIdx = lhsIdx + 1; rhsIdx < coords.size(); ++rhsIdx )
            add_antinodes_step_2( coords[ lhsIdx ], coords[ rhsIdx ], antinodes, field );
}

}// namespace

long long ResonantCollinearity::task_1(const std::string &filename)
{
    Field field = FileReader::read_file( filename );

    AntennasMap antennas = get_list_of_antennas( field );

    Antinides antinodes;

    for ( const auto & [ name_, coords_ ] : antennas )
    {
        add_antinodes( coords_, antinodes );
    }

    validate_antinodes( antinodes, field );

    return antinodes.size();
}

long long ResonantCollinearity::task_2( const std::string & filename )
{
    Field field = FileReader::read_file( filename );

    AntennasMap antennas = get_list_of_antennas( field );

    Antinides antinodes;

    for ( const auto & [ name_, coords_ ] : antennas )
    {
        add_antinodes_2( coords_, antinodes, field );
    }

    validate_antinodes( antinodes, field );

    return antinodes.size();
}
