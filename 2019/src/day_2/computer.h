#pragma once

#include <string>
#include <vector>
#include <queue>

class Computer
{

public:

  long long run_part_1( const std::string & inputFile );

  long long run_part_2( const std::string & inputFile, int expectedResult );

  long long run_day_5_part_1( const std::string & inputFile, const std::queue< long long > & input, std::vector< long long > & output );

  std::vector< long long > prepare_day_7_part_1( const std::string & inputFile );
  bool run_day_7_part_1( const std::queue< long long >& input, std::vector< long long > & output );

  void reset_program( const std::vector< long long > & _memory );

private:

  std::vector< long long > prepare_input( const std::string & inputFile );

  void modify_1202( std::vector< long long > & opcodes, int noun = 12, int verb = 2 );

  void execute( std::vector< long long > & opcodes, long long pos = 0 );

  long long  get_reg( std::vector< long long > & opcodes, long long pos, int mode );
  void set_reg( std::vector< long long > & opcodes, long long pos, long long value, int mode );

  long long run_part_2_step( std::vector< long long > opcodes, int noun, int verb );



public:

  std::vector< long long > memory;

private:
  
  std::queue< long long > m_input;
  std::vector< long long > m_output;

  long long ipos{ 0 };
  bool isHalted{ false };

  // Relative pointer
  long long relPos{ 0 };
};