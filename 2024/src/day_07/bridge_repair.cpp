
#include "bridge_repair.h"

#include <vector>
#include <cmath>
#include <assert.h>

#include "common/file_reader.h"
#include "common/common.h"


namespace
{
struct InputData
{
    std::vector< long long > numbers;
    long long result;
};

std::vector< InputData > prepare_input( const std::string & filename )
{
    std::vector< InputData > result;

    // Read the file
    std::vector< std::string > sInput = FileReader::read_file( filename );

    for ( const auto & line_ : sInput )
    {
        const auto answerAndNums = common::split_line( line_, ':' );

        const std::string answerStr = answerAndNums[ 0 ];
        const std::string numsStr = answerAndNums[ 1 ];

        InputData data;
        data.result = std::stoll( answerStr );

        for ( const auto & num_ : common::split_line( numsStr, ' ' ) )
        {
            data.numbers.push_back( std::stoll( num_ ) );
        }

        result.push_back( data );
    }

    return result;
}

enum class Operation
{
    PLUS,
    MUL,
    CONCAT,

    LAST_ELEMENT
};

std::vector< Operation > get_operations( int num, size_t positions )
{
    std::vector< Operation > result { positions, Operation::PLUS };

    const int operationsSize = static_cast< int >( Operation::LAST_ELEMENT );

    for ( size_t idx = 0 ; num != 0; num /= operationsSize, ++idx )
    {
        result[ idx ] = static_cast< Operation >( num % operationsSize );
    }

    return result;
}

int get_max_operations_num( int positionsCount )
{
    return std::pow( static_cast< int >( Operation::LAST_ELEMENT ), positionsCount );
}

long long get_concat_result( long long lhs, long long rhs )
{
    for ( long long powNumber = rhs; powNumber != 0; powNumber /= 10 )
    {
        lhs *= 10;
    }

    return lhs + rhs;
}

long long get_result(const std::vector< long long > nums, const std::vector< Operation > & operations )
{
    assert( nums.size() - 1 == operations.size() && "Size of nums and operations" );

    long long result { nums[ 0 ] };

    for ( size_t idx = 1; idx < nums.size(); ++idx )
    {
        switch ( operations[ idx - 1 ] )
        {
        case Operation::PLUS: result += nums[ idx ]; break;
        case Operation::MUL : result *= nums[ idx ]; break;
        case Operation::CONCAT : result = get_concat_result( result, nums[ idx ] ); break;
        default: throw "Unknows Operation";
        }
    }

    return result;
}

bool is_valid( const InputData & data )
{
    assert( data.numbers.size() > 1 && "Size must be more that 1" );
    const int maxOperationsNum = get_max_operations_num( data.numbers.size() - 1 );

    for ( int numOperation = 0; numOperation < maxOperationsNum; ++numOperation )
    {
        std::vector< Operation > operations = get_operations( numOperation, data.numbers.size() - 1 );

        if ( get_result( data.numbers, operations ) == data.result )
        {
            return true;
        }
    }

    return false;
}

}// namespace

long long GuardGallivant::task_1( const std::string & /*filename*/ )
{
    return 0;
}


long long GuardGallivant::task_2( const std::string & filename )
{
    std::vector< InputData > inputData = prepare_input( filename );

    long long result { 0 };

    for ( const auto & data_ : inputData )
    {
        if ( is_valid( data_ ) )
        {
            result += data_.result;
        }
    }

    return result;
}
