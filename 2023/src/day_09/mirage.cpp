#include "mirage.h"

#include "common/file_reader.h"

#include <sstream>
#include <stack>

using Sequence = std::vector< long long >;
using Sequencies = std::vector< Sequence >;


Sequencies prepare_input( const std::string & filename )
{
    // Read the file
    std::vector< std::string > sInput = FileReader::read_file( filename );

    Sequencies result;

    for ( const std::string & _line : sInput )
    {
        if ( _line.empty() )
        {
            break;
        }

        Sequence seq;
        std::istringstream iss( _line );

        while( !iss.eof() )
        {
            long long num;

            iss >> num;
            seq.push_back( num );
        }

        result.emplace_back( std::move( seq ) );
    }

    return result;
}

bool is_all_elements_same( const Sequence & seq )
{
    return std::all_of( seq.begin(), seq.end(), [&seq](const int val){ return val == seq[ 0 ]; } );
}

Sequence get_next_diff( const Sequence & seq )
{
    Sequence result;

    for( std::size_t idx = 1; idx < seq.size(); ++idx )
    {
        result.push_back( seq[ idx ] - seq[ idx - 1 ] );
    }

    return result;
}

long long extrapolate( const Sequence & seq )
{
    std::stack< Sequence > diffs;

    diffs.push( seq );

    while( !is_all_elements_same( diffs.top() ) )
    {
        diffs.push( get_next_diff( diffs.top() ) );
    }

    long long increase { diffs.top().back() };
    diffs.pop();

    while( !diffs.empty() )
    {
        increase += diffs.top().back();
        diffs.pop();
    }

    return increase;
}

long long Mirage::task_1( const std::string & filename )
{
    Sequencies sequencies = prepare_input( filename );

    long long result { 0 };

    for ( const Sequence & seq : sequencies )
    {
        result += extrapolate( seq );
    }

    return result;
}

long long extrapolate_2( const Sequence & seq )
{
    std::stack< Sequence > diffs;

    diffs.push( seq );

    while( !is_all_elements_same( diffs.top() ) )
    {
        diffs.push( get_next_diff( diffs.top() ) );
    }

    long long increase { diffs.top().front() };
    diffs.pop();

    while( !diffs.empty() )
    {
        increase = diffs.top().front() - increase;
        diffs.pop();
    }

    return increase;
}

long long Mirage::task_2( const std::string & filename )
{
    Sequencies sequencies = prepare_input( filename );

    long long result { 0 };

    for ( const Sequence & seq : sequencies )
    {
        result += extrapolate_2( seq );
    }

    return result;
}
