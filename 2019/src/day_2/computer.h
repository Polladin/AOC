#pragma once

#include <string>
#include <vector>


class Computer
{

public:

  int run_part_1( const std::string & inputFile );

  int run_part_2( const std::string & inputFile, int expectedResult );

private:

  std::vector< int > prepare_input( const std::string & inputFile );

  void modify_1202( std::vector< int > & opcodes, int noun = 12, int verb = 2 );

  void execute( std::vector< int > & opcodes );
  int  get_reg( std::vector< int > & opcodes, int pos );
  void set_reg( std::vector< int > & opcodes, int pos, int value );

  int run_part_2_step( std::vector< int > opcodes, int noun, int verb );
};