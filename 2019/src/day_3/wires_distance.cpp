
#include "wires_distance.h"

#include "common/file_reader.h"

#include <sstream>
#include <algorithm>
#include <iostream>


int WiresDistance::run_part_1( const std::string & fileName )
{
  // Read and convert input data
  std::vector< t_wire > inputWires = prepare_input( fileName );

  auto dists_1 = add_wire( inputWires[ 0 ] );
  auto dists_2 = add_wire( inputWires[ 1 ] );

  auto intersections = get_intersections( dists_1, dists_2 );

  std::pair< int, int > point = get_nearest_intersection( intersections );

  std::cout << "Res: " << point.first << ", " << point.second << "\n";

  std::cout << "Min steps: " << get_lowest_steps( intersections ) << "\n";

  return std::abs( point.first ) + std::abs( point.second );
}



std::vector< WiresDistance::t_wire > WiresDistance::prepare_input( const std::string & inputFile )
{
  // Read the file
  std::vector< std::string > sInputs = FileReader::read_file( inputFile );
  // Result container

  std::vector< t_wire > wires;

  for ( const auto & _wire : sInputs )
  {
    // Container for wire
    t_wire inputWire;
    // Container for a wire part
    std::string inputWirePart;

    // A stream to split vlues by comma
    std::istringstream iss( _wire );

    // Read values are splitted by comma
    while ( std::getline( iss, inputWirePart, ',' ) )
      inputWire.emplace_back( inputWirePart[ 0 ], std::stoi( inputWirePart.substr( 1 ) ) );

    wires.emplace_back( std::move( inputWire ) );
  }

  return wires;
}



std::pair< WiresDistance::t_dist_coord, WiresDistance::t_dist_coord> WiresDistance::add_wire( const t_wire & wire )
{
  // Result container. X : .first Y: .second
  std::pair< t_dist_coord, t_dist_coord > res;

  // Current position
  int posX = 0;
  int posY = 0;

  int wireCost = 0;

  for ( const auto & _wire_part : wire )
  {
    // Get endpoint
    std::pair< int, int > endPoint = get_wire_part_endpoint( _wire_part, posX, posY );

    if ( _wire_part.first == 'L' || _wire_part.first == 'R' )
    {
      // Add distance to container
      if ( res.second.find( posY ) == res.second.end() )
        res.second.emplace( posY, std::list< t_distance >() );

      res.second[ posY ].emplace_back(  std::min( posX, endPoint.first )
                                      , std::max( posX, endPoint.first )
                                      , _wire_part.first == 'L' ? -wireCost : wireCost );
    }
    else // 'U', 'D'
    {
      // Add distance to container
      if ( res.first.find( posX ) == res.first.end() )
        res.first.emplace( posX, std::list< t_distance >() );

      res.first[ posX ].emplace_back(  std::min( posY, endPoint.second )
                                     , std::max( posY, endPoint.second )
                                     , _wire_part.first == 'D' ? -wireCost : wireCost );
    }

    posX = endPoint.first;
    posY = endPoint.second;

    wireCost += _wire_part.second;
  }

  return res;
}


std::pair< int, int > WiresDistance::get_wire_part_endpoint( const t_wire_part & wirePart, int posX, int posY )
{
  switch ( wirePart.first )
  {
  case 'L': return std::make_pair( posX - wirePart.second, posY );
  case 'R': return std::make_pair( posX + wirePart.second, posY );
  case 'U': return std::make_pair( posX, posY + wirePart.second );
  case 'D': return std::make_pair( posX, posY - wirePart.second );
  }
  throw "Unrecognized direction.";
}


void WiresDistance::print_dists( const std::pair<t_dist_coord, t_dist_coord>& dists )
{
  // X
  auto it = dists.first.begin();
  auto ite = dists.first.end();

  while ( it != ite )
  {
    std::cout << "X: " << ( *it ).first << "\n";

    for ( const auto & _dist : ( *it ).second )
      std::cout << "    Y:[ " << _dist.low << ", " << _dist.high << " ]\n";

    ++it;
  }

  // Y
  it = dists.second.begin();
  ite = dists.second.end();

  while ( it != ite )
  {
    std::cout << "Y: " << ( *it ).first << "\n";

    for ( const auto & _dist : ( *it ).second )
      std::cout << "    X:[ " << _dist.low << ", " << _dist.high << " ]\n";

    ++it;
  }
}


