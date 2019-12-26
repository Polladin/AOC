#pragma once

#include "common/common.h"

#include <set>
#include <map>
#include <queue>
#include <memory>

static const int COUNT_LETTERS = 256;


class Vault
{

private:

  struct Node
  {
    Node( int _dist, std::string _path )
      : dist{ _dist }, path{ _path }
    { }

    int dist;
    std::string path;
    std::vector< std::unique_ptr< Node > > childs;
  };

  using t_color = std::vector< std::vector< unsigned char > >;
  using t_field = std::vector< std::string >;
  using t_distance = std::map< t_coord, int, decltype( compare_coords ) >;

public:

  int run_part_1( const std::string & fileName );
  int run_part_2( const std::string & fileName );

private:

  std::map< char, int > part_2_modify( t_field & field );

  //std::unique_ptr< Vault::Node > dfs( t_coord startPoint, int distToPoint, char currentKey, const t_field & field );

  // BFS
  std::map< char, int > get_distance_to_other_keys( t_coord startPoint, const t_field & field, bool & hasDoors );

  int add_next_nodes( std::unique_ptr< Node > & head, std::map< char, int > nextNodes, const t_field & field );

  int add_next_nodes_2( std::unique_ptr< Node > & head, std::map< char, int > nextNodes, const t_field & field );

  int run_robots( const t_field & field, const std::vector< char > & robots, const std::pair< std::string, int > & path );

  void get_next_nodes( const t_coord & currentPoint, std::queue< t_coord > & que, t_color & color, const t_field & field, t_distance & dist );

  void open_doors( char key, t_field & field );

  t_coord get_start_point( const t_field & field );

  void print_field( const t_field & field );

  int get_keys_count( const t_field & field );

  void fill_keys_distance( const t_field & field );

  void remove_all_doors( t_field & field );

  std::map< char, t_coord > get_all_keys( const t_field & field );

  bool is_key_in_path( char key, const std::string & path );

private:

  // Positions for all keys
  std::map< char, t_coord > keysPosition;

  // Keys with door
  std::set< char > keysWithDoor;

  // Distance between each keys
  int keysDistance[ COUNT_LETTERS ][ COUNT_LETTERS ];

  //
  std::map< std::string, int > cache;
};