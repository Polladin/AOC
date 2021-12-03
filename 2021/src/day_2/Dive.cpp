//
// Created by alexey on 02.12.2021.
//

#include "Dive.h"

#include <sstream>
#include <iostream>

#include "common/file_reader.h"


std::map< std::string, Dive::Direction > Dive::DIR_NAMES = {  { "forward", Direction::FORWARD }
                                                            , { "down"   , Direction::DOWN    }
                                                            , { "up"     , Direction::UP      } };


int Dive::task_1( const std::string & filename )
{
  std::vector< Command > commands = prepare_input( filename );
  int depth { 0 }, horizontal { 0 };

  for ( const auto & _cmd : commands )
  {
//    std::cout << "Dir: " << static_cast< int >( _cmd.direction ) << " len: " << _cmd.length << std::endl;
    switch( _cmd.direction )
    {
      case Dive::Direction::FORWARD:
        horizontal += _cmd.length;
        break;
      case Dive::Direction::UP:
        depth -= _cmd.length;
        break;
      case Dive::Direction::DOWN:
        depth += _cmd.length;
        break;
    }
  }

  std::cout << "Depth: " << depth << " Horizontal: " << horizontal << std::endl;

  return depth * horizontal;
}

int Dive::task_2( const std::string & filename )
{
  std::vector< Command > commands = prepare_input( filename );
  int depth { 0 }, horizontal { 0 }, aim { 0 };

  for ( const auto & _cmd : commands )
  {
//    std::cout << "Dir: " << static_cast< int >( _cmd.direction ) << " len: " << _cmd.length << std::endl;
    switch( _cmd.direction )
    {
      case Dive::Direction::FORWARD:
        horizontal += _cmd.length;
        depth += aim * _cmd.length;
        break;
      case Dive::Direction::UP:
        aim -= _cmd.length;
        break;
      case Dive::Direction::DOWN:
        aim += _cmd.length;
        break;
    }
  }

  std::cout << "Depth: " << depth << " Horizontal: " << horizontal << std::endl;

  return depth * horizontal;
}

std::vector< Dive::Command > Dive::prepare_input( const std::string & filename )
{
  std::vector< Command > commands;

  // Read the file
  std::vector< std::string > sInputs = FileReader::read_file( filename );

  // Prepare command
  for ( const std::string & _sCmd : sInputs )
  {
    std::istringstream iss ( _sCmd );
    std::string cmdName;
    int cmdLength;
    iss >> cmdName >> cmdLength;
    commands.emplace_back( DIR_NAMES[ cmdName ], cmdLength );
  }

  return commands;
}
