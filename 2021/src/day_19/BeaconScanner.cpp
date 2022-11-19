//
// Created by alexey on 18.01.2022.
//

#include "BeaconScanner.h"

#include <vector>
#include <regex>
#include <iostream>
#include <functional>
#include <algorithm>
#include <optional>
#include <limits>

#include "common/file_reader.h"

struct Point3D
{
  Point3D( int i_x, int i_y, int i_z )
    : x { i_x }, y { i_y }, z { i_z }
  {}

  bool operator< ( const Point3D & rhs ) const
  {
    if ( x != rhs.x )
      return x < rhs.x;

    if ( y != rhs.y )
      return y < rhs.y;

    return z < rhs.z;
  }

  bool operator== ( const Point3D & rhs ) const
  {
    return x == rhs.x && y == rhs.y && z == rhs.z;
  }

  int x, y, z;
};

Point3D operator- ( const Point3D & lhs, const Point3D & rhs )
{
  Point3D newPoint = lhs;

  newPoint.x -= rhs.x;
  newPoint.y -= rhs.y;
  newPoint.z -= rhs.z;

  return newPoint;
}

using t_scanner = std::vector< Point3D >;
using t_scanners = std::vector< t_scanner >;


t_scanners prepare_input( const std::string & filename )
{
  // Read the file
  std::vector< std::string > sInput = FileReader::read_file( filename );

  if ( !sInput.back().empty() )
    throw std::runtime_error( "The last line must be empty!" );

  t_scanners res;
  t_scanner scanner;

  for ( const auto & _line : sInput )
  {
    // New scanner
    if ( _line.substr( 0, 3 ) == "---" )
    {
      scanner.clear();
      continue;
    }

    // End for the scanner
    if ( _line.empty() )
    {
      // Push the scanner
      scanner.push_back( Point3D( 0, 0, 0) );
      res.push_back( scanner );
      continue;
    }

    std::regex word_regex(R"(([-]?\d+),([-]?\d+),([-]?\d+))");
    std::smatch coordinates_match;
    std::regex_match( _line, coordinates_match, word_regex );

    if ( coordinates_match.size() != 4 )
      throw std::runtime_error( std::string( "Input is wrong: " ) + _line );

    scanner.emplace_back(   std::stoi( coordinates_match[ 1 ] )
                          , std::stoi( coordinates_match[ 2 ] )
                          , std::stoi( coordinates_match[ 3 ] ) );
  }

  return res;
}

void print_scanners( const t_scanners & scanners )
{
  int idx { 0 };

  for ( const auto & _scanner : scanners )
  {
    std::cout << "--- Scanner " << idx++ << " ---\n";

    for ( const auto & _coord : _scanner )
    {
      std::cout << _coord.x << "," << _coord.y << "," << _coord.z << "\n";
    }

    std::cout << "\n";
  }
}

enum FUNCTIONS
{
    X_ROTATE = 0
  , X_OPPOSITE
  , SET_HEAD_Y
  , SET_HEAD_Z
};

static const std::vector< std::function< Point3D( const Point3D & point ) > > MODIFY_FUNCS =
        {  []( const Point3D & point ) -> Point3D { return {  point.x, -point.z,  point.y }; } // X rotate
         , []( const Point3D & point ) -> Point3D { return { -point.x, -point.y,  point.z }; } // X opposite
         , []( const Point3D & point ) -> Point3D { return {  point.y, -point.x,  point.z }; } // Set head Y
         , []( const Point3D & point ) -> Point3D { return {  point.z,  point.y, -point.x }; } // Set head Z
        };

t_scanner apply_func( const t_scanner & originalScanner, const std::function< Point3D( const Point3D & point ) > & func )
{
  t_scanner newScanner;

  for ( const auto & _point : originalScanner )
    newScanner.push_back( func( _point ) );

  return newScanner;
}

t_scanner move_axes( const t_scanner & originScanner, const std::size_t zeroPoint )
{
  std::function< Point3D( const Point3D & point ) > move_func =
          [ & originScanner, zeroPoint ]( const Point3D & point ) -> Point3D { return point - originScanner[ zeroPoint ]; };

  return apply_func( originScanner, move_func );
}

t_scanner get_opposite( const t_scanner & scanner )
{
  return apply_func( scanner, MODIFY_FUNCS[ FUNCTIONS::X_OPPOSITE ] );
}

void add_x_rotations( t_scanner scanner, t_scanners & result )
{
  for ( std::size_t rotation = 0; rotation < 4; ++rotation )
  {
    result.push_back( scanner );
    scanner = apply_func( scanner, MODIFY_FUNCS[ FUNCTIONS::X_ROTATE ] );
  }
}

void add_rotations( t_scanner scanner, t_scanners & result )
{
  // Add positive rotation
  add_x_rotations( scanner, result );

  scanner = get_opposite( scanner );

  // Add negative rotation
  add_x_rotations( scanner, result );
}

