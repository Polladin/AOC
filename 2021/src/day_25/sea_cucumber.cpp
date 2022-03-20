//
// Created by alexey on 20.03.2022.
//

#include "sea_cucumber.h"

#include <vector>
#include <iostream>

#include "common/file_reader.h"

using t_field = std::vector< std::string >;


void print_field( const t_field & field )
{
  for( const auto & row : field )
    std::cout << row << "\n";
  std::cout << "\n";
}

t_field move_right( const t_field & field, bool & isMoved )
{
  t_field nextField ( field.size(), std::string( field[ 0 ].size(), '.' ) );

  for( std::size_t row = 0; row < field.size(); ++row )
  {
    for( std::size_t col = 0; col < field[ row ].size(); ++col )
    {
      // An empty place or a cucumber with direction to bottom
      if ( field[ row ][ col ] == '.' )
        continue;

      if ( field[ row ][ col ] == 'v' )
      {
        nextField[ row ][ col ] = field[ row ][ col ];
        continue;
      }

      const std::size_t nextCol = ( col + 1 ) % field[ row ].size();

      // Is the next place is empty
      if ( field[ row ][ nextCol ] != '.' )
      {
        nextField[ row ][ col ] = field[ row ][ col ];
        continue;
      }

      isMoved = true;

      // Move the cucumber
      nextField[ row ][ nextCol ] = field[ row ][ col ];
    }
  }

  return nextField;
}

t_field move_bottom( const t_field & field, bool & isMoved )
{
  t_field nextField ( field.size(), std::string( field[ 0 ].size(), '.' ) );

  for( std::size_t col = 0; col < field[ 0 ].size(); ++col )
  {
    for( std::size_t row = 0; row < field.size(); ++row )
    {
      // An empty place or a cucumber with direction to bottom
      if ( field[ row ][ col ] == '.' )
        continue;

      if ( field[ row ][ col ] == '>' )
      {
        nextField[ row ][ col ] = field[ row ][ col ];
        continue;
      }

      const std::size_t nextRow = ( row + 1 ) % field.size();

      // Is the next place is empty
      if ( field[ nextRow ][ col ] != '.' )
      {
        nextField[ row ][ col ] = field[ row ][ col ];
        continue;
      }

      isMoved = true;

      // Move the cucumber
      nextField[ nextRow ][ col ] = 'v';
    }
  }

  return nextField;
}

bool step( t_field & field )
{
  bool isMoved { false };

  field = move_right ( field, isMoved );
//  print_field( field );
  field = move_bottom( field, isMoved );

  return isMoved;
}

int SeaCucumber::task_1( const std::string &filename )
{
  t_field field = FileReader::read_file( filename );

  int steps = 0;

//  print_field( field );

  while( step( field ) )
  {
    ++steps;
    std::cout << "Step: " << steps << "\n";
//    print_field( field );
  }

  return steps;
}

int SeaCucumber::task_2( const std::string &filename )
{
  return 0;
}
