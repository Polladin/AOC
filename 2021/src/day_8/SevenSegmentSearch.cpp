//
// Created by alexey on 08.12.2021.
//

#include "SevenSegmentSearch.h"

#include <vector>
#include <sstream>
#include <regex>
#include <iostream>

#include "common/file_reader.h"
#include "common/common.h"


void SevenSegmentSearch::prepare_input( const std::string & filename )
{
  // Read the file
  std::vector< std::string > sInput = FileReader::read_file( filename );

  //
  for ( const auto & _line : sInput )
  {
    std::vector< std::string > _parts  = common::split_line( _line, '|' );
    std::vector< std::string > _left   = common::split_line( common::trim( _parts[ 0 ] ), ' ' );
    std::vector< std::string > _right  = common::split_line( common::trim( _parts[ 1 ] ), ' ' );

    left.push_back( _left );
    right.push_back( _right );
  }
}

int SevenSegmentSearch::task_1( const std::string & filename )
{
  prepare_input( filename );

  int res { 0 };

  static const std::vector< int > uniqueDigits { 2, 4, 3, 7 };
  // 1, 4, 7, 8 : 2, 4, 3, 7
  for ( const auto & _indicators : right )
  {
    for ( const auto & _digit : _indicators )
    {
      if( std::find( uniqueDigits.begin(), uniqueDigits.end(), _digit.size()) != uniqueDigits.end() )
        ++res;
    }
  }

  return res;
}

int SevenSegmentSearch::task_2( const std::string &filename )
{
  // 1, 8 - 4, 4

  prepare_input( filename );

  int res { 0 };

  for ( std::size_t _idx = 0; _idx < left.size(); ++_idx )
  {
    res += get_result( _idx );
  }

  return res;
}


static std::string get_diff( const std::string & str1, const std::string & str2 )
{
  std::string res;
  for ( auto _ch1 : str1 )
  {
    if ( str2.find( _ch1 ) == std::string::npos )
      res.push_back( _ch1 );
  }

  return res;
}

static bool is_in( const std::string & str, const std::string & inStr )
{
  return std::all_of( inStr.begin(), inStr.end(),
                      [ &str ]( const char ch ){ return str.find( ch ) != std::string::npos; } );
}

int SevenSegmentSearch::get_result( std::size_t idx  )
{
  std::string one, four, eight, eightMinusFour;
  int res { 0 };

  for ( const auto & _digit : left[ idx ] )
  {
    switch( _digit.size() )
    {
      case 2:
        one = _digit;
        break;
      case 4:
        four = _digit;
        break;
      case 7:
        eight = _digit;
        break;
    }
  }

  eightMinusFour = get_diff( eight, four );

  for ( const auto & _digit : right[ idx ] )
  {
    // 1, 4, 7, 8
    switch( _digit.size() )
    {
      case 2:
        res = res * 10 + 1;
        continue;;
      case 3:
        res = res * 10 + 7;
        continue;
      case 4:
        res = res * 10 + 4;
        continue;
      case 7:
        res = res * 10 + 8;
        continue;
    }

    // 2, 3, 5
    if ( _digit.size() == 5 )
    {
      if ( is_in( _digit, one ) )
      {
        res = res * 10 + 3;
        continue;
      }

      if ( is_in( _digit, eightMinusFour ) )
      {
        res = res * 10 + 2;
        continue;
      }
      res = res * 10 + 5;
      continue;
    }

    // 0, 6, 9
    if ( !is_in( _digit, one ) )
    {
      res = res * 10 + 6;
      continue;
    }

    if ( is_in( _digit, four ) )
    {
      res = res * 10 + 9;
      continue;
    }

    res = res * 10 + 0;
  }

  return res;
}

