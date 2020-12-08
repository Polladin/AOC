//
// Created by alexpall on 08.12.2020.
//

#include "computer.h"

std::map< std::string, Computer::COMMANDS > Computer::GET_COMMAND{
          { "nop", COMMANDS::NOP }
        , { "acc", COMMANDS::ACC }
        , { "jmp", COMMANDS::JMP }               };


int Computer::step()
{
  if ( m_currentCommand == m_commands.size() )
    return true;

  if ( m_currentCommand > m_commands.size() )
    return false;

  switch( m_commands[ m_currentCommand ].first )
  {
    case COMMANDS::NOP:
      ++m_currentCommand;
      break;

    case COMMANDS::ACC:
      m_acc += m_commands[ m_currentCommand ].second;
      ++m_currentCommand;
      break;

    case COMMANDS::JMP:
      m_currentCommand += m_commands[ m_currentCommand ].second;
      break;
  }

  return false;
}
