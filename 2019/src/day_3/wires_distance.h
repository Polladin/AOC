#pragma once

#include <vector>
#include <list>
#include <map>
#include <string>


class WiresDistance
{
private:
  
  struct t_distance
  {
    t_distance( int _low, int _high, int _lenBefore )
      : low( _low ), high( _high ), lenBefore( _lenBefore )
    {}

    int low;
    int high;
    int lenBefore;
  };

  using t_wire_part = std::pair< char, int >;
  using t_wire = std::vector< t_wire_part >;

  using t_dist = std::pair< int, int >;
  using t_dist_coord = std::map< int, std::list< t_distance > >;
  using t_dist_list = std::list< t_dist_coord >;

  using t_intersections = std::vector< std::tuple< int, int, int > >;

public:

  int run_part_1( const std::string & fileName );


private:

  std::vector< t_wire > prepare_input( const std::string & inputFile );

  std::pair< t_dist_coord, t_dist_coord > add_wire( const t_wire & wire );

  std::pair< int, int > get_wire_part_endpoint( const t_wire_part & wirePart, int posX, int posY );

  void print_dists( const std::pair< t_dist_coord, t_dist_coord > & dists );

  t_intersections get_intersections(  const std::pair< t_dist_coord, t_dist_coord > & dists_1
                                    , const std::pair< t_dist_coord, t_dist_coord > & dists_2 );

  std::pair<int, int> get_nearest_intersection( t_intersections & intersections, int startX = 0, int startY = 0 );

  int get_lowest_steps( t_intersections & intersections );

};
