#include "fertilizer.h"

#include "common/file_reader.h"
#include "common/common.h"

#include <vector>
#include <algorithm>

struct Transformation
{
    long long source;
    long long offset;

    long long length;
};

using RangesOfTransformations = std::vector<Transformation>;

struct SeedProcessData
{
    std::vector< long long > seeds;

    std::vector<RangesOfTransformations> transformations;
};

std::vector< long long > get_seeds( const std::string & line )
{
    std::vector< std::string > numbers = common::split_line( common::trim( common::split_line( line, ':' )[1] ), ' ' );

    std::vector< long long > result;

    for ( const auto & _num : numbers )
    {
        result.push_back( std::stoll( _num ) );
    }

    return result;
}

Transformation get_transformation( const std::string & line )
{
    std::vector< std::string > numbers = common::split_line( line, ' ' );

    const long long destination = std::stoll( numbers[ 0 ] );
    const long long source = std::stoll( numbers[ 1 ] );
    const long long length = std::stoll( numbers[ 2 ] );

    return { source, destination - source, length };
}

SeedProcessData prepare_input( const std::string & filename )
{
    // Read the file
    std::vector< std::string > sInput = FileReader::read_file( filename );

    SeedProcessData result;

    result.seeds = get_seeds( sInput[ 0 ] );

    for( std::size_t lineIdx = 2; lineIdx < sInput.size(); ++lineIdx )
    {
        RangesOfTransformations transformations;

        for( ; !sInput[ lineIdx ].empty(); ++lineIdx )
        {
            if( sInput[ lineIdx ].find_first_of(':') != std::string::npos )
            {
                continue;
            }

            transformations.emplace_back( get_transformation( sInput[ lineIdx ] ) );
        }

        result.transformations.push_back( transformations );
        transformations.clear();
    }

    return result;
}

long long transform( long long data, const RangesOfTransformations & transformation )
{
    for ( const auto & _range : transformation )
    {
        if ( data >= _range.source && data < _range.source +_range.length )
        {
            return data + _range.offset;
        }
    }

    return data;
}

long long Fertilizer::task_1( const std::string & filename )
{
    SeedProcessData data = prepare_input( filename );

    std::vector< long long > locations;

    for ( const long long _seed : data.seeds )
    {
        long long processed = _seed;

        for ( const auto & _transformation : data.transformations )
        {
            processed = transform( processed, _transformation );
        }

        locations.push_back( processed );
    }

    std::sort( locations.begin(), locations.end() );

    return locations.front();
}

struct DataRange
{
    long long begin;
    long long end;
};

std::vector< DataRange > get_processed_data( const DataRange & range, const RangesOfTransformations & transformation )
{
    std::vector< DataRange > initialRanges { range };
    std::vector< DataRange > transformedRanges;

    for ( const auto & _transformatoin : transformation )
    {
        std::vector< DataRange > newInitialRanges;

        for ( const DataRange & _range : initialRanges )
        {
            // No intersection
            if (    _range.begin >= _transformatoin.source + _transformatoin.length
                 || _range.end < _transformatoin.source)
            {
                newInitialRanges.push_back( _range );
                continue;
            }

            // Inside range
            if (   _range.begin >= _transformatoin.source
                && _range.end < _transformatoin.source + _transformatoin.length )
            {
                transformedRanges.emplace_back( _range.begin + _transformatoin.offset
                                              , _range.end + _transformatoin.offset );
            }

            // Top intersection
            if (    _range.begin < _transformatoin.source
                 && _range.end > _transformatoin.source )
            {
                newInitialRanges.emplace_back( _range.begin, _transformatoin.source );

                if ( _range.end <= _transformatoin.source + _transformatoin.length )
                {
                    transformedRanges.emplace_back( _transformatoin.source + _transformatoin.offset
                                                  , _range.end + _transformatoin.offset );
                }
                else
                {
                    transformedRanges.emplace_back( _transformatoin.source + _transformatoin.offset
                                                  , _transformatoin.source + _transformatoin.length + _transformatoin.offset );

                    newInitialRanges.emplace_back( _transformatoin.source + _transformatoin.length, _range.end );
                }
            }

            // Bottom intersaction
            if (    _range.begin >= _transformatoin.source
                 && _range.begin < _transformatoin.source + _transformatoin.length )
            {
                if ( _range.end <= _transformatoin.source + _transformatoin.length )
                {
                    transformedRanges.emplace_back( _range.begin + _transformatoin.offset
                                                  , _range.end + _transformatoin.offset );
                }
                else
                {
                    transformedRanges.emplace_back( _range.begin + _transformatoin.offset
                                                  , _transformatoin.source + _transformatoin.length + _transformatoin.offset );

                    newInitialRanges.emplace_back( _transformatoin.source + _transformatoin.length, _range.end );
                }
            }
        }

        initialRanges = newInitialRanges;
    }

    std::copy( initialRanges.begin(), initialRanges.end(), std::back_inserter( transformedRanges ) );

    return transformedRanges;
}

std::vector< DataRange > get_processed_data( const std::vector< DataRange > & ranges, const RangesOfTransformations & transformation )
{
    std::vector< DataRange > result;

    for ( const auto & _range : ranges )
    {
        std::vector< DataRange > transfroredRanges = get_processed_data( _range, transformation );

        std::copy( transfroredRanges.begin(), transfroredRanges.end(), std::back_inserter( result ) );
    }

    return result;
}

long long get_lowest_location( long long seed, long long length, std::vector< RangesOfTransformations > & transformations )
{
    const DataRange seedRange { seed, seed + length };

    std::vector< DataRange > processedRanges { seedRange };

    for ( const auto & _transformation : transformations )
    {
        processedRanges = get_processed_data( processedRanges, _transformation );
    }

    std::sort( processedRanges.begin(), processedRanges.end(),
                []( const DataRange& lhs, const DataRange& rhs )
                {
                    return lhs.begin < rhs.begin;
                });

    return processedRanges.front().begin;
}

long long Fertilizer::task_2( const std::string & filename )
{
    SeedProcessData data = prepare_input( filename );

    std::vector< long long > locations;

    for ( std::size_t seedNum = 0; seedNum < data.seeds.size() / 2; ++seedNum )
    {
        locations.push_back( get_lowest_location( data.seeds[ 2 * seedNum ], data.seeds[ 2 * seedNum + 1 ], data.transformations ) );
    }

    std::sort( locations.begin(), locations.end() );

    return locations.front();
}
