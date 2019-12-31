#include "cards.h"

#include <iostream>
#include <unordered_map>

#include "common/file_reader.h"
#include "common/common.h"


const static std::string DEAL_INTO_STR = "deal into new stack";
const static std::string DEAL_WITH_STR = "deal with increment";
const static std::string CUT_STR = "cut";



int Cards::run_part_1( const std::string & fileName, int countCards )
{
  t_suffels shuffles = prepare_input( fileName );

  std::vector< int > cards( countCards );
  for ( int idx = 0; idx < cards.size(); ++idx )
    cards[ idx ] = idx;

  for ( const auto _shuffle : shuffles )
    cards = make_shuffle( _shuffle.first, _shuffle.second, cards );

  for ( int idx = 0; idx < cards.size(); ++idx )
    std::cout << cards[ idx ] << ", ";
  std::cout << "\n";

  //return 0;

  for ( int idx = 0; idx < cards.size(); ++idx )
    if ( cards[ idx ] == 2019 )
      return idx;

  return 0;
}

long long Cards::run_part_2( const std::string & fileName, long long pos, long long countCards )
{
  t_suffels shuffles = prepare_input( fileName );
  std::reverse( shuffles.begin(), shuffles.end() );

  bool needToFindInMap = true;

  std::unordered_map< long long, long long > posMap;

  long long idx = 0;
  long long nextCycleIdx = -1;
  long long nextPosToTest = -1;
  long long cycleToTest = -1;
  const long long lastIdx = 101741582076661ll * shuffles.size();

  while ( idx != lastIdx )
  {
    long long cmdIdx = idx % shuffles.size();

    pos = make_shuffle_back( shuffles[ cmdIdx ].first, shuffles[ cmdIdx ].second, pos, countCards );


    //if ( idx == nextCycleIdx )
    //  std::cout << "Pos : " << pos << "\n";

    //if ( idx >= nextPosToTest - 1 && idx <= nextPosToTest + 1 )
    //{
    //  if ( cycleToTest != -1 )
    //  {
    //    std::cout << "Start Pos : " << pos << "\n";
    //    if ( idx == nextPosToTest + 1 )
    //    {
    //      nextPosToTest += cycleToTest;
    //      cycleToTest = -1;
    //    }
    //  }
    //  else
    //  {
    //    std::cout << "Stop Pos : " << pos << "\n";
    //  }
    //}

    if ( needToFindInMap )
    {
      auto itMap = posMap.find( pos );
      if ( itMap != posMap.end() ) // && itMap->second % shuffles.size() == cmdIdx
      {
        const long long cycle = idx - itMap->second;
        const long long secondCyclesPart = lastIdx - itMap->second;

        cycleToTest = cycle;
        nextPosToTest =  idx + ( shuffles.size() + itMap->second % shuffles.size() - idx % shuffles.size() ) % shuffles.size();

        long long nextIdx = itMap->second + ( secondCyclesPart - secondCyclesPart % cycle );
        nextCycleIdx = idx + cycle;

        std::cout << "First iter : " << itMap->second << "\n";
        std::cout << "Second iter : " << idx << "\n";
        std::cout << "Pos : " << pos << "\n\n";
        //std::cout << "Next idx : " << nextIdx << "\n";
        //std::cout << "start cmd: " << itMap->second % shuffles.size() << " next cmd : " << nextIdx % shuffles.size() << "\n";

        //needToFindInMap = false;

        //idx = nextIdx - 1;
        //posMap.clear();
      }

      posMap[ pos ] = idx;
    }

    ++idx;
  }
  return pos;
}


Cards::t_suffels Cards::prepare_input( const std::string & fileName )
{
  t_suffels res;

  std::vector< std::string > lines = FileReader::read_file( fileName );

  for ( const auto & _line : lines )
  {
    // deal into new stack
    if ( _line.find( DEAL_INTO_STR ) != std::string::npos )
    {
      res.emplace_back( Shuffels::DEAL_INTO, 0 );
    }
    // deal with increment 7
    else if ( _line.find( DEAL_WITH_STR ) != std::string::npos )
    {
      res.emplace_back( Shuffels::DEAL_WITH, std::stoll( _line.substr( DEAL_WITH_STR.size() ) ) );
    }
    // cut -2
    else if ( _line.find( CUT_STR ) != std::string::npos )
    {
      res.emplace_back( Shuffels::CUT, std::stoll( _line.substr( CUT_STR.size() ) ) );
    }
  }

  //for ( const auto _el : res )
  //{
  //  std::cout << "Type: " << static_cast<int>( _el.first ) << " val : " << _el.second << "\n";
  //}

  return res;
}

std::vector<int> Cards::make_shuffle( Shuffels type, int val, const std::vector<int>& table )
{
  switch ( type )
  {
  case Shuffels::CUT: return cut( val, table );
  case Shuffels::DEAL_INTO: return deal_into( table );
  case Shuffels::DEAL_WITH: return deal_with( val, table );

  default:
    throw "Unknown type";
  }
}

long long Cards::make_shuffle_back( Shuffels type, long long val, long long pos, long long size )
{
  switch ( type )
  {
  case Shuffels::CUT: return cut_back( val, pos, size );
  case Shuffels::DEAL_INTO: return deal_into_back( pos, size );
  case Shuffels::DEAL_WITH: return deal_with_back( val, pos, size );

  default:
    throw "Unknown type";
  }
}

std::vector<int> Cards::cut( int val, const std::vector<int>& table )
{
  std::vector< int > res ( table.size() );

  //for ( int idx = 0; idx < table.size(); ++idx )
  //  std::cout << table[ idx ] << ", ";
  //std::cout << "\n";

  if ( val > 0 )
  {
    for ( int idx = val; idx < table.size(); ++idx )
      res[ idx - val ] = table[ idx ];

    for ( int idx = 0; idx < val; ++idx )
      res[ table.size() - val + idx ] = table[ idx ];

    //for ( int idx = 0; idx < res.size(); ++idx )
    //  std::cout << res[ idx ] << ", ";
    //std::cout << "\n";

    return res;
  }
  
  // val < 0
  val = -val;

  for ( int idx = table.size() - val; idx < table.size(); ++idx )
    res[ idx - table.size() + val ] = table[ idx ];

  for ( int idx = 0; idx < table.size() - val; ++idx )
    res[ idx + val ] = table[ idx ];

  //for ( int idx = 0; idx < res.size(); ++idx )
  //  std::cout << res[ idx ] << ", ";
  //std::cout << "\n";

  return res;
}

std::vector<int> Cards::deal_with( int val, const std::vector<int>& table )
{
  std::vector< int > res( table.size() );

  int idxRes = 0;

  for ( int idxTable = 0; idxTable < table.size(); ++idxTable )
  {
    res[ idxRes ] = table[ idxTable ];
    idxRes = ( idxRes + val ) % res.size();
  }
 
  return res;
}

std::vector<int> Cards::deal_into( const std::vector<int>& table )
{
  return std::vector<int>( table.rbegin(), table.rend() );
}

long long Cards::cut_back( long long val, long long pos, long long size )
{
  long long newPos = ( size + ( pos + val ) ) % size;
  return newPos;
}

long long Cards::deal_with_back( long long val, long long pos, long long size )
{
  while ( pos % val != 0 )
    pos += size;

  long long newPos = pos / val;
  return newPos;
}

long long Cards::deal_into_back( long long pos, long long size )
{
  long long newPos = size - pos - 1;
  return newPos;
}
