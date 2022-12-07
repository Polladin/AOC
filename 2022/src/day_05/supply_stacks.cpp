#include "supply_stacks.h"

#include <vector>
#include <regex>
#include <algorithm>
#include <iterator>

#include "common/file_reader.h"
#include "common/common.h"


using t_stacks = std::vector< std::vector< char > >;

struct Movement
{
    std::size_t count;
    std::size_t from;
    std::size_t to;
};

std::tuple< t_stacks, std::vector< Movement > > prepare_input( const std::string & filename )
{
    std::vector< std::string > sInput = FileReader::read_file( filename );

    t_stacks stacks;

    std::size_t idx = 0;

    while ( sInput[ idx ][ 1 ] != '1' )
        ++idx;

    // Read Stacks
    for ( std::size_t pos = 1; pos < sInput[ idx ].size(); pos += 4 )
    {
        std::vector< char > stack;

        int stackPos = idx - 1;

        for( ; stackPos >= 0; --stackPos )
        {
            if ( sInput[ stackPos ][ pos ] != ' ' )
                stack.push_back( sInput[ stackPos ][ pos ] );
        }

        stacks.push_back( std::move( stack ) );
    }

    // Read Movements
    ++idx;
    std::vector< Movement > movements;

    const std::regex regexElves(R"(move (\d+) from (\d+) to (\d+))" );
    std::smatch regexMatch;

    for ( ; idx < sInput.size(); ++idx )
    {// move 1 from 2 to 1

        // Parse the line
        if (    !std::regex_match( sInput[ idx ], regexMatch, regexElves )
             || regexMatch.size() != 4 )
        {
            throw std::invalid_argument( "Invalid input data" );
        }

        movements.push_back( Movement{  .count = std::stoul( regexMatch[ 1 ] )
                                      , .from  = std::stoul( regexMatch[ 2 ] ) - 1
                                      , .to    = std::stoul( regexMatch[ 3 ] ) - 1 } );
    }

    return { stacks, movements };
}

void apply_movements( t_stacks & stacks, const std::vector< Movement > & movements )
{
    for ( const auto & _movement : movements )
    {
        for ( std::size_t idx = 0; idx < _movement.count; ++idx )
        {
            stacks[ _movement.to   ].push_back( stacks[ _movement.from ].back() );
            stacks[ _movement.from ].pop_back();
        }
    }
}

void apply_movements_2( t_stacks & stacks, const std::vector< Movement > & movements )
{
    for ( const auto & _movement : movements )
    {
        auto its = std::prev( stacks[ _movement.from ].end(), _movement.count );
        auto ite = stacks[ _movement.from ].end();

        std::copy( its, ite, std::back_inserter( stacks[ _movement.to ] ) );

        stacks[ _movement.from ].erase( its, ite );
    }
}

void print_result( const t_stacks & stacks )
{
    std::cout << "Res: ";

    for ( const auto & _stack : stacks )
        std::cout << _stack.back();

    std::cout << "\n";
}

long long SupplyStacks::task_1( const std::string & filename )
{
    auto [ stacks, movements ] = prepare_input( filename );

    apply_movements( stacks, movements );

    print_result( stacks );

    return 0;
}

long long SupplyStacks::task_2(const std::string &filename)
{
    auto [ stacks, movements ] = prepare_input( filename );

    apply_movements_2( stacks, movements );

    print_result( stacks );

    return 0;
}
