#pragma once

#include <string>
#include <vector>
#include <map>


class Computer
{
public:

    enum class COMMANDS
    {
          NOP
        , ACC
        , JMP
    };

    static std::map< std::string, COMMANDS > GET_COMMAND;

    using t_commands = std::vector< std::pair< COMMANDS, int > >;

public:

    Computer( t_commands && commands )
      : m_commands{ std::move( commands ) }
    {}

    Computer( const t_commands & commands )
            : m_commands{ commands }
    {}

    int step();

public:

    int m_currentCommand { 0 };
    int m_acc { 0 };
    std::vector< std::pair< COMMANDS, int > > m_commands;
};
