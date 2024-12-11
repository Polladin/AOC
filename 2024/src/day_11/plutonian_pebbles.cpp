
#include "plutonian_pebbles.h"

#include <vector>
#include <assert.h>
#include <sstream>
#include <functional>
#include <unordered_map>

#include "common/file_reader.h"
#include "common/common.h"

namespace
{
using Stones = std::vector< long long >;

Stones prepare_input( const std::string & filename )
{
    Stones result;

    // Read the file
    std::vector< std::string > sInput = FileReader::read_file( filename );
    assert( sInput.size() == 1 && "Must be only the one line input" );

    std::istringstream iss { sInput[ 0 ] };
    long long num;
    for ( iss >> num; iss; iss >> num )
    {
        result.push_back( num );
    }

    return result;
}

bool zero_num( long long num, Stones & stones )
{
    if ( num != 0 )
        return false;

    stones.push_back( 1 );
    return true;
}

int get_number_digits( long long num )
{
    assert( num != 0 && "Number must not be 0" );

    int result { 0 };
    for ( ; num != 0; num /= 10, ++result ){};

    return result;
}

long long get_left_num_part( long long num, int digits )
{
    assert( digits % 2 == 0 && "Digits must be even" );

    digits /= 2;
    for (; digits != 0; --digits, num /= 10 ){}

    return num;
}

long long get_right_num_part( long long num, int digits )
{
    assert( digits % 2 == 0 && "Digits must be even" );

    long long delimetr { 1 };
    digits /= 2;
    for (; digits != 0; --digits, delimetr *= 10 ){}

    return num % delimetr;
}

bool even_number_digits( long long num, Stones & stones )
{
    int digits = get_number_digits( num );

    if ( digits % 2 != 0 )
        return false;

    stones.push_back( get_left_num_part( num, digits ) );
    stones.push_back( get_right_num_part( num, digits ) );

    return true;
}

bool mult_by_2024( long long num, Stones & stones )
{
    stones.push_back( num * 2024 );
    return true;
}

static const std::vector< std::function< bool(long long, Stones&) > > rules =
{
    zero_num,
    even_number_digits,
    mult_by_2024
};

Stones blink( const Stones & stones )
{
    Stones nextStones;

    for ( auto num_ : stones )
    {
        for ( const auto & rule_ : rules )
        {
            if ( rule_( num_, nextStones ) )
            {
                break;
            }
        }
    }

    return nextStones;
}

using GeneratedNums = std::unordered_map< long long, std::vector< long long > >;

GeneratedNums generatedNums;

[[maybe_unused]]
void print_map()
{
    for ( const auto & elem_ : generatedNums )
    {
        std::cout << elem_.first << " : ";
        for ( auto num_ : elem_.second )
        {
            std::cout << num_ << " ";
        }
        std::cout << std::endl;
    }
}

long long get_count_of_generated_nums( long long num, size_t endStep );

void fill_generated_num( long long num, size_t endStep  )
{
    for ( size_t step = generatedNums[ num ].size(); step < endStep; ++step )
    {
        long long countNums { 0 };

        for ( const auto & stone_ : blink( { num } ) )
        {
            countNums += get_count_of_generated_nums( stone_, step );
        }

        generatedNums[ num ].push_back( countNums );
    }
}

long long get_count_of_generated_nums( long long num, size_t endStep )
{
    if ( endStep == 0 )
    {
        return 1;
    }

    fill_generated_num( num, endStep );

    return generatedNums[ num ][ endStep - 1 ];
}

}// namespace

long long PlutonianPebbles::task_1( const std::string & filename )
{
    Stones stones = prepare_input( filename );

    for ( int idx = 0; idx < 25; ++idx )
    {
        stones = blink( stones );
    }

    return stones.size();
}

long long PlutonianPebbles::task_2( const std::string & filename )
{
    Stones stones = prepare_input( filename );

    long long result { 0 };

    for ( auto stone_ : stones )
    {
        result += get_count_of_generated_nums( stone_, 75 );
    }

//    print_map();

    return result;
}
