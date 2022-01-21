//
// Created by alexey on 19.01.2022.
//

#include "TrenchMap.h"

#include <vector>
#include <tuple>
#include <iostream>

#include "common/file_reader.h"

using t_field = std::vector< std::vector< int > >;
const std::size_t X_SIZE = 300;
const std::size_t Y_SIZE = 300;
const std::size_t X_OFFSET = 100;
const std::size_t Y_OFFSET = 100;


std::tuple< std::string, t_field > prepare_input( const std::string & filename )
{
  // Read the file
  std::vector< std::string > sInput = FileReader::read_file( filename );

  std::string rules = sInput[ 0 ];
  t_field field ( Y_SIZE, std::vector< int >( X_SIZE, 0 ) );

  for ( std::size_t row = 0; row < sInput.size() - 2; ++row )
    for ( std::size_t col = 0; col < sInput[ row + 2 ].length(); ++col )
      field[ Y_OFFSET + row ][ X_OFFSET + col ] = ( sInput[ row + 2 ][ col ] == '.' ) ? 0 : 1;

  return { rules, field };
}

void print_field( const t_field & field )
{
  std::cout << "\n---- Field ----\n";
  for ( std::size_t row = Y_OFFSET - 10; row < Y_OFFSET + 110; ++row )
  {
    for ( std::size_t col = X_OFFSET - 10; col < X_OFFSET + 110; ++col )
    {
      std::cout << ( field[ row ][ col ] == 1 ? "#" : "." );
    }
    std::cout << "\n";
  }
}

int bin_to_dec( const std::string & num )
{
  int res = 0;

  for ( auto _ch : num )
  {
    res *= 2;
    res += ( _ch - '0' );
  }

  return res;
}

int get_next( int row, int col, const t_field & field, const std::string & rule )
{
  std::string number;

  static const std::vector< std::vector< int > > _offsets = {  {-1, -1}, {-1,  0}, {-1,  1}
                                                             , { 0, -1}, { 0,  0}, { 0,  1}
                                                             , { 1, -1}, { 1,  0}, { 1,  1} };
  for( const auto & _off : _offsets )
    number.push_back( '0' + field[ row + _off[ 0 ] ][ col + _off[ 1 ] ] );

  return rule[ bin_to_dec( number ) ] == '.' ? 0 : 1;
}

void fill_border( t_field & field )
{
  // Top & Bottom rows
  for( auto _row : { std::size_t( 0 ), Y_SIZE - 1 } )
    for( std::size_t _col = 0; _col < X_SIZE; ++_col )
      field[ _row ][ _col ] = field[ 1 ][ 1 ];

  // Right & Left columns
  for( std::size_t _row = 0; _row < Y_SIZE; ++_row )
    for( auto _col : { std::size_t( 0 ), X_SIZE - 1 }  )
      field[ _row ][ _col ] = field[ 1 ][ 1 ];
}

t_field apply_rule( const t_field & field, const std::string & rule )
{
  t_field newField ( Y_SIZE, std::vector< int >( X_SIZE, 0 ) );

  for ( std::size_t row = 1; row < Y_SIZE - 1; ++row )
    for ( std::size_t col = 1; col < X_SIZE - 1; ++col )
      newField[ row ][ col ] = get_next( row, col, field, rule );

  fill_border( newField );

  return newField;
}

int get_amount_of_pixels( const t_field & field )
{
  int res { 0 };

  for ( std::size_t row = 0; row < Y_SIZE; ++row )
    for ( std::size_t col = 0; col < X_SIZE; ++col )
      res += field[ row ][ col ];

  return res;
}

int TrenchMap::task_1( const std::string & filename )
{
  auto [ rule, field ] = prepare_input( filename );

  print_field( field );
  field = apply_rule( field, rule );
  print_field( field );
  field = apply_rule( field, rule );
  print_field( field );

  return get_amount_of_pixels( field );
}

int TrenchMap::task_2( const std::string & filename )
{
  auto [ rule, field ] = prepare_input( filename );

  for( std::size_t i = 0; i < 50; ++i )
    field = apply_rule( field, rule );

  print_field( field );

  return get_amount_of_pixels( field );
}
