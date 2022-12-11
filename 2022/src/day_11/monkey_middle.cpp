#include "monkey_middle.h"

#include <vector>
#include <functional>
#include <iostream>
#include <numeric>

#include "common/file_reader.h"
#include "common/common.h"


struct Monkey
{
    std::vector< long long > items;

    std::function< long long ( long long ) > inspect_item;

    long long dividedBy;

    long long throwMonkeyFalse;
    long long throwMonkeyTrue;

    long long worryLimit;

    long long countInspected { 0 };
};


std::function< long long ( long long ) > get_inspect_func( const std::string strFunc )
{
    // * old
    if ( strFunc.starts_with( "* old" ) )
        return []( long long old ){ return old * old; };

    long long num = std::stoll( strFunc.substr( 2 ) );

    // +
    if ( strFunc[ 0 ] == '+' )
        return [num]( long long old ){ return old + num; };

    // *
    return [num]( long long old ){ return old * num; };
}

Monkey get_monkey( std::size_t idx, std::vector< std::string > & sInput )
{
    Monkey monkey;
    // Items: Starting items: 79, 98
    ++idx;

    auto items = common::split_line( common::split_line( sInput[ idx ], ':' )[ 1 ], ',' );

    std::transform(   items.begin(), items.end(), std::back_inserter( monkey.items )
                    , []( const std::string & str ) { return std::stoll( str ); } );

    // Operation: Operation: new = old * 19
    ++idx;

    monkey.inspect_item = get_inspect_func( sInput[ idx ].substr( 23 ) );

    // Test:
    //   Test: divisible by 11
    ++idx;

    monkey.dividedBy = std::stoll( sInput[ idx ].substr( 21 ) );

    //    If true: throw to monkey 2
    ++idx;
    monkey.throwMonkeyTrue = std::stoll( sInput[ idx ].substr( 29 ) );

    //    If false: throw to monkey 7
    ++idx;
    monkey.throwMonkeyFalse = std::stoll( sInput[ idx ].substr( 30 ) );

    return monkey;
}

std::vector< Monkey > prepare_input( const std::string & filename )
{
    auto sInput = FileReader::read_file( filename );

    std::vector< Monkey > res;

    const std::size_t MONKEY_BLOCK_SIZE = 6;

    for ( std::size_t idx = 0; idx < sInput.size(); idx += MONKEY_BLOCK_SIZE )
    {
        res.push_back( get_monkey( idx, sInput ) );
    }

    return res;
}


void monkey_turn( Monkey & monkey, std::vector< Monkey > & monkeys, bool isPart1 = true )
{
    for ( long long _item : monkey.items )
    {
        // Inspect
        long long inspectedItem = monkey.inspect_item( _item );

        // Bored
        if ( isPart1 )
            inspectedItem /= 3;
        else
            inspectedItem %= monkey.worryLimit;

        // Test
        std::size_t toMonkey = ( inspectedItem % monkey.dividedBy == 0 ) ? monkey.throwMonkeyTrue : monkey.throwMonkeyFalse;

        monkeys[ toMonkey ].items.push_back( inspectedItem );

        ++monkey.countInspected;
    }

    monkey.items.clear();
}


long long MonkeyMiddle::task_1( const std::string & filename )
{
    std::vector< Monkey > monkeys = prepare_input( filename );

    for ( int turn = 0; turn < 20; ++turn )
    {
        for ( auto & _monkey : monkeys )
            monkey_turn( _monkey, monkeys );

//        for ( const auto & _monkey : monkeys )
//            std::for_each( _monkey.items.begin(), _monkey.items.end(), []( long long item ){ std::cout << item << ", "; } );
//        std::cout << "\n";
    }

    std::vector< long long > inspected;

    for ( std::size_t idx = 0; idx < monkeys.size(); ++idx )
    {
//        std::cout << "idx " << idx << " : " << monkeys[ idx ].countInspected << "\n";
        inspected.push_back( monkeys[ idx ].countInspected );
    }

    std::sort( inspected.begin(), inspected.end() );

    return inspected.back() * inspected[ inspected.size() - 2 ];
}

long long MonkeyMiddle::task_2( const std::string & filename )
{
    std::vector< Monkey > monkeys = prepare_input( filename );

    long long worryLimit { 1 };

    for ( const auto & _monkey : monkeys )
        worryLimit *= _monkey.dividedBy;

    for ( auto & _monkey : monkeys )
        _monkey.worryLimit = worryLimit;

    for ( int turn = 0; turn < 10000; ++turn )
    {
        for ( auto & _monkey : monkeys )
            monkey_turn( _monkey, monkeys, /* isPart1*/ false );
    }

    for ( const auto & _monkey : monkeys )
        std::for_each( _monkey.items.begin(), _monkey.items.end(), []( long long item ){ std::cout << item << ", "; } );
    std::cout << "\n";

    std::vector< long long > inspected;

    for ( std::size_t idx = 0; idx < monkeys.size(); ++idx )
    {
        std::cout << "idx " << idx << " : " << monkeys[ idx ].countInspected << "\n";
        inspected.push_back( monkeys[ idx ].countInspected );
    }

    std::sort( inspected.begin(), inspected.end() );

    return inspected.back() * inspected[ inspected.size() - 2 ];
}
