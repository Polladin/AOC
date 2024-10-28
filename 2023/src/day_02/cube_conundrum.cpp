#include "cube_conundrum.h"

#include <map>

#include "common/file_reader.h"
#include "common/common.h"


using t_tries = std::map<std::string, int>;

using t_games = std::map<int, t_tries>;

const std::vector<std::string> COLORS = {"red", "green", "blue"};

// MAX: 12 red cubes, 13 green cubes, and 14 blue cubes
const t_tries MAX_TRIES = { {"red", 12}, {"green", 13}, {"blue", 14}};


t_tries get_empty_tries()
{
    t_tries result;

    for (const auto& _color : COLORS)
    {
        result[_color] = 0;
    }

    return result;
}

int get_game_number(const std::string& gameLine)
{
    // Game xxx
    const std::string num = common::split_line(gameLine, ' ')[1];
    return std::stoi(num);
}

t_tries getTry(const std::string& tryLine)
{
    t_tries result = get_empty_tries();

    // 5 blue, 4 red, 13 green;
    std::vector< std::string > cubes = common::split_line(tryLine, ',');

    for (const auto& _try : cubes)
    {
        std::vector< std::string > slittedTry = common::split_line( _try, ' ' );

        const std::string& color = common::trim( slittedTry[1] );
        const int num = std::stoi(slittedTry[0]);

        result[color] = num;
    }

    return result;
}

t_tries getMaxTry(const std::string& triesLine)
{
    std::vector< std::string > triesLines = common::split_line(triesLine, ';');

    t_tries tries = get_empty_tries();

    for (const auto& _tryLine : triesLines)
    {
        t_tries newTry = getTry( _tryLine );

        for (const auto& _color : COLORS)
        {
            tries[_color] = std::max(tries[_color], newTry[_color]);
        }
    }

    return tries;
}


t_games prepare_input(const std::string& filename)
{
    // Read the file
    std::vector< std::string > sInput = FileReader::read_file( filename );

    t_games result;

    for( const auto & _line : sInput )
    {
        if (_line.empty())
        {
            continue;
        }

        t_tries maxCubes = get_empty_tries();

        std::vector< std::string > splittedLines = common::split_line(_line, ':');

        const std::string& gameNumberLine = splittedLines[0];
        const std::string& triesLines = splittedLines[1];

        result[get_game_number(gameNumberLine)] = getMaxTry(triesLines);
    }

    return result;
}

bool isUnreal(const t_tries& tries)
{
    for (const auto& _color : COLORS)
    {
        if( tries.find( _color )->second > MAX_TRIES.find( _color )->second)
        {
            return true;
        }
    }

    return false;
}

int CubeConundrum::task_1( const std::string & filename )
{
    t_games games = prepare_input( filename );

    int result {0};

    for( auto const& [_gameNum, _tries] : games )
    {
        if (!isUnreal(_tries))
        {
            result += _gameNum;
        }
    }

    return result;
}


int CubeConundrum::task_2( const std::string & filename )
{
    t_games games = prepare_input( filename );

    int result {0};

    for( auto const& [_gameNum, _tries] : games )
    {
        int power {1};

        for (const auto& _color : COLORS)
        {
            power *= _tries.find( _color )->second;
        }

        result += power;
    }

    return result;
}
