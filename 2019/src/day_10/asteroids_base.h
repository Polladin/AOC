#pragma once

#include <string>
#include <vector>


class AsteroidsBase
{
public:

  struct t_coords
  {
    t_coords( int _x, int _y )
      : X( _x ), Y( _y )
    {}
    int X, Y;
  };

  using t_asteroid = t_coords;


public:

  std::pair< int, t_coords > run_part_1( const std::string & fileName );

  int run_part_2( const std::string & fileName, t_asteroid center );

  static int gcd( int a, int b );

  static t_asteroid get_normolized_coordinate( const t_asteroid & asteroid );

private: 

  std::vector< t_asteroid > prepare_input( const std::string & fileName );

  int get_observed_steroids( const t_asteroid & asteroidBase, std::vector< t_asteroid > asteroids );

  std::vector< t_asteroid > get_ordered_asteroids( const t_asteroid & asteroidBase, std::vector< t_asteroid > asteroids );

  std::vector< t_asteroid > get_vapored_asteroids( std::vector< t_asteroid > sortedAsteroids );

  int get_next_pos( int pos, const t_asteroid & precAsteroid, std::vector< t_asteroid > sortedAsteroids );
};

