#include "asteroids_base.h"

#include "common/file_reader.h"

#include <algorithm>
#include <set>
#include <functional>
#include <cmath>
#include <iostream>

const double PI = 3.14159265359;


// Asteroids comparator
static std::function< bool( const AsteroidsBase::t_asteroid & lhs, const AsteroidsBase::t_asteroid & rhs ) > asteroidsComparator =
[]( const AsteroidsBase::t_asteroid & lhs, const AsteroidsBase::t_asteroid & rhs )
{
  return lhs.X == rhs.X ? lhs.Y < rhs.Y : lhs.X < rhs.X;
};


bool on_the_same_line( const AsteroidsBase::t_asteroid & lhs, const AsteroidsBase::t_asteroid & rhs )
{
  auto lhsNormal = AsteroidsBase::get_normolized_coordinate( lhs );
  auto rhsNormal = AsteroidsBase::get_normolized_coordinate( rhs );

  return lhsNormal.X == rhsNormal.X && lhsNormal.Y == rhsNormal.Y;
}


double get_sin( double X, double Y )
{
  return Y / std::sqrt( X * X + Y * Y );
}


static std::function< bool( const AsteroidsBase::t_asteroid & lhs, const AsteroidsBase::t_asteroid & rhs ) > asteroidsSortedByClockwice =
[]( const AsteroidsBase::t_asteroid & lhs, const AsteroidsBase::t_asteroid & rhs )
{
  static const double eps = 0.0001;

  // Vert Line
  if ( lhs.X == 0 && rhs.X == 0 )
    return lhs.Y < rhs.Y;

  // Horizont line
  if ( lhs.Y == 0 && rhs.Y == 0 )
    return lhs.X > rhs.X;

  // Different sides
  if ( lhs.X < 0 && rhs.X >= 0 )
    return true;

  if ( lhs.X >= 0 && rhs.X < 0 )
    return false;

  // Right side
  if ( lhs.X >= 0 && rhs.X >= 0 )
  {
    double a = get_sin( lhs.X, -lhs.Y );
    double b = get_sin( rhs.X, -rhs.Y );
    if ( std::abs( a - b ) < eps )
      return ( std::abs( lhs.X ) + std::abs( lhs.Y ) ) > ( std::abs( rhs.X ) + std::abs( rhs.Y ) );

    return get_sin( lhs.X, -lhs.Y ) < get_sin( rhs.X, -rhs.Y );
  }

  // Left side
  double a = get_sin( lhs.X, lhs.Y );
  double b = get_sin( rhs.X, rhs.Y );
  
  if ( std::abs( a - b ) < eps )
    return ( std::abs( lhs.X ) + std::abs( lhs.Y ) ) > ( std::abs( rhs.X ) + std::abs( rhs.Y ) );

  return get_sin( lhs.X, lhs.Y ) < get_sin( rhs.X, rhs.Y );
};


std::pair< int, AsteroidsBase::t_coords > AsteroidsBase::run_part_1( const std::string & fileName )
{
  std::vector< t_asteroid > asteroids = prepare_input( fileName );
  
  int res = -1;
  t_coords resCoords( asteroids[0] );

  for ( const auto & _asteroid : asteroids )
  {
    auto observedAsteroids = get_observed_steroids( _asteroid, asteroids );
    if ( res < observedAsteroids )
    {
      res = observedAsteroids;
      resCoords = _asteroid;
    }
  }

  return std::make_pair( res, resCoords );
}


int AsteroidsBase::run_part_2( const std::string & fileName, t_asteroid center )
{
  t_asteroid a{ 6, -3 };
  t_asteroid b{ 4, -2 };
  bool isRes = asteroidsSortedByClockwice(a, b);

  std::vector< t_asteroid > asteroids = prepare_input( fileName );

  // Get sorted asteroids
  auto sortedAsteroids = get_ordered_asteroids( center, asteroids );

  auto res = get_vapored_asteroids( sortedAsteroids );

  if ( res.size() > 199 )
    std::cout << res[199].X + center.X << " : " << res[199].Y + center.Y << "\n";

  //for ( const auto & _asteroid : res )
  //{
  //  std::cout << _asteroid.X + center.X << " : " << _asteroid.Y + center.Y << "\n";
  //}
  std::cout << "\n";

  return 0;
}


int AsteroidsBase::gcd( int a, int b )
{
  while ( a % b != 0 )
  {
    a = a % b;
    std::swap( a, b );
  }

  return b;
}

