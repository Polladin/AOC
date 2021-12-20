//
// Created by alexey on 21.12.2021.
//

#include "SyntaxScoring.h"

#include <vector>
#include <stack>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>

#include "common/file_reader.h"

int get_score( const std::string & line )
{
  static const std::set< char >       OPEN_CHUNKS     { '(', '[', '{', '<' };
  static const std::map< char, char > OPPOSITE_CHUNKS { { ')', '(' }, { ']', '[' }, { '}', '{'  }, { '>', '<'   } };
  static const std::map< char, int >  SCORES          { { ')', 3   }, { ']', 57  }, { '}', 1197 }, { '>', 25137 } };
  std::stack< char > chunks;

  for ( const auto _chunk : line )
  {
    // An open chunk
    if ( OPEN_CHUNKS.count( _chunk ) )
    {
      chunks.push( _chunk );
      continue;
    }

    // An Close chunk
    if ( chunks.top() == OPPOSITE_CHUNKS.find( _chunk )->second )
    {
      chunks.pop();
      continue;
    }

    // An Error
    return SCORES.find( _chunk )->second;
  }

  return 0;
}

std::stack< char > get_rest_chunks( const std::string & line )
{
  static const std::set< char >       OPEN_CHUNKS     { '(', '[', '{', '<' };
  static const std::map< char, char > OPPOSITE_CHUNKS { { ')', '(' }, { ']', '[' }, { '}', '{'  }, { '>', '<'   } };
  std::stack< char > chunks;

  for ( const auto _chunk : line )
  {
    // An open chunk
    if ( OPEN_CHUNKS.count( _chunk ) )
    {
      chunks.push( _chunk );
      continue;
    }

    // An Close chunk
    if ( chunks.top() == OPPOSITE_CHUNKS.find( _chunk )->second )
    {
      chunks.pop();
      continue;
    }

    // An Error
    return {};
  }

  return chunks;
}

long long get_score_task_2( const std::string & line )
{
  static const std::map< char, long long > SCORES { { '(', 1   }, { '[', 2  }, { '{', 3 }, { '<', 4 } };

  std::stack< char > restChunks = get_rest_chunks( line );

  long long res { 0 };

  while( !restChunks.empty() )
  {
    res = res * 5 + SCORES.find( restChunks.top() )->second;
    restChunks.pop();
  }

  return res;
}


int SyntaxScoring::task_1( const std::string &filename )
{
  // Read the file
  std::vector< std::string > sInput = FileReader::read_file( filename );
  int res { 0 };

  for ( const auto & _line : sInput )
    res += get_score( _line );

  return res;
}


long long SyntaxScoring::task_2( const std::string &filename )
{
  // Read the file
  std::vector< std::string > sInput = FileReader::read_file( filename );
  std::vector< long long > res;

  for ( const auto & _line : sInput )
  {
    long long score = get_score_task_2( _line );
    if ( score != 0 )
      res.push_back( score );
  }

  std::sort( res.begin(), res.end() );
  return res[ res.size() / 2 ];
}