t_scanners rotate_axes( const t_scanner & originScanner )
{
  t_scanners result;

  t_scanners xyzHeadScanners = {  originScanner
                                , apply_func( originScanner, MODIFY_FUNCS[ FUNCTIONS::SET_HEAD_Y ] )
                                , apply_func( originScanner, MODIFY_FUNCS[ FUNCTIONS::SET_HEAD_Z ] ) };

  for ( const auto & _scanner : xyzHeadScanners )
    add_rotations( _scanner, result );

  return result;
}

t_scanners get_axes( const t_scanner & originScanner )
{
  t_scanners res;

  for ( std::size_t _idx = 0; _idx < originScanner.size(); ++_idx )
  {
    // Move axes to a point & Get all possible axes rotations
    t_scanners movedAxesScanners = rotate_axes( move_axes( originScanner, _idx ) );

    // Add to result
    res.insert( res.end(), movedAxesScanners.begin(), movedAxesScanners.end() );
  }

  return res;
}

t_scanners get_first_axes( const t_scanner & originScanner )
{
  t_scanners res;

  for ( std::size_t _idx = 0; _idx < originScanner.size(); ++_idx )
  {
    // Move axes to a point
    res.push_back( move_axes( originScanner, _idx ) );
  }

  return res;
}

int get_intersections( const t_scanner & lhs, const t_scanner & rhs )
{
  int res { 0 };

  for ( const auto & _point : lhs )
  {
    if ( std::find( rhs.begin(), rhs.end(), _point ) != rhs.end() )
      ++res;

    if ( res >= 12 )
      break;
  }

  return res;
}

std::optional< std::pair< t_scanner, t_scanner > > compare_axes( const t_scanners & lhs, const t_scanners & rhs )
{
  for ( const auto & _lhs : lhs )
    for ( const auto & _rhs : rhs )
      if ( get_intersections( _lhs, _rhs ) >= 12 )
      {
        return { std::make_pair( _lhs, _rhs ) };
      }

  return {};
}

int BeaconScanner::task_1( const std::string & filename )
{
  t_scanners scanners = prepare_input( filename );

  int amountScanners = scanners.size();

  t_scanner currentScanner = scanners[ 0 ];
  scanners.erase( scanners.begin() );

  while ( !scanners.empty() )
  {
    for ( std::size_t _idx = 0; _idx < scanners.size(); ++_idx )
    {
      auto res = compare_axes( get_first_axes( currentScanner ), get_axes( scanners[ _idx ] ) );

      if ( !res )
        continue;

      currentScanner = res.value().first;

      for ( const auto _point : res.value().second )
      {
        if ( std::find( currentScanner.begin(), currentScanner.end(), _point ) == currentScanner.end() )
          currentScanner.push_back( _point );
      }

      scanners.erase( std::next( scanners.begin(), _idx ) );

      break;
    }

    std::cout << "Size: " << scanners.size() << "\n";
  }

  return currentScanner.size() - amountScanners;
}

int BeaconScanner::task_2( const std::string &filename )
{
  t_scanners scanners = prepare_input( filename );

  int amountScanners { 1 };

  t_scanner currentScanner = scanners[ 0 ];
  scanners.erase( scanners.begin() );

  while ( !scanners.empty() )
  {
    for ( std::size_t _idx = 0; _idx < scanners.size(); ++_idx )
    {
      auto res = compare_axes( get_first_axes( currentScanner ), get_axes( scanners[ _idx ] ) );

      if ( !res )
        continue;

      currentScanner = res.value().first;

      for ( std::size_t _pointIdx = 0; _pointIdx < res.value().second.size() - 1; ++_pointIdx )
      {
        if ( std::find( currentScanner.begin(), currentScanner.end(), res.value().second[ _pointIdx ] ) == currentScanner.end() )
          currentScanner.insert( currentScanner.end() - amountScanners,  res.value().second[ _pointIdx ] );
      }

      currentScanner.push_back( res.value().second.back() );
      ++amountScanners;

      scanners.erase( std::next( scanners.begin(), _idx ) );

      break;
    }

    std::cout << "Size: " << scanners.size() << "\n";
  }

  int maxSize = std::numeric_limits< int >::min();


  int currentScannerSize = currentScanner.size() - 1;

  for( std::size_t i1 = 0; i1 < amountScanners; ++i1 )
  {

    for ( std::size_t i2 = 0; i2 < amountScanners; ++i2 )
    {
      if ( i1 == i2 )
        continue;

      int dist =  std::abs( currentScanner[ currentScannerSize - i1 ].x - currentScanner[ currentScannerSize - i2 ].x )
                + std::abs( currentScanner[ currentScannerSize - i1 ].y - currentScanner[ currentScannerSize - i2 ].y )
                + std::abs( currentScanner[ currentScannerSize - i1 ].z - currentScanner[ currentScannerSize - i2 ].z );

      maxSize = std::max( maxSize, dist );

    }
  }

  return maxSize;
}
