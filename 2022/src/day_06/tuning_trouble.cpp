#include "tuning_trouble.h"

#include <vector>
#include <set>

#include "common/file_reader.h"


long long run( const std::string & message, std::size_t offset )
{
    auto ite = std::prev( message.end(), offset );

    for ( auto it = message.begin(); it != ite; ++it )
    {
        std::set subSet( it, std::next( it, offset ) );

        if ( subSet.size() == offset )
            return std::distance( message.begin(), it ) + offset;
    }

    throw "Wrong input";
}

long long TuningTrouble::task_1( const std::string & filename )
{
    std::string input = FileReader::read_file( filename )[ 0 ];

    return run( input, 4 );
}

long long TuningTrouble::task_2( const std::string & filename )
{
    std::string input = FileReader::read_file( filename )[ 0 ];

    return run( input, 14 );
}
