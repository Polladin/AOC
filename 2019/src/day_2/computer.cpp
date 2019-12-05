
#include "computer.h"

#include "common/file_reader.h"

#include <sstream>
#include <iostream>


int Computer::run_part_1( const std::string & inputFile )
{
  std::vector< int > inputCodes = prepare_input( inputFile );

  modify_1202( inputCodes );

  execute( inputCodes );

  //for ( auto el : inputCodes )
  //  std::cout << el << ", ";
  //std::cout << std::endl;

  return inputCodes[ 0 ];
}

int Computer::run_part_2( const std::string & inputFile, int expectedResult )
{
  std::vector< int > inputCodes = prepare_input( inputFile );

  for ( int noun = 0; noun < 100; ++noun )
  {
    for ( int verb = 0; verb < 100; ++verb )
    {
      if ( run_part_2_step( inputCodes, noun, verb ) == expectedResult )
        return 100 * noun + verb;

      // std::cout << "Verb: " << verb << std::endl;
    }
    
    // std::cout << "Noun: " << noun << std::endl;
  }
}

int Computer::run_part_2_step( std::vector< int > opcodes, int noun, int verb )
{
  modify_1202( opcodes, noun, verb );

  execute( opcodes );

  return opcodes[ 0 ];
}


std::vector< int > Computer::prepare_input( const std::string & inputFile )
{
  // Read the file
  std::vector< std::string > sInputs = FileReader::read_file( inputFile );
  std::istringstream iss( sInputs[ 0 ] );

  // Result container
  std::vector< int > result;
  std::string _line;

  // Read int values are splitted by comma
  while ( std::getline( iss, _line, ',' ) )
    result.push_back( std::stoi( _line ) );

  return result;
}

void Computer::modify_1202( std::vector< int >& opcodes, int noun, int verb )
{
  opcodes[ 1 ] = noun;
  opcodes[ 2 ] = verb;
}

void Computer::execute( std::vector< int >& opcodes )
{
  int pos = 0;
  bool stop = false;
  const int MAX_STEPS = 1000;

  for ( int i = 0; i < MAX_STEPS; ++i )
  {
    switch ( opcodes[ pos ] )
    {
    case 1: // SUM
      set_reg(  opcodes
              , opcodes[ pos + 3 ], 
                get_reg( opcodes, opcodes[ pos + 1 ] ) + get_reg( opcodes, opcodes[ pos + 2 ] ) );
      pos += 4;
      break;

    case 2: // MUL
      set_reg(  opcodes
              , opcodes[ pos + 3 ]
              , get_reg( opcodes, opcodes[ pos + 1 ] ) * get_reg( opcodes, opcodes[ pos + 2 ] ) );
      pos += 4;
      break;

    case 99: // HALT
      stop = true;
      break;
    }

    if ( stop )
      break;
  }

}

int Computer::get_reg( std::vector<int>& opcodes, int pos )
{
  if ( pos < opcodes.size() )
    return opcodes[ pos ];

  return 0;
}

void Computer::set_reg( std::vector<int>& opcodes, int pos, int value )
{
  if ( pos >= opcodes.size() )
    opcodes.resize( pos + 1 );

  opcodes[ pos ] = value;
}

