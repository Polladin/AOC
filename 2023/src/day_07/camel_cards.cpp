#include "camel_cards.h"

#include "common/file_reader.h"
#include "common/common.h"

#include <map>
#include <set>
#include <optional>

struct Hand
{
    std::string cards;
    long long bid;
};

std::vector< Hand > prepare_input( const std::string & filename )
{
    // Read the file
    std::vector< std::string > sInput = FileReader::read_file( filename );

    std::vector< Hand > result;

    for ( const std::string & _line : sInput )
    {
        if ( _line.empty() )
        {
            continue;
        }

        const std::vector< std::string > splittedLine = common::split_line( _line, ' ' );
        const long long bid = std::stoll( splittedLine[ 1 ] );

        result.emplace_back( splittedLine[ 0 ], bid );
    }

    return result;
}

const std::map< char, long long > CARD_VALUE =
{
    { '2', 2 }, { '3', 3 }, { '4', 4 }, { '5', 5 }, { '6', 6 }, { '7', 7 }, { '8', 8 }, { '9', 9 }
    , { 'T', 10 }, { 'J', 1 }, { 'Q', 12 }, { 'K', 13 }, { 'A', 14 }
};

std::multimap< long long, char > get_copies( const std::string & cards )
{
    std::map< char, long long >  cardCopies;

    for ( const char card1 : cards )
    {
        const long long copies = std::count( cards.begin(), cards.end(), card1 );

        cardCopies.emplace( card1, copies );
    }

    std::multimap< long long, char > counts;

    long long jCount = 0;

    for ( const auto & _cardInfo :  cardCopies)
    {
        if ( _cardInfo.first == 'J' )
        {
            jCount += _cardInfo.second;
            continue;
        }

        counts.emplace( _cardInfo.second, _cardInfo.first );
    }

    if ( counts.size() == 0 )
    {
        counts.emplace( 5, 'J' );
    }
    else
    {
        auto it = std::prev(counts.end());
        const long long newCount = it->first + jCount;
        const char newLetter = it->second;

        counts.erase( it );
        counts.emplace( newCount, newLetter );
    }

    return counts;
}

struct CardLessComparator
{
    static bool isFiveOfKind( const std::string & cards )
    {
        return get_copies( cards ).count( 5ll ) > 0;
    }

    static bool isFourOfKind( const std::string & cards )
    {
        return get_copies( cards ).count( 4ll ) > 0;
    }

    static bool isFullHous( const std::string & cards )
    {
        return    get_copies( cards ).count( 3ll ) > 0
               && get_copies( cards ).count( 2ll ) > 0;
    }

    static bool isThreeOfKind( const std::string & cards )
    {
        return get_copies( cards ).count( 3ll ) > 0;
    }

    static bool isTwoPair( const std::string & cards )
    {
        return get_copies( cards ).count( 2ll ) == 2;
    }

    static bool isOnePair( const std::string & cards )
    {
        return get_copies( cards ).count( 2ll ) > 0;
    }

    std::optional< bool > compare(   const std::string & lhs
                                   , const std::string & rhs
                                   , std::function<bool(const std::string & cards)> func)
    {
        if ( !func( lhs ) && func( rhs ) )
        {
            return { true };
        }

        if ( func( lhs ) && !func( rhs ) )
        {
            return { false };
        }

        if ( func( lhs ) && func( rhs ))
        {
            // Rest of
            for ( std::size_t idx = 0; idx < lhs.size(); ++idx )
            {
                if ( CARD_VALUE.find( lhs[ idx ] )->second == CARD_VALUE.find( rhs[ idx ] )->second )
                {
                    continue;
                }

                return CARD_VALUE.find( lhs[ idx ] )->second < CARD_VALUE.find( rhs[ idx ] )->second;
            }

            std::abort();
        }

        return {};
    }

    bool operator()( const Hand & lhs, const Hand & rhs )
    {
        // Five
        if ( const auto cmpResult = compare( lhs.cards, rhs.cards, isFiveOfKind) )
        {
            return cmpResult.value();
        }

        // Four
        if ( const auto cmpResult = compare( lhs.cards, rhs.cards, isFourOfKind) )
        {
            return cmpResult.value();
        }

        // Full House
        if ( const auto cmpResult = compare( lhs.cards, rhs.cards, isFullHous) )
        {
            return cmpResult.value();
        }

        // Three
        if ( const auto cmpResult = compare( lhs.cards, rhs.cards, isThreeOfKind) )
        {
            return cmpResult.value();
        }

        // Two pairs
        if ( const auto cmpResult = compare( lhs.cards, rhs.cards, isTwoPair) )
        {
            return cmpResult.value();
        }

        // One pairs
        if ( const auto cmpResult = compare( lhs.cards, rhs.cards, isOnePair) )
        {
            return cmpResult.value();
        }

        // Rest of
        for ( std::size_t idx = 0; idx < lhs.cards.size(); ++idx )
        {
            if ( CARD_VALUE.find( lhs.cards[ idx ] )->second == CARD_VALUE.find( rhs.cards[ idx ] )->second )
            {
                continue;
            }

            return CARD_VALUE.find( lhs.cards[ idx ] )->second < CARD_VALUE.find( rhs.cards[ idx ] )->second;
        }

        std::abort();
    }
};

long long CamelCards::task_1( const std::string & filename )
{
    std::vector< Hand > hands = prepare_input( filename );

    CardLessComparator cardLessComparator;

    std::sort( hands.begin(), hands.end(), cardLessComparator );

    long long result { 0 };

    for( std::size_t idx = 0; idx < hands.size(); ++idx )
    {
        result = result + ( idx + 1 ) * hands[ idx ].bid;
        std::cout << "Id: " << idx + 1 << " - " << hands[ idx ].cards << " bid: " << hands[ idx ].bid
                  << " res: " << result << std::endl;
    }

    return result;
}

long long CamelCards::task_2( const std::string & /*filename*/ )
{
    return 0;
}
