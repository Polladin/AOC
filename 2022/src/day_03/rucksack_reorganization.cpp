#include "rucksack_reorganization.h"

#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <optional>

#include "common/file_reader.h"


std::string get_sorted_unique_str( std::string && str )
{
    std::sort( str.begin(), str.end() );

    str.erase( std::unique( str.begin(), str.end() ), str.end() );

    return std::move( str );
}

char get_intersection_unique( const std::string & str )
{
    std::vector< char > res;

    std::size_t posHalf = str.length() / 2;

    std::string part_1 = get_sorted_unique_str( str.substr( 0      , posHalf ) );
    std::string part_2 = get_sorted_unique_str( str.substr( posHalf, posHalf ) );

    std::set_intersection(   part_1.begin(), part_1.end()
                           , part_2.begin(), part_2.end()
                           , std::back_inserter( res ) );

    if ( res.size() != 1 )
        throw "Wrong Union!";

    return res.front();
}

long long get_priority( char ch )
{
    std::cout << "Plus '" << ch << "' : " << (( ch >= 'a' && ch <= 'z' ) ? ch - 'a' + 1 : ch - 'A' + 27) << "\n";
    return ( ch >= 'a' && ch <= 'z' ) ? ch - 'a' + 1 : ch - 'A' + 27;
}

std::optional< long long > corresponds( const std::string & pack_1, const std::string & pack_2, const std::string & pack_3 )
{
    std::vector< char > res_1_2;
    std::vector< char > res_2_3;
    std::vector< char > res_3_1;

    std::set_intersection(   pack_1.begin(), pack_1.end()
                           , pack_2.begin(), pack_2.end()
                           , std::back_inserter( res_1_2 ) );

    std::set_intersection(   pack_3.begin(), pack_3.end()
                           , pack_2.begin(), pack_2.end()
                           , std::back_inserter( res_2_3 ) );

    std::set_intersection(   pack_1.begin(), pack_1.end()
                           , pack_3.begin(), pack_3.end()
                           , std::back_inserter( res_3_1 ) );

    std::vector< char > res_1_2_2_3;

    std::set_intersection(   res_1_2.begin(), res_1_2.end()
                           , res_2_3.begin(), res_2_3.end()
                           , std::back_inserter( res_1_2_2_3 ) );

    std::vector< char > res;

    std::set_intersection(   res_1_2_2_3.begin(), res_1_2_2_3.end()
                           , res_3_1.begin()    , res_3_1.end()
                           , std::back_inserter( res ) );

    if ( res.size() != 1 )
        throw "Fail!";

    return { get_priority( res.front() ) };
}


long long RucksackReorganization::task_1( const std::string & filename )
{
    std::vector< std::string > rucksacks = FileReader::read_file( filename );

    long long res = 0;

    for ( const auto & _rucksack : rucksacks )
    {
        res += get_priority( get_intersection_unique( _rucksack ) );
//        std::cout << "res: " << res << "\n";
    }

    return res;
}

long long RucksackReorganization::task_2(const std::string &filename)
{
    std::vector< std::string > rucksacks = FileReader::read_file( filename );

    for ( auto & _rucksack : rucksacks )
        _rucksack = get_sorted_unique_str( std::move( _rucksack ) );

    std::set< std::size_t > usedIdx;

    long long res = 0;


    for ( std::size_t idx = 0; idx < rucksacks.size(); idx += 3 )
    {
        res += corresponds( rucksacks[ idx ], rucksacks[ idx + 1 ], rucksacks[ idx + 2 ] ).value();
    }

    return res;
}