WiresDistance::t_intersections WiresDistance::get_intersections( const std::pair<t_dist_coord, t_dist_coord>& dists_1, const std::pair<t_dist_coord, t_dist_coord>& dists_2 )
{
  t_intersections res;

  // X dist_1
  for ( auto _dist : dists_1.first )
  {
    for ( const auto & _yDist : _dist.second )
    {
      int yLow  = _yDist.low;
      int yHigh = _yDist.high;

      auto yit = dists_2.second.lower_bound( yLow );
      
      while ( yit != dists_2.second.end() && ( *yit ).first < yHigh )
      {
        if ( ( *yit ).first < yLow )
        {
          ++yit;
          continue;
        }

        for ( const auto & _xDist : ( *yit ).second )
        {
          if ( _xDist.low < _dist.first && _xDist.high > _dist.first )
          {
            std::pair< int, int > intersectionPoint { _dist.first, ( *yit ).first };

            // Calculate length for the first wire
            int firstWareLength = std::abs( _yDist.lenBefore );
            if ( _yDist.lenBefore < 0 )
            {
              firstWareLength += _yDist.high - intersectionPoint.second;
            }
            else
            {
              firstWareLength += intersectionPoint.second - _yDist.low;
            }
              
            // Calculate length for the second wire
            int secondWareLength = std::abs( _xDist.lenBefore );
            if ( _xDist.lenBefore < 0 )
            {
              secondWareLength += _xDist.high - intersectionPoint.first;
            }
            else
            {
              secondWareLength += intersectionPoint.first - _xDist.low;
            }

            res.emplace_back( _dist.first, ( *yit ).first, firstWareLength + secondWareLength );
          }
        }

        ++yit;
      }

    }
  }


  // Y dist_1
  for ( auto _dist : dists_1.second )
  {
    for ( const auto & _xDist : _dist.second )
    {
      int xLow = _xDist.low;
      int xHigh = _xDist.high;

      auto xit = dists_2.first.lower_bound( xLow );

      while ( xit != dists_2.first.end() && ( *xit ).first < xHigh )
      {
        if ( ( *xit ).first < xLow )
        {
          ++xit;
          continue;
        }

        for ( const auto & _yDist : ( *xit ).second )
        {
          std::pair< int, int > intersectionPoint{ ( *xit ).first, _dist.first };

          int firstWareLength = std::abs( _yDist.lenBefore );
          if ( _yDist.lenBefore < 0 )
          {
            firstWareLength += _yDist.high - intersectionPoint.second;
          }
          else
          {
            firstWareLength += intersectionPoint.second - _yDist.low;
          }

          // Calculate length for the second wire
          int secondWareLength = std::abs( _xDist.lenBefore );
          if ( _xDist.lenBefore < 0 )
          {
            secondWareLength += _xDist.high - intersectionPoint.first;
          }
          else
          {
            secondWareLength += intersectionPoint.first - _xDist.low;
          }

          if ( _yDist.low < _dist.first && _yDist.high > _dist.first )
            res.emplace_back( ( *xit ).first, _dist.first, firstWareLength + secondWareLength );
        }

        ++xit;
      }

    }
  }


  return res;
}


std::pair<int, int> WiresDistance::get_nearest_intersection( t_intersections & intersections, int startX, int startY )
{
  std::sort( intersections.begin(), intersections.end(),
    [ startX, startY ]( const std::tuple< int, int, int > & lhs, const std::tuple< int, int, int > & rhs )
                      { 
                        return   ( std::abs( std::get< 0 >( lhs ) - startX ) + std::abs( std::get< 1 >( lhs ) - startY ) )
                               < ( std::abs( std::get< 0 >( rhs ) - startX ) + std::abs( std::get< 1 >( rhs ) - startY ) ); 
                      } );

  return { std::get< 0 >( intersections.front() ), std::get< 1 >( intersections.front() ) };
}

int WiresDistance::get_lowest_steps( t_intersections & intersections )
{
  std::sort( intersections.begin(), intersections.end(),
            []( const std::tuple< int, int, int > & lhs, const std::tuple< int, int, int > & rhs )
              { 
                return  std::get< 2 >( lhs ) < std::get< 2 >( rhs ); 
              } );

  return std::get< 2 >( intersections.front() );
}

