#include "scratchcards.h"

#include "common/file_reader.h"
#include "common/common.h"

#include <set>
#include <iostream>
#include <numeric>


struct Card
{
    int id;
    std::set< int > winNums;
    std::set< int > yourNums;
};

int get_card_number( const std::string& cardStr )
{
    return std::stoi(common::split_line( cardStr, ' ' )[1]);
}

std::set< int > get_numbers( std::string numbersStr )
{
    std::set< int > result;

    for ( const auto& _num : common::split_line( common::trim(numbersStr), ' ' ) )
    {
        result.insert( std::stoi( _num ) );
    }

    return result;
}

std::vector< Card > prepare_input( const std::string & filename )
{
    std::vector< Card > result;

    // Read the file
    std::vector< std::string > sInput = FileReader::read_file( filename );

    for( const auto & _line : sInput )
    {
        if ( _line.empty() )
        {
            continue;
        }

        const std::vector< std::string > cardLine = common::split_line( _line, ':' );

        const std::vector< std::string > numbers = common::split_line( cardLine[ 1 ], '|' );

        result.emplace_back( /*id*/ get_card_number( cardLine[ 0 ])
                           , /*winNums*/ get_numbers( numbers[ 0 ] )
                           , /*yourNums*/ get_numbers( numbers[ 1 ] )  );
    }

    return result;
}

int get_card_value( const Card& card )
{
    std::set< int > intersection;

    std::set_intersection( card.winNums.begin(), card.winNums.end()
                         , card.yourNums.begin(), card.yourNums.end()
                         , std::inserter(intersection, intersection.begin()));

    if ( intersection.size() == 0 )
    {
        return 0;
    }

    int res = 1;

    for ( size_t pow = 1; pow < intersection.size(); ++pow )
    {
        res *= 2;
    }

    return res;
}

int Scratchcards::task_1( const std::string & filename )
{
    std::vector< Card > cards = prepare_input( filename );

    int res { 0 };

    for ( const auto& _card : cards )
    {
        res += get_card_value( _card );
    }

    return res;
}

int get_count_of_wins( const Card& card )
{
    std::set< int > intersection;

    std::set_intersection( card.winNums.begin(), card.winNums.end()
                         , card.yourNums.begin(), card.yourNums.end()
                         , std::inserter(intersection, intersection.begin()));

    return intersection.size();
}

int Scratchcards::task_2( const std::string & filename )
{
    std::vector< Card > cards = prepare_input( filename );

    std::vector< int > copies ( cards.size(), 1 );

    for ( size_t cardIdx = 0; cardIdx < cards.size(); ++cardIdx )
    {
        const int winCount = get_count_of_wins( cards[ cardIdx ] );

        for ( size_t winIdx = cardIdx + 1; winIdx < cardIdx + 1 + winCount; ++winIdx )
        {
            copies[ winIdx ] += copies[ cardIdx ];
        }
    }

    return std::accumulate( copies.begin(), copies.end(), 0 );
}
