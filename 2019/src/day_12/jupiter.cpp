
#include "jupiter.h"

#include "common/file_reader.h"
#include "common/common.h"

#include <sstream>
#include <iostream>
#include <vector>


int Jupiter::run_part_1( const std::string & fileName, int steps )
{
  std::vector< t_moon > moons = prepare_input( fileName );
  std::vector< t_moon > startMoons = moons;
  std::vector< t_moon > velocity;

  // Initialize velocity
  for ( int i = 0; i < moons.size(); ++i )
    velocity.emplace_back( std::array< int, 3 >{ 0, 0, 0 } );

  // Main loop
  for ( int _step = 0; _step < steps; ++_step )
  {
    //print_moons( moons, velocity );

    update_celocity( moons, velocity );

    update_position( moons, velocity );

  }

  return calc_energy( moons, velocity );
}


long long Jupiter::run_part_2( const std::string & fileName )
{
  std::vector< t_moon > moons = prepare_input( fileName );
  std::vector< t_moon > startMoons = moons;
  std::vector< t_moon > velocity;
  std::array< long long, 3 > zeroVelocityStep{0, 0, 0};
  int foundZeros = 0;

  // Initialize velocity
  for ( int i = 0; i < moons.size(); ++i )
  {
    velocity.emplace_back( std::array< int, 3 >{ 0, 0, 0 } );
  }

  // Main loop
  long long _step = 0;
  while( foundZeros != 3 )
  {
    update_celocity( moons, velocity );

    update_position( moons, velocity );


    for ( int _coord = 0; _coord < 3; ++_coord )
    {
      if ( is_the_same_coords( moons, startMoons, _coord )
          && is_velocity_zero( velocity, _coord ) )
      {
        if ( zeroVelocityStep[ _coord ] == 0 )
        {
          zeroVelocityStep[ _coord ] = _step + 1;
          ++foundZeros;
        }
      }
      
    }

    ++_step;
  }

  std::cout << "Steps: \n";
  for ( int i = 0; i < 3; ++i )
    std::cout << i << " : " << zeroVelocityStep[ i ] << "\n";
  std::cout << "\n";


  return lcm( lcm( zeroVelocityStep[ 0 ], zeroVelocityStep[ 1 ] ), zeroVelocityStep[ 2 ] );
}


std::vector< Jupiter::t_moon > Jupiter::prepare_input( const std::string & fileName )
{
  std::vector< t_moon > res;

  // Read the file
  std::vector< std::string > sInputs = FileReader::read_file( fileName );

  for ( const auto & _line : sInputs )
  {
    std::istringstream iss( _line );
    std::string param;
    std::vector< int > coords;

    while ( std::getline( iss, param, ',' ) )
      coords.emplace_back( std::stoi( param.substr( param.find('=') + 1 ) ) );
        
    res.emplace_back( std::array< int, 3 >{ coords[ 0 ], coords[ 1 ], coords[ 2 ] }  );
  }

  return res;
}

void Jupiter::update_celocity( const std::vector<t_moon>& moons, std::vector<t_moon>& velocity )
{

  for ( int moonNum = 0; moonNum < moons.size(); ++moonNum )
  {
    for ( int moonPair = 0; moonPair < moons.size(); ++moonPair )
    {
      if ( moonNum == moonPair )
        continue;

      for ( int _coord = 0; _coord < 3; ++_coord )
      {
        if ( moons[ moonNum ][ _coord ] < moons[ moonPair ][ _coord ] )
          velocity[ moonNum ][ _coord ] += 1;

        if ( moons[ moonNum ][ _coord ] > moons[ moonPair ][ _coord ] )
          velocity[ moonNum ][ _coord ] -= 1;
      }
    }
  }

}

void Jupiter::update_position( std::vector<t_moon>& moons, const std::vector<t_moon>& velocity )
{
  for ( int moonNum = 0; moonNum < moons.size(); ++moonNum )
    for ( int _coord = 0; _coord < 3; ++_coord )
      moons[ moonNum ][ _coord ] += velocity[ moonNum ][ _coord ];
}

void Jupiter::print_moons( const std::vector<t_moon>& moons, const std::vector<t_moon>& velocity )
{
  for ( int moonNum = 0; moonNum < moons.size(); ++moonNum )
  {
    std::cout << "Pos: " << moons[ moonNum ][ 0 ] << ", " << moons[ moonNum ][ 1 ] << ", " << moons[ moonNum ][ 2 ] << ", ";
    std::cout << "Vel: " << velocity[ moonNum ][ 0 ] << ", " << velocity[ moonNum ][ 1 ] << ", " << velocity[ moonNum ][ 2 ] << "\n";
  }

  std::cout << "\n";
}

int Jupiter::calc_energy( const std::vector<t_moon>& moons, const std::vector<t_moon>& velocity )
{
  int res{0};

  for ( int moonNum = 0; moonNum < moons.size(); ++moonNum )
  {
    int kin{0};
    int pot{0};

    for ( int _coord = 0; _coord < 3; ++_coord )
    {
      kin += std::abs( velocity[ moonNum ][ _coord ] );
      pot += std::abs( moons[ moonNum ][ _coord ] );
    }

    res += kin * pot;
  }

  return res;
}


bool Jupiter::is_the_same_coords( const std::vector<t_moon>& moons, const std::vector<t_moon>& startMoons, int coords )
{
  for ( int moonNum = 0; moonNum < moons.size(); ++moonNum )
    if ( moons[ moonNum ][ coords ] != startMoons[ moonNum ][ coords ] )
      return false;

  return true;
}

bool Jupiter::is_velocity_zero( const std::vector<t_moon> & velocity, int coords )
{
  for ( int moonNum = 0; moonNum < velocity.size(); ++moonNum )
    if ( velocity[ moonNum ][ coords ] != 0 )
      return false;

  return true;
}

