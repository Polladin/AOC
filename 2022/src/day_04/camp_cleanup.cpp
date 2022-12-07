#include "camp_cleanup.h"

#include <vector>
#include <regex>

#include "common/file_reader.h"
#include "common/common.h"


using t_assignment = std::pair< long long, long long >;
using t_elves_pair = std::pair< t_assignment, t_assignment >;


std::vector< t_elves_pair > prepare_input( const std::string & filename )
{
    std::vector< std::string > sInput = FileReader::read_file( filename );

    std::vector< t_elves_pair > res;

    const std::regex regexElves(R"((\d+)-(\d+),(\d+)-(\d+))" );
    std::smatch regexMatch;

    for ( const auto & _line : sInput )
    { // _line : "1-2,3-4"

        // Parse the line
        if (    !std::regex_match( _line, regexMatch, regexElves )
             || regexMatch.size() != 5 )
        {
            throw std::invalid_argument( "Invalid input data" );
        }

        res.emplace_back(  t_assignment ( std::stoll( regexMatch[ 1 ] ), std::stoll( regexMatch[ 2 ] ) )
                         , t_assignment ( std::stoll( regexMatch[ 3 ] ), std::stoll( regexMatch[ 4 ] ) ) );
    }

    return res;
}

bool is_contains( const t_assignment & lhs, const t_assignment & rhs )
{
    if (    lhs.first  <= rhs.first
         && lhs.second >= rhs.second )
        return true;

    return false;
}

bool is_contains( const t_elves_pair & elves )
{
    return is_contains( elves.first, elves.second ) || is_contains( elves.second, elves.first );
}

bool is_overlap( const t_assignment & lhs, const t_assignment & rhs )
{
    if (    lhs.first  <= rhs.first
         && lhs.second >= rhs.first )
        return true;

    return false;
}

bool is_overlap( const t_elves_pair & elves )
{
    return    is_overlap( elves.first, elves.second )
           || is_overlap( elves.second, elves.first );
}


long long CampCleanup::task_1( const std::string & filename )
{
    std::vector< t_elves_pair > elves = prepare_input( filename );

    long long res = 0;

    for ( const auto & _elves : elves )
    {
        res += ( is_contains( _elves ) ? 1 : 0 );
    }

    return res;
}

long long CampCleanup::task_2(const std::string &filename)
{
    std::vector< t_elves_pair > elves = prepare_input( filename );

    long long res = 0;

    for ( const auto & _elves : elves )
    {
        res += ( is_overlap( _elves ) ? 1 : 0 );
    }

    return res;
}
