
#include "ceres_search.h"

#include <vector>
#include <algorithm>
#include <optional>
#include <iostream>

#include "common/file_reader.h"


namespace
{
using Field = std::vector< std::string >;

size_t getXSize( const Field & field )
{
    return field[ 0 ].size();
}

size_t getYSize( const Field & field )
{
    return field.size();
}

bool compare_at_point( const Field & field, const Field & pattern, size_t xIndexField, size_t yIndexField )
{
    if (    xIndexField + getXSize( pattern ) - 1 >= getXSize( field )
         || yIndexField + getYSize( pattern ) - 1 >= getYSize( field ) )
    {
        return false;
    }

    for ( size_t yIndex = 0; yIndex < getYSize( pattern ); ++yIndex )
    {
        for ( size_t xIndex = 0; xIndex < getXSize( pattern ); ++xIndex )
        {
            if (    pattern[ yIndex ][ xIndex ] != '.'
                 && pattern[ yIndex ][ xIndex ] != field[ yIndexField + yIndex ][ xIndexField + xIndex ] )
            {
                return false;
            }
        }
    }

    return true;
}

size_t compare_with_pattern( const Field & field, const Field & pattern )
{
    size_t result { 0 };

    for ( size_t yIndexField = 0; yIndexField < field.size(); ++yIndexField )
    {
        for ( size_t xIndexField = 0; xIndexField < field[ yIndexField ].size(); ++xIndexField )
        {
            result += compare_at_point( field, pattern, xIndexField, yIndexField ) ? 1 : 0;
        }
    }

    return result;
}

std::vector< Field > patternsTask1 = {
    {"XMAS"}, {"SAMX"},
    {"X","M","A","S"}, {"S","A","M","X"},
    {"X...",
     ".M..",
     "..A.",
     "...S"},
    {"...X",
     "..M.",
     ".A..",
     "S..."},
    {"S...",
     ".A..",
     "..M.",
     "...X"},
    {"...S",
     "..A.",
     ".M..",
     "X..."}
};

std::vector< Field > patternsTask2 = {
    {"M.S",
     ".A.",
     "M.S"},
    {"S.S",
     ".A.",
     "M.M"},
    {"M.M",
     ".A.",
     "S.S"},
    {"S.M",
     ".A.",
     "S.M"}
};

}// namespace

long long CeresSearch::task_1(const std::string & filename)
{
    // Read the file
    Field field = FileReader::read_file( filename );

    size_t result { 0 };

    for ( const auto & pattern : patternsTask1 )
    {
        result += compare_with_pattern( field, pattern );
    }

    return result;
}

long long CeresSearch::task_2(const std::string & filename)
{
    // Read the file
    Field field = FileReader::read_file( filename );

    size_t result { 0 };

    for ( const auto & pattern : patternsTask2 )
    {
        result += compare_with_pattern( field, pattern );
    }

    return result;
}
