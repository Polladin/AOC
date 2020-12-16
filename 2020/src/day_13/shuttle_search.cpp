//
// Created by alexpall on 16.12.2020.
//

#include "shuttle_search.h"

#include <vector>
#include <iostream>
#include <regex>

#include "common/file_reader.h"
#include "common/common.h"
#include "chinese_remains.h"


struct InputData
{
    int currentTimeId;
    std::vector< int > busIDs;
};

struct InputData2
{
  std::vector< long long > a;
  std::vector< long long > m;
};

InputData prepare_input( const std::string & filename )
{
  // Read the file
  std::vector<std::string> sInput = FileReader::read_file( filename );

  InputData data;
  data.currentTimeId = std::stoi( sInput[ 0 ] );

  std::regex getBusIDs(R"((\d+))");
  std::smatch searchResult;

  while( std::regex_search( sInput[ 1 ], searchResult, getBusIDs ) )
  {
    data.busIDs.push_back( std::stoi( searchResult[ 0 ] ) );
    sInput[ 1 ] = searchResult.suffix().str();
  }

  return data;
}

InputData2 prepare_input_2( const std::string & filename )
{
  // Read the file
  std::vector<std::string> sInput = FileReader::read_file( filename );

  InputData2 data;

  std::regex getBusIDs(R"(([^,]+))");
  std::smatch searchResult;

  long long offset = 0;

  while( std::regex_search( sInput[ 1 ], searchResult, getBusIDs ) )
  {
    if ( searchResult[ 0 ] != "x" )
    {
      long long busID = std::stoi( searchResult[ 0 ] );
      data.m.push_back( busID );

      long long busOffset = busID - offset;
      while( busOffset < 0 ) busOffset += busID;
      data.a.push_back( busOffset  % busID );
    }

    ++offset;
    sInput[ 1 ] = searchResult.suffix().str();
  }

  return data;
}


int ShuttleSearch::task_1( const std::string & filename )
{
  InputData input = prepare_input( filename );

  std::vector< std::pair< int, int > > nearestBuses;

  for ( int _busId : input.busIDs )
  {
    int nearesTimeStamp = input.currentTimeId / _busId * _busId;
    if ( nearesTimeStamp < input.currentTimeId )
      nearesTimeStamp += _busId;

    nearestBuses.emplace_back( nearesTimeStamp, _busId );
  }

  std::sort( nearestBuses.begin(), nearestBuses.end(),
             []( const std::pair< int, int > & lhs, const std::pair< int, int > & rhs )
               { return lhs.first < rhs.first; } );

  return ( nearestBuses[ 0 ].first - input.currentTimeId ) * nearestBuses[ 0 ].second;
}

long long ShuttleSearch::task_2( const std::string &filename )
{
  InputData2 input = prepare_input_2( filename );

  std::cout << "\n";
  for ( auto _num : input.a )
    std::cout << _num << " ";
  std::cout << "\n";

  std::cout << "\n";
  for ( auto _num : input.m )
    std::cout << _num << " ";
  std::cout << "\n";


  return ChineseRemains::calculate( input.a, input.m );
}
