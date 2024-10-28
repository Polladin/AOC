#include "boat_race.h"

#include "common/file_reader.h"
#include "common/common.h"

#include <vector>

struct Race
{
    long long time;
    long long distance;
};

std::vector< long long > get_numerics( const std::string & line )
{
    std::vector< std::string > numbers = common::split_line( common::trim( common::split_line( line, ':' )[1] ), ' ' );

    std::vector< long long > result;

    for ( const auto & _num : numbers )
    {
        result.push_back( std::stoll( _num ) );
    }

    return result;
}

std::vector< Race > prepare_input( const std::string & filename )
{
    // Read the file
    std::vector< std::string > sInput = FileReader::read_file( filename );

    std::vector< long long > times = get_numerics( sInput[ 0 ]);
    std::vector< long long > distance = get_numerics( sInput[ 1 ]);

    std::vector< Race > result;

    for ( std::size_t idx = 0; idx < times.size(); ++idx )
    {
        result.emplace_back( times[ idx ], distance[ idx ] );
    }

    return result;
}

long long get_race_win_count( const Race & race )
{
    long long result { 0 };

    for ( long long time = 1; time < race.time; ++time )
    {
        const long long speed = time;
        const long long distance = ( race.time - time ) * speed;

        result += ( distance > race.distance ) ? 1ll : 0ll;
    }

    return result;
}

long long BoatRace::task_1( const std::string & filename )
{
    std::vector< Race > races = prepare_input( filename );

    long long result { 1 };

    for ( const Race & _race : races )
    {
        result *= get_race_win_count( _race );
    }

    return result;
}

long long BoatRace::task_2( const std::string & filename )
{
    return task_1( filename );
}
