#pragma once

#include <string>
#include <vector>
#include <map>

#include "common/common.h"



class DonutMaze
{

private:

  using t_field = std::vector< std::string >;
  using t_teleports = std::multimap< std::string, std::pair< t_coord, int > >;
  using t_teleports_coords = std::multimap< t_coord, std::string, decltype( compare_coords ) >;

  class BFS
  {
  public:
    BFS( const t_field & field, const t_teleports & teleports, const t_teleports_coords & teleportsCoords )
      : m_field{ field }
      , m_teleports{ teleports }
      , m_teleportsCoords{ teleportsCoords }
    {}

    std::vector< std::vector< int > > bfs( const t_coord startPoint );

  private:

    std::vector< std::pair< t_coord, int > > get_neighbours( const t_coord pos, int level );

  private:

    const t_field            & m_field;
    const t_teleports        & m_teleports;
    const t_teleports_coords & m_teleportsCoords;

    std::vector< std::vector< std::vector< int > > > m_color;
    std::vector< std::vector< std::vector< int > > > m_distance;
    std::vector< std::vector< std::vector< std::string > > > m_path;

  };

public:

  DonutMaze()
    : m_teleportsCoords( compare_coords )
  {}

  int run_part_1( const std::string & fileName );

private:

  t_field prepare_input( const std::string & fileName );

  void find_all_teleports( const t_field & field );

private:

  t_teleports        m_teleports;
  t_teleports_coords m_teleportsCoords;

};