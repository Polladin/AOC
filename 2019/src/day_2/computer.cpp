
#include "computer.h"

#include "common/file_reader.h"

#include <sstream>
#include <iostream>
#include <array>


long long Computer::run_part_1( const std::string & inputFile )
{
  std::vector< long long > inputCodes = prepare_input( inputFile );

  modify_1202( inputCodes );

  execute( inputCodes );

  //for ( auto el : inputCodes )
  //  std::cout << el << ", ";
  //std::cout << std::endl;

  return inputCodes[ 0 ];
}

long long Computer::run_part_2( const std::string & inputFile, int expectedResult )
{
  std::vector< long long > inputCodes = prepare_input( inputFile );

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

  return 0;
}


long long Computer::run_day_5_part_1( const std::string & inputFile, const std::queue< long long >& input, std::vector< long long > & output )
{
  // Initialize input
  m_input = input;
  
  // Clear output que;
  m_output.clear();

  std::vector< long long > inputCodes = prepare_input( inputFile );

  execute( inputCodes );

  // Copy output data
  output = m_output;

  return inputCodes[ 0 ];
}

void Computer::prepare_day_7_part_1( const std::string & inputFile )
{
  memory = prepare_input( inputFile );
  ipos = 0;
  isHalted = false;
  relPos = 0;
}

bool Computer::run_day_7_part_1( const std::queue< long long >& input, std::vector< long long > & output )
{
  // Initialize input
  m_input = input;

  // Clear output que;
  m_output.clear();

  execute( memory, ipos );

  // Copy output data
  output = m_output;

  return isHalted;
}


long long Computer::run_part_2_step( std::vector< long long > opcodes, int noun, int verb )
{
  modify_1202( opcodes, noun, verb );

  execute( opcodes );

  return opcodes[ 0 ];
}


std::vector< long long > Computer::prepare_input( const std::string & inputFile )
{
  // Read the file
  std::vector< std::string > sInputs = FileReader::read_file( inputFile );
  std::istringstream iss( sInputs[ 0 ] );

  // Result container
  std::vector< long long > result;
  std::string _line;

  // Read int values are splitted by comma
  while ( std::getline( iss, _line, ',' ) )
    result.push_back( std::stoll( _line ) );

  return result;
}

void Computer::modify_1202( std::vector< long long >& opcodes, int noun, int verb )
{
  opcodes[ 1 ] = noun;
  opcodes[ 2 ] = verb;
}

void Computer::execute( std::vector< long long >& opcodes, long long pos )
{
  bool stop = false;
  const int MAX_STEPS = 100000000;
  std::array< int, 3 > modes;

  for ( int i = 0; i < MAX_STEPS; ++i )
  {
    if ( i % 100000 == 0 && i > 1000 )
      std::cout << "I : " << i << "\n";

    // Inititalize parameter modes
    modes[ 0 ] = ( opcodes[ pos ] / 100   ) % 10;
    modes[ 1 ] = ( opcodes[ pos ] / 1000  ) % 10;
    modes[ 2 ] = ( opcodes[ pos ] / 10000 ) % 10;

    // Action
    switch ( opcodes[ pos ] % 100 )
    {
    case 1: // SUM
      set_reg(  opcodes
              , opcodes[ pos + 3 ], 
                get_reg( opcodes, opcodes[ pos + 1 ], modes[ 0 ] ) 
              + get_reg( opcodes, opcodes[ pos + 2 ], modes[ 1 ] )
             , modes[ 2 ] );
      pos += 4;
      break;

    case 2: // MUL
      set_reg(  opcodes
              , opcodes[ pos + 3 ]
              ,  get_reg( opcodes, opcodes[ pos + 1 ], modes[ 0 ] ) 
               * get_reg( opcodes, opcodes[ pos + 2 ], modes[ 1 ] )
              , modes[ 2 ] );
      pos += 4;
      break;

    case 3: // Input
      if ( m_input.size() == 0 )
      {
        stop = true;
        break;
      }

      set_reg( opcodes, opcodes[ pos + 1 ], m_input.front(), modes[ 0 ] );
      m_input.pop();

      pos += 2;
      break;

    case 4: // Output
      m_output.push_back( get_reg( opcodes, opcodes[ pos + 1 ], modes[ 0 ] ) );

      pos += 2;
      break;

    case 5: // jump-if-true
      if ( get_reg( opcodes, opcodes[ pos + 1 ], modes[ 0 ] ) != 0 )
        pos = get_reg( opcodes, opcodes[ pos + 2 ], modes[ 1 ] );
      else
        pos += 3;
      break;

    case 6: // jump-if-false
      if ( get_reg( opcodes, opcodes[ pos + 1 ], modes[ 0 ] ) == 0 )
        pos = get_reg( opcodes, opcodes[ pos + 2 ], modes[ 1 ] );
      else
        pos += 3;
      break;

    case 7: // less than
      if (  get_reg( opcodes, opcodes[ pos + 1 ], modes[ 0 ] )
          < get_reg( opcodes, opcodes[ pos + 2 ], modes[ 1 ] ) )
        set_reg( opcodes, opcodes[ pos + 3 ], 1, modes[ 2 ] );
      else
        set_reg( opcodes, opcodes[ pos + 3 ], 0, modes[ 2 ] );

      pos += 4;
      break;

    case 8: // equals
      if (   get_reg( opcodes, opcodes[ pos + 1 ], modes[ 0 ] )
          == get_reg( opcodes, opcodes[ pos + 2 ], modes[ 1 ] ) )
        set_reg( opcodes, opcodes[ pos + 3 ], 1, modes[ 2 ] );
      else
        set_reg( opcodes, opcodes[ pos + 3 ], 0, modes[ 2 ] );

      pos += 4;
      break;

    case 9: // Set Relative code
      relPos += get_reg( opcodes, opcodes[ pos + 1 ], modes[ 0 ] );

      pos += 2;
      break;

    case 99: // HALT
      stop = true;
      isHalted = true;
      break;
    }

    if ( stop )
    {
      ipos = pos;
      break;
    }
  }

}




long long Computer::get_reg( std::vector< long long >& opcodes, long long pos, int mode )
{
  if ( mode == 1 )
    return pos;

  if ( mode == 2 )
    return get_reg( opcodes, relPos + pos, 0 );

  if ( pos < opcodes.size() )
    return opcodes[ pos ];

  return 0;
}

void Computer::set_reg( std::vector< long long >& opcodes, long long pos, long long value, int mode )
{
  if ( mode == 2 )
    pos = relPos + pos;

  if ( pos >= opcodes.size() )
    opcodes.resize( pos + 1 );

  opcodes[ pos ] = value;
}

