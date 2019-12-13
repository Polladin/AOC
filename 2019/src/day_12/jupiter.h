#pragma once

#include <vector>
#include <string>
#include <array>


class Jupiter
{
private:

  /*struct t_moon
  {
    t_moon(int _x, int _y, int _z)
      : x(_x), y(_y), z(_z)
    {}

    int x, y, z;
  };*/

  using t_moon = std::array< int, 3 >;

public:

  int run_part_1( const std::string & fileName, int steps );

  long long run_part_2( const std::string & fileName );

private:

  std::vector< t_moon > prepare_input( const std::string & fileName );

  void update_celocity( const std::vector< t_moon > & moons, std::vector< t_moon > & velocity );

  void update_position( std::vector< t_moon > & moons, const std::vector< t_moon > & velocity );

  void print_moons( const std::vector< t_moon > & moons, const std::vector< t_moon > & velocity );

  int calc_energy( const std::vector< t_moon > & moons, const std::vector< t_moon > & velocity );

  bool is_the_same_coords( const std::vector< t_moon > & moons, const std::vector< t_moon > & startMoons, int coords );

  bool is_velocity_zero( const std::vector< t_moon > & velocity, int coords );
};