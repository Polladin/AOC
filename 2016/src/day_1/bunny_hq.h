#pragma once

#include <string>
#include <vector>


class BunnyHQ
{
private:

  using t_move = std::pair< char, int >;


public:

  int run_part_1( const std::string & fileName );

private:

  std::vector< t_move > prepare_input( const std::string & fileName );

  std::array< int, 2 > move_to( const std::vector< t_move > & movements );

};