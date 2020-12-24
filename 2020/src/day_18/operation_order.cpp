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
    if ( sInput[ currentIdx ] >= '0' && sInput[ currentIdx ] <= '9' )
    {
      number = number * 10 + sInput[ currentIdx ] - '0';
    }
    else if ( sInput[ currentIdx ] == '*' || sInput[ currentIdx ] == '+' )
    {
//      std::cout << "Res: " << result << " num: " << number << std::endl;
      result = ( op == Operations::ADD ) ? result + number
                                         : result * number;
      number = 0;

      op = ( sInput[ currentIdx ] == '*' ) ? Operations::MULT : Operations::ADD;
    }
    else if ( sInput[ currentIdx ] == '(' )
    {
      ++currentIdx;
      number = prepare_brakets( sInput, currentIdx );
    }
    else if ( sInput[ currentIdx ] == ')' )
    {
//      std::cout << "Res: " << result << " num: " << number << std::endl;
      result = ( op == Operations::ADD ) ? result + number
                                         : result * number;
      ++currentIdx;
      return result;
    }

    ++currentIdx;
  }

  result = ( op == Operations::ADD ) ? result + number
                                     : result * number;

  return result;
}

unsigned long long prepare_input( const std::string & filename )
{
  std::vector< std::string > sInput = FileReader::read_file( filename );

  unsigned long long res = 0;

  for ( const auto & _line : sInput )
  {
    std::size_t idx { 0 };
    unsigned long long resOne = prepare_brakets( _line, idx );
    res += resOne;
    std::cout << _line << " = " << resOne << " Res : " << res << std::endl;
  }

  return res;
}


unsigned long long OperationOrder::task_1( const std::string & filename )
{
  return prepare_input( filename );
}
