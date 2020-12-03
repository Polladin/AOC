//
// Created by alexpall on 03.12.2020.
//

#include "toboggan_trajectory.h"

#include "common/file_reader.h"


static const int SPACE = 0;
static const int TREE = 1;


int TobogganTrajectory::task_1( const std::string & filename )
{
  t_field inputField = prepare_input( filename );

  int trees = 0;
  std::size_t xPos = 0;

  // 3 - right (X) | 1 - down (Y)
  for ( std::size_t yPos = 0; yPos < inputField.size(); ++yPos, xPos = ( xPos + 3 ) % inputField[ 0 ].size() )
  {
    if ( inputField[ yPos ][ xPos ] == TREE )
      ++trees;
  }

  return trees;
}


long long TobogganTrajectory::task_2( const std::string & filename, const std::vector< std::pair< int, int > > & offsets)
{
  t_field inputField = prepare_input( filename );

  long long res = 1;

  for ( const auto & _offset : offsets )
  {
    int trees = 0;
    std::size_t xPos = 0;

    // 3 - right (X) | 1 - down (Y)
    for (std::size_t yPos = 0; yPos < inputField.size(); yPos = yPos + _offset.second, xPos = ( xPos + _offset.first ) % inputField[ 0 ].size() )
    {
      if (inputField[yPos][xPos] == TREE)
        ++trees;
    }

    res *= trees;
  }

  return res;
}


TobogganTrajectory::t_field TobogganTrajectory::prepare_input(const std::string &filename)
{
  // Read the file
  std::vector< std::string > sInputs = FileReader::read_file( filename );

  // Convert input data from string to int
  t_field field;
  field.resize( sInputs.size() );

  for ( std::size_t lineIdx = 0; lineIdx < sInputs.size(); ++lineIdx )
  {
    field[ lineIdx ].resize( sInputs[ lineIdx ].size() );

    for ( std::size_t _position = 0; _position < sInputs[ lineIdx ].size(); ++_position )
      field[ lineIdx ][ _position ] = ( sInputs[ lineIdx ][ _position ] == '.' ) ? SPACE : TREE;
  }

  return field;
}
