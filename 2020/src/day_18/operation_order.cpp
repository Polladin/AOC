//
// Created by alexey on 25.12.2020.
//

#include "operation_order.h"

#include <vector>
#include <iostream>

#include "common/file_reader.h"


enum class Operations
{
    EMPTY
  , ADD
  , MULT
};


unsigned long long prepare_brakets( const std::string & sInput, std::size_t & currentIdx )
{
  unsigned long long result { 0 };
  unsigned long long number { 0 };
  Operations op { Operations::ADD };

  while( currentIdx < sInput.size() )
  {
    // Is number
    if ( sInput[ currentIdx ] >= '0' && sInput[ currentIdx ] <= '9' )
    {
      number = number * 10 + sInput[ currentIdx ] - '0';
    }
    // Is Operator: MUL or ADD
    else if ( sInput[ currentIdx ] == '*' || sInput[ currentIdx ] == '+' )
    {
      result = ( op == Operations::ADD ) ? result + number
                                         : result * number;
      number = 0;

      op = ( sInput[ currentIdx ] == '*' ) ? Operations::MULT : Operations::ADD;
    }
    // Is bracket
    else if ( sInput[ currentIdx ] == '(' )
    {
      ++currentIdx;
      number = prepare_brakets( sInput, currentIdx );
    }
    else if ( sInput[ currentIdx ] == ')' )
    {
      break;
    }

    ++currentIdx;
  }

  result = ( op == Operations::ADD ) ? result + number
                                     : result * number;

  return result;
}


void put_bracket_left( std::string & line, std::size_t idx )
{
  int brackets { 0 };

  while( idx >= 0 )
  {
    if ( line[ idx ] == ')' )
    {
      ++brackets;
    }
    else if ( line[ idx ] == '(' )
    {
      --brackets;
    }

    if ( brackets == 0
        && (  ( line[ idx ] >= '0' && line[ idx ] <= '9' )
            ||  line[ idx ] == '(' ) )
    {
      // Put bracket
      line.insert( idx, 1, '(' );
      return;
    }

    if ( idx == 0 )
      break;

    --idx;
  }
}

void put_bracket_right( std::string & line, std::size_t idx )
{
  int brackets { 0 };

  while( idx < line.length() )
  {
    if ( line[ idx ] == ')' )
    {
      --brackets;
    }
    else if ( line[ idx ] == '(' )
    {
      ++brackets;
    }

    if ( brackets == 0
        && (    ( line[ idx ] >= '0' && line[ idx ] <= '9' )
             || line[ idx ] == ')' ) )
    {
      // Put bracket
      line.insert( idx + 1, 1, ')' );
      return;
    }

    ++idx;
  }
}

std::string modify_string( const std::string & line )
{
  std::string res = line;
  std::size_t idx = 0;

  while( idx < res.length() )
  {
    if( res[ idx ] != '+' )
    {
      ++idx;
      continue;
    }

    // put bracket left
    put_bracket_left( res, idx - 1 );

    // put bracket right
    put_bracket_right( res, idx + 2 );

    idx += 2;
  }

  return res;
}


unsigned long long prepare_input_1( const std::string & filename )
{
  std::vector< std::string > sInput = FileReader::read_file( filename );

  unsigned long long res = 0;

  for ( const auto & _line : sInput )
  {
    std::size_t idx { 0 };
    unsigned long long resOne = prepare_brakets( _line, idx );
    res += resOne;
  }

  return res;
}

unsigned long long prepare_input_2( const std::string & filename )
{
  std::vector< std::string > sInput = FileReader::read_file( filename );

  unsigned long long res = 0;

  for ( const auto & _line : sInput )
  {
    std::size_t idx { 0 };
    unsigned long long resOne = prepare_brakets( modify_string( _line ), idx );
    res += resOne;
  }

  return res;
}


unsigned long long OperationOrder::task_1( const std::string & filename )
{
  return prepare_input_1( filename );
}

unsigned long long OperationOrder::task_2( const std::string & filename )
{
  return prepare_input_2( filename );
}
