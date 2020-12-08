//
// Created by alexpall on 08.12.2020.
//

#include "handheld_halting.h"

#include <sstream>
#include <set>

#include "common/file_reader.h"
#include "computer.h"



Computer::t_commands prepare_input( const std::string & filename )
{
  std::vector< std::string > sInputs = FileReader::read_file( filename );
  Computer::t_commands cmds;

  for ( const auto & _line : sInputs )
  {
    std::istringstream iss ( _line );
    std::string sCmd;
    int intCode;

    iss >> sCmd >> intCode;

    cmds.emplace_back( Computer::GET_COMMAND[ sCmd ], intCode );
  }

  return cmds;
}


int HandheldHalting::task_1( const std::string & filename )
{
  Computer comp( prepare_input( filename ) );

  std::set< int > executedLines;

  int nextLine = comp.m_currentCommand;
  int accValue = comp.m_acc;

  while ( executedLines.count( nextLine ) == 0 )
  {
    executedLines.insert( nextLine );

    comp.step();
    nextLine = comp.m_currentCommand;
    accValue = comp.m_acc;
  }

  return accValue;
}



bool checkInput( const Computer::t_commands & cmds, int & retValue )
{
  Computer comp( cmds );

  int nextLine = comp.m_currentCommand;

  std::set< int > executedLines;

  while ( executedLines.count( nextLine ) == 0 )
  {
    executedLines.insert( nextLine );

    if ( comp.step() )
    {
      retValue = comp.m_acc;
      return true;
    }

    nextLine = comp.m_currentCommand;
  }

  return false;
}


int HandheldHalting::task_2( const std::string & filename )
{
  int result;
  Computer::t_commands inputCmds = prepare_input( filename );

  static std::map< Computer::COMMANDS, Computer::COMMANDS > switchTo
          {   { Computer::COMMANDS::NOP, Computer::COMMANDS::JMP }
            , { Computer::COMMANDS::JMP, Computer::COMMANDS::NOP }  };

  for ( std::size_t idx = 0; idx < inputCmds.size(); ++idx )
  {
    if ( switchTo.count( inputCmds[ idx ].first ) )
    {
      inputCmds[ idx ].first = switchTo[ inputCmds[ idx ].first ];

      if ( checkInput( inputCmds, result ) )
        return result;

      inputCmds[ idx ].first = switchTo[ inputCmds[ idx ].first ];
    }
  }

  throw std::invalid_argument( "Answer not found!" );
}