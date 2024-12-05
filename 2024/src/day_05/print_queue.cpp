
#include "print_queue.h"

#include <vector>
#include <map>
#include <optional>
#include <algorithm>

#include "common/file_reader.h"
#include "common/common.h"


namespace
{
using Rule = std::vector< int >;
using PlaceBeforeT = std::map< int, Rule >;
using Pages = std::vector< int >;

struct InputData
{
    PlaceBeforeT rules;
    std::vector< Pages > updates;
};

InputData prepare_input(const std::string & filename)
{
    InputData result;

    // Read the file
    std::vector< std::string > sInput = FileReader::read_file( filename );

    size_t lineIdx { 0 };

    for ( ; !sInput[ lineIdx ].empty(); ++lineIdx )
    {
        auto pageBeforeRule = common::split_line( sInput[ lineIdx ], '|' );

        int page = std::stoi( pageBeforeRule[ 0 ] );
        int beforePage = std::stoi( common::rtrim( pageBeforeRule[ 1 ] ) );

        result.rules[ page ].push_back( beforePage );
    }

    for ( ++lineIdx; lineIdx < sInput.size(); ++lineIdx )
    {
        auto pagesStr = common::split_line( sInput[ lineIdx ], ',' );

        result.updates.emplace_back();

        for ( auto pageStr : pagesStr )
        {
            result.updates.back().push_back( std::stoi( common::rtrim( pageStr ) ) );
        }
    }

    return result;
}

const Rule* get_rule( int page, const PlaceBeforeT & rules )
{
    auto it = rules.find( page );
    return it != rules.end() ? &(it->second) : nullptr;
}

bool check_update( Pages & update, const PlaceBeforeT & rules,
                   std::optional< std::function< void ( size_t, Pages& )> > changeOpt = {} )
{
    for ( size_t idx = 1; idx < update.size(); ++idx )
    {
        if ( const Rule* rule = get_rule( update[ idx ], rules ) )
        {
            for ( auto beforePage : *rule )
            {
                auto endIt = update.begin() + idx;
                if ( std::find( update.begin(), endIt, beforePage ) != endIt )
                {
                    if ( changeOpt )
                    {
                        (*changeOpt)( idx, update );
                    }
                    return false;
                }
            }
        }
    }

    return true;
}

bool updateWasFixed( Pages & update, const PlaceBeforeT & rules )
{
    const auto swapPage = []( size_t idx, Pages & update )
    {
        std::swap( update[ idx - 1 ], update[ idx ] );
    };

    bool wasUpdated { false };

    while ( !check_update( update, rules, swapPage ) )
    {
        wasUpdated = true;
    }

    return wasUpdated;
}

}// namespace

long long PrintQueue::task_1( const std::string & filename )
{
    InputData inputData = prepare_input( filename );

    long long result { 0 };

    for ( auto & update : inputData.updates )
    {
        if ( !updateWasFixed( update, inputData.rules ) )
        {
            result += update[ update.size() / 2 ];
        }
    }

    return result;
}

long long PrintQueue::task_2( const std::string & filename )
{
    InputData inputData = prepare_input( filename );

    long long result { 0 };

    for ( auto & update : inputData.updates )
    {
        if ( updateWasFixed( update, inputData.rules ) )
        {
            result += update[ update.size() / 2 ];
        }
    }

    return result;
}
