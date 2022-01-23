//
// Created by alexey on 21.01.2022.
//

#include "DiracDice.h"

#include <iostream>
#include <vector>
#include <map>


int roll_dice( int & dice, int & rolls )
{
  int sum { 0 };

  for ( int i = 0; i < 3; ++i )
  {
    ++dice;
    if ( dice > 100 )
      dice = 1;

    sum += dice;
  }

  rolls += 3;

  return sum;
}

long long DiracDice::task_1( int pos1, int pos2 )
{
  long long score1 { 0 };
  long long score2 { 0 };

  int dice { 100 };
  int rolls { 0 };

  while( score1 < 1000 && score2 < 1000 )
  {
    pos1 += roll_dice( dice, rolls );
    pos1 = pos1 - ( ( pos1 - 1 ) / 10 * 10 );

    score1 += pos1;

    std::cout << "Pos 1 : " << pos1 << " score : " << score1 <<  "\n";

    if ( score1 >= 1000 )
      break;

    pos2 += roll_dice( dice, rolls );
    pos2 = pos2 - ( ( pos2 - 1 ) / 10 * 10 );

    score2 += pos2;

    std::cout << "Pos 2 : " << pos2 << " score : " << score2 <<  "\n";

  }

  return rolls * ( score1 >= 1000 ? score2 : score1 );
}

// -------------------------- TASK 2 --------------------------------

using t_players = std::vector< long long >;
using t_score = std::vector< t_players >;
using t_dice = std::map< int, int >;

t_dice get_dice_values()
{
  t_dice diceValues;

  for ( int d = 3; d <= 9; ++d )
    diceValues[ d ] = 0;

  for( int d1 = 1; d1 <= 3; ++d1 )
    for( int d2 = 1; d2 <= 3; ++d2 )
      for( int d3 = 1; d3 <= 3; ++d3 )
        ++diceValues[ d1 + d2 + d3 ];

  return diceValues;
}

t_score roll( const t_score & score, const t_dice & dice )
{
  t_score newScores = t_score ( 35, std::vector< long long >( 10, 0) );

  for( const auto & diceVal : dice )
  {
    for ( int scoreIdx = 0; scoreIdx < 21; ++scoreIdx )
    {
      for ( int posIdx = 0; posIdx < 10; ++posIdx )
      {
        // Calculate new position
        int newPos = posIdx + 1 + diceVal.first;

        // Normalize position
        newPos = newPos - ( ( newPos - 1 ) / 10 * 10 );

        // Add to score
        newScores[ scoreIdx + newPos ][ newPos - 1 ] += score[ scoreIdx ][ posIdx ] * diceVal.second;
      }
    }
  }

  return newScores;
}

long long get_not_winners( const t_score & scores )
{
  long long res { 0 };

  for ( int scoresIdx = 0; scoresIdx < 21; ++ scoresIdx )
    for ( int playerPos = 0; playerPos < 10; ++playerPos )
      res += scores[ scoresIdx ][ playerPos ];

  return res;
}

long long get_winners( const t_score & scores )
{
  long long res { 0 };

  for ( int scoresIdx = 21; scoresIdx < 35; ++ scoresIdx )
    for ( int playerPos = 0; playerPos < 10; ++playerPos )
      res += scores[ scoresIdx ][ playerPos ];

  return res;
}

void clear_winners( t_score & scores )
{
  for ( int scoresIdx = 21; scoresIdx < 35; ++ scoresIdx )
    for ( int playerPos = 0; playerPos < 10; ++playerPos )
      scores[ scoresIdx ][ playerPos ] = 0;
}

void check_winners( const t_score & scoresP1, const t_score & scoresP2, long long & winners1, long long & winners2 )
{
  winners1 += get_winners( scoresP1 ) * get_not_winners( scoresP2 );
  winners2 += get_winners( scoresP2 ) * get_not_winners( scoresP1 );
}

std::tuple< long long, long long > play_game( t_score & scoresP1, t_score & scoresP2 )
{
  long long winners1 { 0 };
  long long winners2 { 0 };

  // Initialize the dice
  t_dice dice = get_dice_values();

  while( get_not_winners( scoresP1 ) > 0  && get_not_winners( scoresP2 ) > 0 )
  {
    // Player 1 roll
    scoresP1 = roll( scoresP1, dice );

    check_winners( scoresP1, scoresP2, winners1, winners2 );
    clear_winners( scoresP1 );

    // Player 2 roll
    scoresP2 = roll( scoresP2, dice );

    check_winners( scoresP1, scoresP2, winners1, winners2 );
    clear_winners( scoresP2 );
  }

  return { winners1, winners2 };
}

long long DiracDice::task_2( int pos1, int pos2 )
{
  t_score scoresP1 = t_score ( 35, std::vector< long long >( 10, 0) );
  t_score scoresP2 = t_score ( 35, std::vector< long long >( 10, 0) );

  // Set start positions
  scoresP1[ 0 ][ pos1 - 1 ] = 1;
  scoresP2[ 0 ][ pos2 - 1 ] = 1;

  // Play
  auto [ winners1, winners2 ] = play_game( scoresP1, scoresP2 );

  std::cout << "Winner 1: " << winners1 << " winner 2: " << winners2 << "\n";

  return std::max( winners1, winners2 );
}
