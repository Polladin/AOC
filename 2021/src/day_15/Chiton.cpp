//
// Created by alexey on 26.12.2021.
//

#include "Chiton.h"

#include <vector>
#include <queue>
#include <numeric>
#include <limits>

#include "common/file_reader.h"
#include "common/common.h"

using t_array = std::vector< std::vector< int > >;


t_array prepare_input( const std::string & filename )
{
  // Read the file
  std::vector< std::string > sInput = FileReader::read_file( filename );

  t_array res ( sInput.size(), std::vector< int >( sInput[ 0 ].size(), 0 ) );

  for ( std::size_t _y = 0; _y < sInput.size(); ++_y )
    for ( std::size_t _x = 0; _x < sInput[ _y ].size(); ++_x )
      res[ _y ][ _x ] = sInput[ _y ][ _x ] - '0';

  return res;
}

t_array prepare_input_task_2( const std::string & filename )
{
  t_array original = prepare_input( filename );
  const int xLength = static_cast< int >( original[ 0 ].size() );
  const int yLength = static_cast< int >( original.size() );

  t_array newField = t_array ( yLength * 5, std::vector< int >( xLength * 5, 0 ) );

  for ( std::size_t _column = 0; _column < 5; ++_column )
  {
    for ( std::size_t _row = 0; _row < 5; ++_row )
    {
      const std::size_t yOffset = _column * yLength;
      const std::size_t xOffset = _row * xLength;

      for( std::size_t _y = 0; _y < yLength; ++_y )
      {
        for( std::size_t _x = 0; _x < xLength; ++_x )
        {
          int newVal = original[ _y ][ _x ] + static_cast< int >( _column + _row );
          newVal = ( newVal > 9 ) ? newVal - 9 : newVal;
          newField[ _y + yOffset ][ _x + xOffset ] = newVal;
        }
      }
    }
  }

  return newField;
}


int breath_search( const t_array & weights  )
{
  const int xLength = static_cast< int >( weights[ 0 ].size() );
  const int yLength = static_cast< int >( weights.size() );

  std::queue< t_coord > nextPoints;

  t_array lengths ( yLength, std::vector< int >( xLength, std::numeric_limits< int >::max() ) );
  static const std::vector< std::pair< int, int > > offsets = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

  // Push the start point
  nextPoints.emplace( 0, 0 );
  lengths[ 0 ][ 0 ] = 0;

  while( !nextPoints.empty() )
  {
    // Pop the next point
    t_coord currentPoint = nextPoints.front();
    nextPoints.pop();

    // Update a length for all neighbours
    for ( const auto _offset : offsets )
    {
      int newX = currentPoint.x + _offset.first;
      int newY = currentPoint.y + _offset.second;

      if (   newX < 0 || newX >= xLength
          || newY < 0 || newY >= yLength )
      {
        continue;
      }

      int newLength = lengths[ currentPoint.y ][ currentPoint.x ] + weights[ newY ][ newX ];

      if ( lengths[ newY ][ newX ] > newLength )
      {
        lengths[ newY ][ newX ] = newLength;
        nextPoints.emplace( newX, newY );
      }
    }
  }


  return lengths[ yLength - 1 ][ xLength - 1 ];
}


int Chiton::task_1( const std::string & filename )
{
  t_array weights = prepare_input( filename );

  return breath_search( weights );
}

int Chiton::task_2( const std::string & filename )
{
  t_array weights = prepare_input_task_2( filename );

  return breath_search( weights );
}
