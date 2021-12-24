//
// Created by alexey on 24.12.2021.
//

#include "TransparentOrigami.h"

#include <vector>

#include "common/file_reader.h"
#include "common/common.h"

struct Rule
{
  Rule( bool _fold_along_X, int _fold_line )
    : fold_along_X{ _fold_along_X }
    , fold_line{ _fold_line }
  {}

  bool fold_along_X;
  int fold_line;
};

std::tuple< std::vector< t_coord >, std::vector< Rule > > prepare_input( const std::string & filename )
{
  // Read the file
  std::vector< std::string > sInput = FileReader::read_file( filename );

  std::vector< t_coord > dots;
  std::vector< Rule > rules;
  std::size_t idx = 0;

  // Read dots
  for ( ; !sInput[ idx ].empty(); ++idx )
  {
    std::vector< std::string > coordinates = common::split_line( sInput[ idx ], ',' );
    dots.emplace_back( std::atoi( coordinates[ 0 ].c_str() ), std::atoi( coordinates[ 1 ].c_str() ) );
  }

  // Skip the empty line
  ++idx;

  // Read folding rules
  for ( ; idx < sInput.size(); ++idx )
  {
    std::vector< std::string > _rule = common::split_line( sInput[ idx ], '=' );
    rules.emplace_back( _rule[ 0 ].back() == 'x', std::atoi( _rule[ 1 ].c_str() ) );
  }

  return { dots, rules };
}

int calc_dots( const std::vector< t_coord > & dots )
{
  static const std::size_t X_SIZE = 900;
  static const std::size_t Y_SIZE = 900;

  std::array< std::array< int, X_SIZE >, Y_SIZE > field;

  for ( std::size_t _y = 0; _y < Y_SIZE; ++_y )
    for ( std::size_t _x = 0; _x < X_SIZE; ++_x )
      field[ _y ][ _x ] = 0;

  for ( const auto & _dot : dots )
    field[ _dot.y ][ _dot.x ] = 1;

  int res { 0 };

  for ( std::size_t _y = 0; _y < Y_SIZE; ++_y )
    for ( std::size_t _x = 0; _x < X_SIZE; ++_x )
      res += field[ _y ][ _x ];

    return res;
}

void print_dots( const std::vector< t_coord > & dots )
{
  static const std::size_t X_SIZE = 50;
  static const std::size_t Y_SIZE = 50;

  std::array< std::array< int, X_SIZE >, Y_SIZE > field;

  for ( std::size_t _y = 0; _y < Y_SIZE; ++_y )
    for ( std::size_t _x = 0; _x < X_SIZE; ++_x )
      field[ _y ][ _x ] = 0;

  for ( const auto & _dot : dots )
    field[ _dot.y ][ _dot.x ] = 1;

  std::cout << "\n";
  for ( std::size_t _y = 0; _y < Y_SIZE; ++_y )
  {
    for ( std::size_t _x = 0; _x < X_SIZE; ++_x )
    {
      std::cout << ( field[ _y ][ _x ] == 1 ? "#" : "." );
    }
    std::cout << "\n";
  }
}

int TransparentOrigami::task_1( const std::string &filename )
{
  auto [ dots, rules ] = prepare_input( filename );

  const auto & _rule = rules[ 0 ];

  for ( auto & _dot : dots )
  {
    auto & _dotCoordinate = _rule.fold_along_X ? _dot.x : _dot.y;

    if ( _dotCoordinate > _rule.fold_line )
      _dotCoordinate = _rule.fold_line * 2 - _dotCoordinate;
  }

  return calc_dots( dots );
}

int TransparentOrigami::task_2( const std::string &filename )
{
  auto [ dots, rules ] = prepare_input( filename );

  for ( const auto & _rule : rules )
  {
    for ( auto & _dot : dots )
    {
      auto & _dotCoordinate = _rule.fold_along_X ? _dot.x : _dot.y;

      if ( _dotCoordinate > _rule.fold_line )
        _dotCoordinate = _rule.fold_line * 2 - _dotCoordinate;
    }
  }

  print_dots( dots );

  return 0;
}
