#include "calorie_counting.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

#include "common/file_reader.h"


std::vector< long long > prepare_input( const std::string & filename )
{
    // Read the file
    std::vector< std::string > sInput = FileReader::read_file( filename );

    std::vector< long long > res;
    long long total_elf_colories { 0 };

    for( const auto & _line : sInput )
    {
        if ( _line.empty() )
        {
            res.push_back( total_elf_colories );
            total_elf_colories = 0;

            continue;
        }

        total_elf_colories += std::stoll( _line );
    }

    return res;
}


long long CalorieCounting::part_1( const std::string & filename )
{
    std::vector< long long > elves = prepare_input( filename );

    std::sort( elves.begin(), elves.end() );

    return elves.back();
}

long long CalorieCounting::part_2(const std::string &filename)
{
    std::vector< long long > elves = prepare_input( filename );

    std::sort( elves.begin(), elves.end() );

    return std::accumulate( std::prev( elves.end(), 3 ), elves.end(), 0ll );
}
