//
// Created by alexey on 02.12.2021.
//

#ifndef ADVENTOFCODE2021_DIVE_H
#define ADVENTOFCODE2021_DIVE_H

#include <string>
#include <map>
#include <vector>


class Dive
{
  enum class Direction
  {
      FORWARD
    , DOWN
    , UP
  };

  struct Command
  {
    Command( Direction i_direction, int i_length )
      : direction{ i_direction }, length{ i_length }
    {}

    Direction direction;
    int       length;
  };

  static std::map< std::string, Direction > DIR_NAMES;

private:

  static std::vector< Command > prepare_input( const std::string & filename );

public:

  int task_1( const std::string & filename );
  int task_2( const std::string & filename );

};


#endif //ADVENTOFCODE2021_DIVE_H
