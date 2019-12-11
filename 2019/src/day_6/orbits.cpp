#include "orbits.h"

#include "common/file_reader.h"

#include <sstream>
#include <iostream>


int Orbits::run_part_1( const std::string & fileName )
{
  t_planet_orbits orbits = prepare_input( fileName );

  int res = 0;

  for ( const auto & _planet : orbits )
  {
    res += get_planet_orbits( _planet.first, orbits );
  }

  return res;
}

int Orbits::run_part_2( const std::string & fileName )
{
  t_planet_orbits orbits = prepare_input( fileName );

  auto youPath = get_planet_path( "YOU", orbits );
  auto sanPath = get_planet_path( "SAN", orbits );

  std::string interPlanet = get_intersection( youPath, sanPath );

  size_t youLen = std::find( youPath.begin(), youPath.end(), interPlanet ) - youPath.begin();
  size_t sanLen = std::find( sanPath.begin(), sanPath.end(), interPlanet ) - sanPath.begin();

  return youLen + sanLen;
}




Orbits::t_planet_orbits Orbits::prepare_input( const std::string & fileName )
{
  t_planet_orbits res;

  // Read the file
  std::vector< std::string > sInputs = FileReader::read_file( fileName );

  // Split by ')'
  for ( const auto & _line : sInputs )
  {
    // Find the splitter
    size_t bracketPos = _line.find( ')' );

    res.emplace(  _line.substr( bracketPos + 1 )
                , _line.substr( 0, bracketPos ) );
  }

  return res;
}


int Orbits::get_planet_orbits( const std::string & planet, const t_planet_orbits & orbits )
{
  int res{ 0 };
  auto it = orbits.find( planet );


  while ( it != orbits.end() )
  {
    ++res;
    it = orbits.find( it->second );
  }

  return res;
}

std::vector< std::string > Orbits::get_planet_path( const std::string & planet, const t_planet_orbits & orbits )
{
  std::vector< std::string > path;

  auto it = orbits.find( planet );

  while ( it != orbits.end() )
  {
    path.emplace_back( it->second );
    it = orbits.find( it->second );
  }

  return path;
}

std::string Orbits::get_intersection( const std::vector< std::string > & lpath, const std::vector< std::string > & rpath )
{
  
  for ( const auto & _lplanet : lpath )
    for ( const auto & _rplanet : rpath )
      if ( _lplanet == _rplanet )
        return _lplanet;

  throw "No common planets";
}
