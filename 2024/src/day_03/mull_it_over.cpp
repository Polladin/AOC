
#include "mull_it_over.h"

#include <vector>
#include <regex>
#include <iostream>

#include "common/file_reader.h"


namespace
{

using MultCommands = std::vector< std::pair< long long, long long > >;

std::pair< long long, long long > getNewCommand( const std::smatch& smatch)
{
    if ( smatch.size() != 3 )
    {
      throw std::invalid_argument( "Must be 3 match patterns" );
    }

    long long firstNum = std::stoll( smatch[ 1 ].str() );
    long long secondNum = std::stoll( smatch[ 2 ].str() );

    return { firstNum, secondNum };
}

MultCommands prepare_input(const std::string & filename)
{
    MultCommands result;

    // Read the file
    std::vector< std::string > sInput = FileReader::read_file( filename );

    for (std::string line_ : sInput)
    {
        const std::regex multPattern(R"reg(mul\(([0-9]{1,3}),([0-9]{1,3})\))reg");

        for (std::smatch smatch; regex_search(line_, smatch, multPattern); line_ = smatch.suffix())
        {
            result.emplace_back( getNewCommand( smatch ) );
        }
    }

    return result;
}

bool turnMultCommandOnOff( const std::string& command, bool & enableMul )
{
    if ( command == "do()" )
    {
        enableMul = true;
        return true;
    }

    if ( command == "don't()" )
    {
        enableMul = false;
        return true;
    }

    return !enableMul;
}

MultCommands prepare_input_task_2(const std::string & filename)
{
    MultCommands result;

    bool enableMul { true };

    // Read the file
    std::vector< std::string > sInput = FileReader::read_file( filename );

    for (std::string line_ : sInput)
    {
        const std::regex multPattern(R"reg(mul\(([0-9]{1,3}),([0-9]{1,3})\)|don't\(\)|do\(\))reg");

        for (std::smatch smatch; regex_search(line_, smatch, multPattern); line_ = smatch.suffix())
        {
            if ( turnMultCommandOnOff( smatch.str(), enableMul ) )
            {
                continue;
            }

            result.emplace_back( getNewCommand( smatch ) );
        }
    }

    return result;
}


};// namespace

long long MullItOver::task_1(const std::string & filename)
{
    MultCommands commands = prepare_input( filename );

    long long result { 0 };

    for ( const auto & multCmd : commands )
    {
        result += multCmd.first * multCmd.second;
    }

    return result;
}

long long MullItOver::task_2(const std::string & filename)
{
    MultCommands commands = prepare_input_task_2( filename );

    long long result { 0 };

    for ( const auto & multCmd : commands )
    {
        result += multCmd.first * multCmd.second;
    }

    return result;
}
