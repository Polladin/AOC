//
// Created by alexey on 13.02.2022.
//

#include "Amphipod.h"

#include <vector>
#include <array>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>
#include <queue>

#include "common/file_reader.h"

using t_pos = std::pair< int, int >;
using t_positions = std::vector< t_pos >;

struct Score
{
  explicit Score( int i_score )
    : score{ i_score }
  {}

  int score;
  std::vector< std::pair< char, t_pos > > steps;
};

using t_field = std::vector< std::string >;
using t_field_score = std::vector< std::pair< t_field, Score > >;




static const std::map< char, int > letterPositions = { { 'A', 3 }, { 'B', 5 }, { 'C', 7 }, { 'D', 9 } };

void print_field( const t_field & field )
{
  for ( const auto & _str : field )
    std::cout << _str << '\n';
  std::cout << "----\n";
}

void print_score( const Score & score )
{
  std::cout << "Score : " << score.score << "\n";

  for ( const auto & _step : score.steps )
    std::cout << _step.first << " [" << _step.second.first << "," << _step.second.second << "]; ";
  std::cout << "\n";
}

void print_fields( const t_field_score & fields )
{
  for( const auto & _field : fields )
  {
//    if ( _field.second.score != 8513 )
//      continue;

    print_score( _field.second );
//    std::cout << "Score : " << _field.second.score << "\n";
//
//    for ( const auto & _step:_field.second.steps )
//      std::cout << _step.first << " [" << _step.second.first << "," << _step.second.second << "]; ";
//    std::cout << "\n";

    print_field( _field.first );
  }
}

void print_positions( const t_positions & pos )
{
  for ( const auto & _pos : pos )
    std:: cout << "[" << _pos.first << "," << _pos.second << "] ";
  std::cout << "\n";
}

t_field prepare_input( const std::string & filename )
{
  // Read the file
  std::vector< std::string > sInput = FileReader::read_file( filename );

  for ( auto & _str : sInput )
  {
    std::replace( _str.begin(), _str.end(), ' ', '#' );

    if ( _str.size() < sInput[ 0 ].length() )
      _str += std::string( sInput[ 0 ].length() - _str.length(), '#' );
  }

  return sInput;
}

t_positions get_positions( const t_field & data )
{
  t_positions pos;

  for ( std::size_t row = 0; row < data.size(); ++row )
  {
    for ( std::size_t col = 0; col < data[ row ].length(); ++col )
    {
      if ( !std::isalpha( data[ row ][ col ] ) )
        continue;

      pos.emplace_back( row, col );
    }
  }

  return pos;
}

bool puzzle_completed( const t_field & data, std::size_t depth )
{
  for ( const auto & _letter : letterPositions )
  {
    for ( std::size_t _currentDepth = 2; _currentDepth < depth + 2; ++_currentDepth )
    {
      if ( data[ _currentDepth ][ _letter.second ] != _letter.first )
        return false;
    }
  }

  return true;
}

bool is_right_place( const t_field & data, const t_pos & pos, std::size_t depth )
{
  char letter = data[ pos.first ][ pos.second ];

  if ( letterPositions.find( letter )->second != pos.second )
    return false;

  for ( std::size_t _row = pos.first; _row < 2 + depth; ++_row )
    if ( data[ _row ][ pos.second ] != letter )
      return false;

  return true;
}

t_positions get_next_positions( const t_field & data, const t_pos & pos  )
{
  static const std::vector< std::pair< int, int > > offsets = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

  t_positions result;

  std::queue< std::pair< int, int > > nextPositions;

  // Create an array with marks for visited nodes
  std::vector< std::vector< bool > > visited ( data.size(), std::vector< bool >( data[ 0 ].size(), false ) );

  // Push current position as a start pos and mark as visited
  nextPositions.push( pos );
  visited[ pos.first ][ pos.second ] = true;

  while( !nextPositions.empty() )
  {
    // Get the next pos
    std::pair< int, int > _currentPos = nextPositions.front();
    nextPositions.pop();

    // Find available positions
    for ( const auto & _offset : offsets )
    {
      // Is it free
      if ( data[ _currentPos.first + _offset.first ][ _currentPos.second + _offset.second ] != '.' )
        continue;

      // Isn't it visited
      if ( visited[ _currentPos.first + _offset.first ][ _currentPos.second + _offset.second ] )
        continue;

      const int newFirst  = _currentPos.first + _offset.first;
      const int newSecond = _currentPos.second + _offset.second;

      // Add the position to the queue and to result
      nextPositions.emplace( newFirst, newSecond );
      result.emplace_back  ( newFirst, newSecond );
      visited[ newFirst ][ newSecond ] = true;
    }
  }

  return result;
}

