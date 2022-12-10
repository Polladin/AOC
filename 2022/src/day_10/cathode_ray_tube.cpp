#include "cathode_ray_tube.h"

#include <vector>
#include <numeric>
#include <iostream>

#include "common/file_reader.h"
#include "common/common.h"


enum class Command
{
     NOP
   , ADDX
};

using t_command = std::pair< Command, int >;

const std::vector< int > signalCycles { 20, 60, 100, 140, 180, 220 };


std::vector< t_command > prepare_input( const std::string & filename )
{
    std::vector< t_command > res;

    auto sInput = FileReader::read_file( filename );

    for ( const auto & _line : sInput )
    {
        // NOOP
        if ( _line.starts_with("noop") )
        {
            res.emplace_back( Command::NOP, 0 );
            continue;
        }

        // ADDX
        res.emplace_back( Command::ADDX, std::stoi( _line.substr( 5 ) ) );
    }

    return res;
}

void check_signal( int reg, int cycle, std::vector< long long > & signals )
{
    if ( std::find( signalCycles.begin(), signalCycles.end(), cycle ) == signalCycles.end() )
        return;

    signals.push_back( cycle * reg );
}

void run_cmd( t_command cmd, int & reg, std::vector< long long > & signals, int & cycle )
{
    if ( cmd.first == Command::NOP )
    {
        ++cycle;
        check_signal( reg, cycle, signals );
        return;
    }

    // ADDX
    for ( int idx = 0; idx < 2; ++idx )
    {
        ++cycle;
        check_signal( reg, cycle, signals );
    }

    reg += cmd.second;
}


void draw_symbol( int reg, int cycle, std::string & draw )
{
    cycle = cycle % 40;

    if ( cycle >= reg && cycle < reg + 3 )
        draw.push_back( '@' );
    else
        draw.push_back( ' ' );
}

void run_cmd( t_command cmd, int & reg, std::string & draw, int & cycle )
{
    if ( cmd.first == Command::NOP )
    {
        ++cycle;
        draw_symbol( reg, cycle, draw );
        return;
    }

    // ADDX
    for ( int idx = 0; idx < 2; ++idx )
    {
        ++cycle;
        draw_symbol( reg, cycle, draw );
    }

    reg += cmd.second;
}

long long CathodeRayTube::task_1( const std::string & filename )
{
    std::vector< t_command > cmds = prepare_input( filename );

    int reg   = 1;
    int cycle = 0;

    std::vector< long long > signals;

    for ( const auto & _cmd : cmds )
        run_cmd( _cmd, reg, signals, cycle );

    return std::accumulate( signals.begin(), signals.end(), 0 );
}

long long CathodeRayTube::task_2( const std::string & filename )
{
    std::vector< t_command > cmds = prepare_input( filename );

    int reg   = 1;
    int cycle = 0;

    std::string draw;

    for ( const auto & _cmd : cmds )
        run_cmd( _cmd, reg, draw, cycle );

    for ( int idx = 0; idx < 6; ++idx )
        std::cout << draw.substr( idx * 40, 40 ) << "\n";

    return 0;
}
