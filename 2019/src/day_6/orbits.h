#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>


class Orbits
{
private:

  using t_planet_orbits = std::multimap< std::string, std::string >;

  
public:

  int run_part_1( const std::string & fileName );
  int run_part_2( const std::string & fileName );

private:

  t_planet_orbits prepare_input( const std::string & fileName );

  int get_planet_orbits( const std::string & planet, const t_planet_orbits & orbits );

  std::vector< std::string > get_planet_path( const std::string & planet, const t_planet_orbits & orbits );

  std::string get_intersection( const std::vector< std::string > & lpath, const std::vector< std::string > & rpath );

};