std::vector< AsteroidsBase::t_asteroid > AsteroidsBase::prepare_input( const std::string & fileName )
{
  // Result
  std::vector< t_asteroid > res;

  // Read the file
  std::vector< std::string > sInputs = FileReader::read_file( fileName );

  for ( int y = 0; y < sInputs.size(); ++y )
  {
    for ( int x = 0; x < sInputs[y].size(); ++x )
    {
      if ( sInputs[ y ][ x ] == '.' )
        continue;

      // Add new asteroid
      res.emplace_back( x, y );
    }
  }

  return res;
}

int AsteroidsBase::get_observed_steroids( const t_asteroid & asteroidBase, std::vector<t_asteroid> asteroids )
{
  // Normalize coordinates with center asteroid
  for ( auto & _asteroid : asteroids )
  {
    _asteroid.X -= asteroidBase.X;
    _asteroid.Y -= asteroidBase.Y;
  }

  // Create set with observed asteroids
  std::set< t_asteroid, decltype( asteroidsComparator ) > observedAsteroids( asteroidsComparator );

  for ( auto & _asteroid : asteroids )
  {
    // Center Asteroid
    if ( _asteroid.X == 0 && _asteroid.Y == 0 )
      continue;

    // Asteroid on the same X
    if ( _asteroid.X == 0 )
    {
      observedAsteroids.emplace( 0, _asteroid.Y / std::abs( _asteroid.Y ) );
      continue;
    }

    // Asteroid on the same Y
    if ( _asteroid.Y == 0 )
    {
      observedAsteroids.emplace( _asteroid.X / std::abs( _asteroid.X ), 0 );
      continue;
    }

    // Other asteroids
    auto asteroidGCD = std::abs( gcd( _asteroid.X, _asteroid.Y ) );
    observedAsteroids.emplace( _asteroid.X / asteroidGCD, _asteroid.Y / asteroidGCD );
  }

  return observedAsteroids.size();
}

AsteroidsBase::t_asteroid AsteroidsBase::get_normolized_coordinate( const t_asteroid & asteroid )
{
  // Center Asteroid
  if ( asteroid.X == 0 && asteroid.Y == 0 )
    return asteroid;

  // Asteroid on the same X
  if ( asteroid.X == 0 )
    return{ 0, asteroid.Y / std::abs( asteroid.Y ) };

  // Asteroid on the same Y
  if ( asteroid.Y == 0 )
    return{ asteroid.X / std::abs( asteroid.X ), 0 };

  // Other asteroids
  auto asteroidGCD = std::abs( gcd( asteroid.X, asteroid.Y ) );

  return { asteroid.X / asteroidGCD, asteroid.Y / asteroidGCD };
}


std::vector< AsteroidsBase::t_asteroid > AsteroidsBase::get_ordered_asteroids( const t_asteroid & asteroidBase, std::vector<t_asteroid> asteroids )
{
  std::vector< t_asteroid > res;

  // Normalize coordinates with center asteroid
  for ( auto & _asteroid : asteroids )
  {
    if ( _asteroid.X == asteroidBase.X && _asteroid.Y == asteroidBase.Y )
      continue;

    res.emplace_back( _asteroid.X - asteroidBase.X, _asteroid.Y - asteroidBase.Y );
  }

  // Sort asteroids
  std::sort( res.rbegin(), res.rend(), asteroidsSortedByClockwice );

  return res;
}

std::vector< AsteroidsBase::t_asteroid > AsteroidsBase::get_vapored_asteroids( std::vector< t_asteroid > sortedAsteroids )
{
  std::vector< t_asteroid > res{ sortedAsteroids[ 0 ] };
  t_asteroid preVapored = sortedAsteroids[0];
  sortedAsteroids.erase( sortedAsteroids.begin() );

  int pos = 0;

  while ( sortedAsteroids.size() > 0 )
  {
    pos = get_next_pos( pos, preVapored, sortedAsteroids );

    res.push_back( sortedAsteroids[ pos ] );
    preVapored = sortedAsteroids[ pos ];

    sortedAsteroids.erase( sortedAsteroids.begin() + pos );
  }

  return res;
}

int AsteroidsBase::get_next_pos( int pos, const t_asteroid & precAsteroid, std::vector< t_asteroid > sortedAsteroids )
{
  pos = pos % sortedAsteroids.size();
  int nextPos = pos;

  if ( !on_the_same_line( precAsteroid, sortedAsteroids[ nextPos ] ) )
    return nextPos;

  nextPos = ( nextPos + 1 ) % sortedAsteroids.size();

  while ( nextPos != pos )
  {
    if ( !on_the_same_line( precAsteroid, sortedAsteroids[ nextPos ] ) )
      return nextPos;

    nextPos = ( nextPos + 1 ) % sortedAsteroids.size();
  }

  return nextPos;
}