bool is_corridor_containing_other_letters( const t_field & data, const t_pos & pos, char letter, int depth )
{
  for ( std::size_t _row = 2; _row < 2 + depth; ++_row )
  {
    if (   data[ _row ][ pos.second ] != letter
        && data[ _row ][ pos.second ] != '.' )
      return true;
  }

  return false;
}

bool is_corridor_bottom_empty( const t_field & data, const t_pos & pos, int depth )
{
  for ( std::size_t _row = pos.first + 1; _row < 2 + depth; ++_row )
  {
    if ( data[ _row ][ pos.second ] == '.' )
      return true;
  }

  return false;
}

t_positions get_reasonable_positions( const t_field & data, const t_pos & oldPos, const t_positions & positions, char letter )
{
  static const std::set< int > crossroadColumns = { 3, 5, 7, 9 };

  t_positions reasonablePositions;

  for ( const auto & _pos : positions )
  {
    // Crossroads
    if ( _pos.first == 1 && crossroadColumns.count( _pos.second ) )
      continue;

    if ( _pos.first == 1 && oldPos.first == 1 )
      continue;

    if ( _pos.first == 1 )
    {
      reasonablePositions.push_back( _pos );
      continue;
    }

    // Not owned corridor
    if ( _pos.second != letterPositions.find( letter )->second )
      continue;

    // Stay with other letters
    if ( is_corridor_containing_other_letters( data, _pos, letter, 4 ) )
      continue;

    // Not the final place in the corridor
    if ( is_corridor_bottom_empty( data, _pos, 4 ) )
      continue;

    reasonablePositions.clear();
    reasonablePositions.push_back( _pos );
    break;
  }

//  std::cout << "All pos: ";
//  print_positions( positions );
//  std::cout << "Next Pos for letter: " << letter << " - ";
//  print_positions( reasonablePositions );
//  print_field( data );

  return reasonablePositions;
}

int calc_score( const t_field & data, const t_pos & originalPos, const t_pos & nextPos )
{
  static const std::map< char, int > scoreMultiplier = { { 'A', 1 }, { 'B', 10 }, { 'C', 100 }, { 'D', 1000 } };

  int len = std::abs( originalPos.second - nextPos.second ) + std::abs( originalPos.first - 1 ) + std::abs( nextPos.first - 1 );

  const int multiplier = scoreMultiplier.find( data[ originalPos.first ][ originalPos.second ] )->second;

  return len *  multiplier;
}

bool is_equal_fields( const t_field & lhs, const t_field & rhs )
{
  for( int i = 0; i < lhs.size(); ++i )
    if ( lhs[ i ] != rhs[ i ] )
      return false;

  return true;
}

bool is_resolved( const t_field & field )
{
  t_positions letters = get_positions( field );

  const auto letterInRightPlace = [ &field ]( const t_pos & letterPos )
  { return is_right_place( field, letterPos, 4 ); };

  return std::all_of( letters.begin(), letters.end(), letterInRightPlace );
}

bool is_in_next_fields( const t_field & field, t_field_score & nextFields, const Score & score )
{
//  return false;
//  for ( auto _field : nextFields )
//  {
//    if ( !is_equal_fields( field, _field.first ) )
//      continue;
//
//    if ( score.score < _field.second.score )
//    {
//      _field.second = score;
//      return true;
//    }
//  }

  if ( is_resolved( field ) )
    return false;

  auto is_fields_equal = [ &field ]( const std::pair< t_field, Score > & nextField )
                                   { return is_equal_fields( field, nextField.first ); };

  auto it = std::find_if( nextFields.begin(), nextFields.end(), is_fields_equal );

  if ( it == nextFields.end() )
    return false;

//  if (  ( score.steps[ 0 ].first == 'B' && score.steps[ 0 ].second.first == 1 && score.steps[ 0 ].second.second == 4 )
//     || ( it->second.steps[ 0 ].first == 'B' && it->second.steps[ 0 ].second.first == 1 && it->second.steps[ 0 ].second.second == 4) )
//  {
//    print_score( it->second );
//    print_field( it->first );
//    print_score( score );
//    print_field( field );
//  }

  if ( score.score < it->second.score )
  {
    it->second = score;
  }

  return true;
//  return std::any_of( nextFields.begin(), nextFields.end(), is_fields_equal );
}

