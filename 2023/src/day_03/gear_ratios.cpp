#include "gear_ratios.h"

#include "common/file_reader.h"

#include <optional>
#include <iostream>


bool contains_special_symbol( int row, int column, const std::vector< std::string >& input )
{
    static const std::vector<std::pair<int, int>> OFFSETS = {  { -1, -1 }, { 0, -1 }, { 1, -1 }
                                                             , { -1,  0 },            { 1,  0 }
                                                             , { -1,  1 }, { 0,  1 }, { 1,  1 } };

    for( const auto& _offset : OFFSETS )
    {
        const int newRow = row + _offset.second;
        const int newCol = column + _offset.first;

        if (   newRow < 0
            || newCol < 0
            || newRow >= static_cast<int>( input.size() )
            || newCol >= static_cast<int>( input[newRow].size() ) )
        {
            continue;
        }

        if ( input[ newRow ][ newCol ] != '.' && !std::isdigit( input[ newRow ][ newCol ] ) )
        {
            return true;
        }
    }

    return false;
}

struct Range
{
    Range( int iBegin, int iEnd )
        : begin{ iBegin }
        , end{ iEnd }
    {}

    int begin;
    int end;
};

std::vector<std::pair<int, Range>> getNumbers(const std::string& line)
{
    std::vector<std::pair<int, Range>> result;

    int num { 0 };
    std::optional<int> startIdx;

    for( size_t idx = 0; idx < line.size(); ++idx )
    {
        if ( std::isdigit( line[ idx ] ) )
        {
            num = num * 10 + line[ idx ] - '0';

            if ( !startIdx )
            {
                startIdx = idx;
            }
        }
        else
        {
            if( startIdx )
            {
                result.emplace_back( std::make_pair(num, Range(startIdx.value(), idx)) );
                num = 0;
                startIdx.reset();
            }
        }
    }

    if( startIdx )
    {
        result.emplace_back( std::make_pair(num, Range(startIdx.value(), line.size())) );
    }

    return result;
}


std::vector<int> prepare_input( const std::string & filename )
{
    // Read the file
    std::vector< std::string > sInput = FileReader::read_file( filename );

    std::vector< int > result;

    for ( int rowIdx = 0; rowIdx < static_cast< int >( sInput.size() ); ++rowIdx)
    {
        if ( sInput[ rowIdx ].empty() )
        {
            continue;
        }

        std::vector<std::pair<int, Range>> nums = getNumbers( sInput[ rowIdx ] );

        for ( const auto& _num : nums )
        {
            for ( int columnIdx = _num.second.begin; columnIdx < _num.second.end; ++columnIdx )
            {
                if ( contains_special_symbol(rowIdx, columnIdx, sInput ) )
                {
                    result.push_back( _num.first );
                    break;
                }
            }
        }
    }

    return result;
}

int GearRatios::task_1( const std::string & filename )
{
    std::vector<int> nums = prepare_input( filename );

    int res = 0;

    for (const int _num : nums)
    {
        res += _num;
    }

    return res;
}

using NumsInRow = std::vector<std::pair<int, Range>>;

std::vector<std::pair<int, NumsInRow>> prepare_input_task_2( const std::string & filename, std::vector< std::string >& field )
{
    // Read the file
    std::vector< std::string > sInput = FileReader::read_file( filename );

    std::vector<std::pair<int, NumsInRow>> result;

    for ( int rowIdx = 0; rowIdx < static_cast< int >( sInput.size() ); ++rowIdx)
    {
        if ( sInput[ rowIdx ].empty() )
        {
            continue;
        }

        std::vector<std::pair<int, Range>> nums = getNumbers( sInput[ rowIdx ] );
        std::vector<std::pair<int, Range>> numsSpecial;

        for ( const auto& _num : nums )
        {
            for ( int columnIdx = _num.second.begin; columnIdx < _num.second.end; ++columnIdx )
            {
                if ( contains_special_symbol(rowIdx, columnIdx, sInput ) )
                {
                    numsSpecial.push_back( _num );
                    break;
                }
            }
        }

        result.emplace_back(rowIdx, numsSpecial);
    }

    field = sInput;

    return result;
}

std::optional< std::pair< int, int > > get_two_gears(std::size_t row,
                                                 std::size_t col,
                                                 const std::vector<std::pair<int, NumsInRow>>& nums)
{
    std::vector< int > adjacentNumbers;

    for ( const auto& _num : nums )
    {
        if ( std::abs( _num.first - static_cast<int>(row) ) <= 1 )
        {
            for ( const auto& _numInRows : _num.second )
            {
                if ( static_cast<int>(col) >= _numInRows.second.begin - 1 && static_cast<int>(col) <= _numInRows.second.end )
                {
                    adjacentNumbers.push_back( _numInRows.first );
                }
            }
        }
    }

    if (adjacentNumbers.size() != 2)
    {
        return {};
    }

    return { { adjacentNumbers[0], adjacentNumbers[1] } };
}

std::vector<std::pair<int, int>> get_gears_product(const std::vector<std::pair<int, NumsInRow>>& nums,
                                                   const std::vector< std::string >& field)
{
    std::vector<std::pair<int, int>> result;

    for( std::size_t _row = 0; _row < field.size(); ++_row )
    {
        for ( std::size_t _col = 0; _col < field[ _row ].size(); ++_col )
        {
            if ( field[ _row ][ _col ] == '*' )
            {
                if ( auto gears = get_two_gears( _row, _col, nums ) )
                {
                     result.push_back(gears.value());
                }
            }
        }
    }

    return result;
}

int GearRatios::task_2( const std::string & filename )
{
    std::vector< std::string > field;

    std::vector<std::pair<int, NumsInRow>> nums = prepare_input_task_2(filename, field);

    std::vector<std::pair<int, int>> gears = get_gears_product(nums, field);

    int res = 0;

    for ( const auto& _gear : gears )
    {
        int productOf = _gear.first * _gear.second;

        res += productOf;
    }

    return res;
}
