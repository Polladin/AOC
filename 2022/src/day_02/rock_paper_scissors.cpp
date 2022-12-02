#include "rock_paper_scissors.h"

#include <vector>
#include <map>
#include <functional>

#include "common/file_reader.h"
#include "common/common.h"


enum class Figures
{
      Rock
    , Paper
    , Scissors
};

enum class GameResult
{
      Win
    , Lose
    , Draw
};

static const std::map< Figures, Figures > get_win_figure = {  { Figures::Rock    , Figures::Paper    }
                                                            , { Figures::Paper   , Figures::Scissors }
                                                            , { Figures::Scissors, Figures::Rock     } };

static const std::map< Figures, Figures > get_loose_figure = {  { Figures::Rock    , Figures::Scissors }
                                                              , { Figures::Paper   , Figures::Rock     }
                                                              , { Figures::Scissors, Figures::Paper    } };


static const std::map< Figures, long long > scoresFigure = {  { Figures::Rock    , 1 }
                                                            , { Figures::Paper   , 2 }
                                                            , { Figures::Scissors, 3 } };

static const std::map< GameResult, long long > scoresGameResult = {  { GameResult::Lose, 0 }
                                                                   , { GameResult::Draw, 3 }
                                                                   , { GameResult::Win , 6 } };

static const std::map< char, Figures > convertToFigures = {  { 'A', Figures::Rock     }
                                                           , { 'B', Figures::Paper    }
                                                           , { 'C', Figures::Scissors }
                                                           , { 'X', Figures::Rock     }
                                                           , { 'Y', Figures::Paper    }
                                                           , { 'Z', Figures::Scissors } };

static const std::map< char, GameResult > convertToGameResult = {  { 'X', GameResult::Lose }
                                                                 , { 'Y', GameResult::Draw }
                                                                 , { 'Z', GameResult::Win  } };

struct RoundChooses
{
    Figures opponent;
    Figures your;
};


GameResult get_game_result( const RoundChooses & choose )
{
    if ( choose.opponent == choose.your )
        return GameResult::Draw;

    switch ( choose.opponent )
    {
    case Figures::Paper    : return choose.your == Figures::Scissors ? GameResult::Win  : GameResult::Lose;
    case Figures::Rock     : return choose.your == Figures::Scissors ? GameResult::Lose : GameResult::Win ;
    case Figures::Scissors : return choose.your == Figures::Rock     ? GameResult::Win  : GameResult::Lose;
    }

    throw( "Wrong Choose" );
}

long long get_scores( const RoundChooses & choose )
{
    return  scoresFigure.find( choose.your )->second
          + scoresGameResult.find( get_game_result( choose ) )->second;
}

Figures get_your_choose( Figures opponent, GameResult expectedResult )
{
    switch ( expectedResult )
    {
    case GameResult::Win  : return get_win_figure.find( opponent )->second;
    case GameResult::Draw : return opponent;
    case GameResult::Lose : return get_loose_figure.find( opponent )->second;
    }

    throw ( "Wrong expected result" );
}

std::vector< RoundChooses > prepare_input( const std::string & filename, bool part_1 )
{
    // Read the file
    std::vector< std::string > sInput = FileReader::read_file( filename );

    std::vector< RoundChooses > res;

    for( const auto & _line : sInput )
    {
        if ( _line.empty() )
            break;

        const Figures opponent = convertToFigures.find( _line.front() )->second;
        const Figures your     = ( part_1 ? convertToFigures.find( _line.back()  )->second
                                          : get_your_choose( opponent, convertToGameResult.find( _line.back() )->second ) );

        res.emplace_back( opponent, your );
    }

    return res;
}

long long run( const std::string & filename, bool part_1 )
{
    std::vector< RoundChooses > chooses = prepare_input( filename, part_1 );

    long long res { 0 };

    for ( const auto & _choose : chooses )
        res += get_scores( _choose );

    return res;
}

long long RockPaperScissors::task_1( const std::string & filename )
{
    return run( filename, /* part_1 */ true );
}

long long RockPaperScissors::task_2(const std::string &filename)
{
    return run( filename, /* part_1 */ false );
}