void create_fields_with_step( const t_field & data, const t_pos & originalPos, const t_positions & nextPositions, t_field_score & newFields, const Score & score )
{
  for( const auto & _pos : nextPositions )
  {
    t_field newField = data;

    // Move a letter
    newField[ _pos.first ][ _pos.second ] = data[ originalPos.first ][ originalPos.second ];

    // Clear old position
    newField[ originalPos.first ][ originalPos.second ] = '.';

//    std::cout << "Created a new field with step score: " << calc_score( data, originalPos, _pos ) + score;
//    print_field( newField );

    Score newScore( score.score + calc_score( data, originalPos, _pos ) );
    newScore.steps = score.steps;
    newScore.steps.emplace_back( newField[ _pos.first ][ _pos.second ], _pos );

    if( is_in_next_fields( newField, newFields, newScore ) )
      continue;

    newFields.push_back( std::make_pair( std::move( newField ),  newScore ) );
  }
}

bool step( const t_field & data, const t_pos & pos, t_field_score & nextFields, const Score & score )
{
  // Check is it a right place
  if ( is_right_place( data, pos, 4 ) )
    return false;

  const char letter = data[ pos.first ][ pos.second ];

//  std::cout << "Step for letter: " << letter << " pos: [" << pos.first << ", " << pos.second << "]\n";

  // Get All possible positions
  t_positions nextAvailablePositions = get_next_positions( data, pos );

//  std::cout << "All next positions: ";
//  print_positions( nextAvailablePositions );

  // Remove not reasonable positions
  nextAvailablePositions = get_reasonable_positions( data, pos, nextAvailablePositions, letter );

//  std::cout << "Reasonable positions: ";
//  print_positions( nextAvailablePositions );

  if ( nextAvailablePositions.empty() )
    return false;

  // Create fields
  create_fields_with_step( data, pos, nextAvailablePositions, nextFields, score );

  return true;
}

void get_results( t_field_score & scoreFields, t_field_score & results )
{
  auto add_result = [ &results ]( const std::pair< t_field, Score > & scoreField )
  {
    if ( !is_resolved( scoreField.first ) )
      return false;

    results.push_back( scoreField );

    return true;
  };

  auto itEnd = std::remove_if( scoreFields.begin(), scoreFields.end(), add_result );
  scoreFields.erase( itEnd, scoreFields.end() );
}

int get_score( const t_field & data )
{
  t_field_score currentFields { std::make_pair( data, Score( 0 ) ) };
  t_field_score results;

  for( int _step = 0; _step < 30; ++_step )
  {
    t_field_score nextFields;

    get_results( currentFields, results );

    // Print results
    std::cout << ">>> Results: \n";
    print_fields( results );
    std::cout << "<<< Results: \n\n";

    std::cout << "Fields: " << currentFields.size() << "\n";

    for ( auto const & _scoreField : currentFields )
    {
      const t_field & _field = _scoreField.first;
      const Score     _score = _scoreField.second;

//      std::cout << "Current field score:" << _score << "\n";
//      print_field( _field );

      // Get position for all letters
      t_positions letters = get_positions( _field );

//      std::cout << "Letter pos: ";
//      print_positions( letters );

      for ( const auto & _pos : letters )
        step( _field, _pos, nextFields, _score );
    }

//    std::cout << "Next fields:\n";
//    print_fields( nextFields );

    currentFields = nextFields;
  }

  t_field winner;
  Score winnerScore ( 999999 );

  for ( const auto & _field : results )
  {
    if ( winnerScore.score > _field.second.score )
    {
      winner = _field.first;
      winnerScore = _field.second;
    }
  }

  print_score( winnerScore );
  print_field( winner );

  return 10;
}


int Amphipod::task_1( const std::string & filename )
{
  return 0;
}

int Amphipod::task_2( const std::string & filename )
{
  t_field data = prepare_input( filename );

  for ( const auto & _str : data )
    std::cout << _str << "\n";
  std::cout << "\n";

  return get_score( data );
}
