
#include "password_philosophy.h"

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <array>
#include <sstream>
#include <regex>

#include "common/file_reader.h"


int PasswordPhilosophy::task_1( const std::string &filename )
{
  int validatedPasswords = 0;

  std::vector< PasswordPhilosophy::Record > records = prepare_input( filename );

  for ( const auto & _record : records )
  {
    int numberSpecialSymbols { 0 };

    for ( auto it = _record.password.begin(); it != _record.password.end(); ++it )
      if( *it == _record.symbol )
        ++numberSpecialSymbols;

    if ( numberSpecialSymbols >= _record.low && numberSpecialSymbols <= _record.high )
      ++validatedPasswords;
  }


  return validatedPasswords;
}

int PasswordPhilosophy::task_2( const std::string &filename )
{
  int validatedPasswords = 0;

  std::vector< PasswordPhilosophy::Record > records = prepare_input( filename );

  for ( const auto & _record : records )
  {
    if (   _record.password[ _record.low  - 1 ] != _record.symbol
        && _record.password[ _record.high - 1 ] != _record.symbol )
      continue;

    if (   _record.password[ _record.low  - 1 ] == _record.symbol
        && _record.password[ _record.high - 1 ] == _record.symbol )
      continue;

    ++validatedPasswords;
  }


  return validatedPasswords;
}


std::vector< PasswordPhilosophy::Record > PasswordPhilosophy::prepare_input( const std::string & filename )
{
  // Read the file
  std::vector< std::string > sInputs = FileReader::read_file( filename );

  // Convert input data from string to int
  std::vector< Record > inputs;
  inputs.reserve( sInputs.size() );

  for ( const auto & _line : sInputs )
  {
    std::regex word_regex(R"((\d+)-(\d+) (.): (\w+))");
    std::smatch pieces_match;
    std::regex_match(_line, pieces_match, word_regex);

    if ( pieces_match.size() != 5 )
      throw std::invalid_argument( "Must be 4 arguments" );

    Record rec;
    rec.low  = std::stoi( pieces_match[ 1 ].str() );
    rec.high =  std::stoi(pieces_match[ 2 ].str() );
    rec.symbol = pieces_match[3].str()[ 0 ];
    rec.password = pieces_match[4].str();

    inputs.push_back( std::move( rec ) );
  }

  return inputs;
}
