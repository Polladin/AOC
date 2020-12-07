//
// Created by alexpall on 07.12.2020.
//

#include "custom_customs.h"

#include <set>
#include <algorithm>

#include "common/file_reader.h"


std::vector< std::string > prepare_input( const std::string & filename )
{
  // Read the file
  std::vector< std::string > sInputs = FileReader::read_file( filename );

  std::vector< std::string > result;
  std::string _str;

  for ( const auto & _line : sInputs )
  {
    if ( _line.empty() )
    {
      result.push_back( _str );
      _str.clear();
      continue;
    }

    _str += _line;
  }

  return result;
}

using t_records = std::vector< std::vector< std::string > >;

t_records prepare_input_2( const std::string & filename )
{
  // Read the file
  std::vector< std::string > sInputs = FileReader::read_file( filename );

  t_records groups;
  std::vector< std::string > group;

  for ( const auto & _line : sInputs )
  {
    if ( _line.empty() )
    {
      std::sort( group.begin(), group.end() );
      groups.push_back( group );
      group.clear();
      continue;
    }

    group.push_back( _line );
  }

  return groups;
}


int CustomCustoms::task_1(const std::string & filename)
{
  int res { 0 };

  std::vector< std::string > input = prepare_input( filename );

  for ( const auto & _inp : input )
  {
    std::set< char > _tempCounter { _inp.begin(), _inp.end() };
    res += _tempCounter.size();
  }

  return res;
}


int CustomCustoms::task_2(const std::string & filename)
{
  int res { 0 };

  t_records groups = prepare_input_2( filename );

  for ( const auto & _group : groups )
  {
    std::vector< char > _commonAnswers { _group[0].begin(), _group[0].end() };
    std::vector< char > _tmpAnswers;
    for ( std::size_t customerIdx = 1; customerIdx < _group.size(); ++customerIdx )
    {
      for ( char _answer : _commonAnswers )
      {
        if ( std::find( _group[ customerIdx ].begin(), _group[ customerIdx ].end(), _answer ) != _group[ customerIdx ].end() )
          _tmpAnswers.push_back( _answer );
      }

      _commonAnswers = _tmpAnswers;
      _tmpAnswers.clear();
    }

    res += _commonAnswers.size();
  }

  return res;
}

