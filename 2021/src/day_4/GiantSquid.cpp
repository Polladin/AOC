//
// Created by alexey on 04.12.2021.
//

#include "GiantSquid.h"

#include <sstream>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <iomanip>

#include "common/file_reader.h"
#include "common/log.h"




int GiantSquid::task_1( const std::string & filename )
{
  prepare_input( filename );

  for ( int _currentNum : m_randomNumbers )
  {
    // Mark the number on all boards
    mark_numbers_on_boards( _currentNum );

    // Search a winner
    std::optional< int > winner = search_winner();

    if ( !winner )
      continue;

    std::cout << "Winner: " << winner.value() << " last number: " << _currentNum << " sum:" << get_sum_unmarked_numbers( winner.value() )  << "\n";

    // Calc total score
    int score = get_sum_unmarked_numbers( winner.value() ) * _currentNum;

    return score;
  }

  return 0;
}

static std::vector< int > get_numbers_from_string( std::string str )
{
  std::vector< int > result;

  // Replace ',' to ' '
  std::replace( str.begin(), str.end(), ',', ' ' );

  // Collect numbers
  std::istringstream iss { str };
  std::copy( std::istream_iterator< int >( iss ), std::istream_iterator< int >(), std::back_inserter( result ) );

  return result;
}

std::vector< GiantSquid::Board::BoardNumber > GiantSquid::get_board_line( const std::string &str )
{
  std::vector< Board::BoardNumber > newLine;

  std::istringstream issBoardLine { str };
  for ( auto it = std::istream_iterator< int >( issBoardLine ); it != std::istream_iterator< int >(); ++it )
    newLine.emplace_back( *it );

  return newLine;
}


void GiantSquid::prepare_input( const std::string &filename )
{
  // Read the file
  std::vector< std::string > sInputs = FileReader::read_file( filename );

  // Read random numbers
  m_randomNumbers = get_numbers_from_string( sInputs[0] );

  // Read boards
  for ( std::size_t _linePos = 1; _linePos < sInputs.size(); ++ _linePos )
  {
    const auto & _line = sInputs[ _linePos ];

    // Create a new board if the line is empty
    if ( _line.empty() )
    {
      m_boards.emplace_back();
      continue;
    }

    // Add a new line with numbers to the current board
    m_boards.back().add_line( get_board_line( _line ) );
  }
}

void GiantSquid::mark_numbers_on_boards( int num )
{
  for ( auto & _board : m_boards )
    for ( auto & _line : _board.field )
      for ( auto & _boardNumber : _line )
        if ( _boardNumber.num == num )
          _boardNumber.marked = true;
}

std::optional< int > GiantSquid::search_winner() const
{
  const std::size_t rows    = m_boards[ 0 ].field.size();
  const std::size_t columns = m_boards[ 0 ].field[0].size();

  for ( std::size_t _boardIdx = 0; _boardIdx < m_boards.size(); ++_boardIdx )
  {

    // Lines
    for ( std::size_t _row = 0; _row < rows; ++_row )
    {
      size_t marked { 0 };

      for ( std::size_t _col = 0; _col < columns; ++_col )
        marked += m_boards[ _boardIdx ].field[ _row ][ _col ].marked ? 1 : 0;

      if ( marked == columns )
        return _boardIdx;
    }

    // Columns
    for ( std::size_t _col = 0; _col < columns; ++_col )
    {
      size_t marked { 0 };

      for ( std::size_t _row = 0; _row < rows; ++_row )
        marked += m_boards[ _boardIdx ].field[ _row ][ _col ].marked ? 1 : 0;

      if ( marked == rows )
        return _boardIdx;
    }
  }

  return {};
}

int GiantSquid::get_sum_unmarked_numbers( std::size_t boardIdx ) const
{
  int sum { 0 };

  for ( auto & _line : m_boards[ boardIdx ].field )
    for ( auto & _boardNumber : _line )
      sum += _boardNumber.marked ? 0 : _boardNumber.num;

  return sum;
}

void GiantSquid::print_board( const GiantSquid::Board & board ) const
{
  for ( std::size_t _row = 0; _row < board.field.size(); ++_row )
  {
    for ( std::size_t _col = 0; _col < board.field[0].size(); ++_col )
    {
      std::cout << std::setfill(' ') << std::setw( 2 ) << board.field[ _row ][ _col ].num << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";

  for ( std::size_t _row = 0; _row < board.field.size(); ++_row )
  {
    for ( std::size_t _col = 0; _col < board.field[0].size(); ++_col )
    {
      std::cout << std::setfill(' ') << std::setw( 2 ) << board.field[ _row ][ _col ].marked << " ";
    }
    std::cout << "\n";
  }
}

int GiantSquid::task_2( const std::string &filename )
{
  std::optional< int > winner;

  prepare_input( filename );

  for ( int _currentNum : m_randomNumbers )
  {
    // Mark the number on all boards
    mark_numbers_on_boards( _currentNum );

    while ( ( winner = search_winner() ) && m_boards.size() > 1 )
      m_boards.erase( std::next( m_boards.begin(), winner.value() ) );

    if ( !winner || m_boards.size() > 1 )
      continue;

    std::cout << "Last number: " << _currentNum << " sum:" << get_sum_unmarked_numbers( 0 )  << "\n";

    // Calc total score
    int score = get_sum_unmarked_numbers( 0 ) * _currentNum;

    return score;
  }

  return 0;
}
