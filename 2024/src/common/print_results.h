//
// Created by alexey on 21.12.2021.
//
#pragma once

#include "common.h"

#include <sstream>

namespace common {

template < typename ResultType >
void print_test_result( const std::string & testNum, ResultType result )
{
  std::cout << "Res for TEST " << testNum << ": " << result << "\n" << std::endl;
}

template < typename ResultType >
void print_task_result( ResultType result )
{
  std::cout << "Res for TASK : " << result << std::endl;
}

template < typename TestedClass >
void print_results(   const std::string &day
                    , const std::string &title
                    , const std::string &enabledPart1 = "1|1"
                    , const std::string &enabledPart2 = "1|1" )
{
  std::vector< std::string > part_1 = common::split_line( enabledPart1, '|' );
  std::vector< std::string > part_2 = common::split_line( enabledPart1, '|' );

  if ( part_1.size() != 2 || part_2.size() != 2 )
    throw std::runtime_error( "Enable Part must be in format 1101|1" );

  std::cout << title << "\n";

  // ----------------- PART 1 -----------------------------------


  for ( std::size_t _part = 0; _part < 2; ++_part )
  {
    // Part 1
    if( _part == 0 && std::find( enabledPart1.begin(), enabledPart1.end(), '1' ) != enabledPart1.end())
      std::cout << "\n------------------- TASK 1: -------------------\n\n";

    // Part 2
    if( _part == 1 && std::find( enabledPart2.begin(), enabledPart2.end(), '1' ) != enabledPart2.end())
      std::cout << "\n------------------- TASK 2: -------------------\n\n";

    std::vector< std::string > enables = common::split_line( _part == 0 ? enabledPart1 : enabledPart2, '|' );

    // Part 1: TESTS
    for( std::size_t _idx = 0; _idx < enables[ 0 ].size(); ++_idx )
    {
      if( enables[ 0 ][ _idx ] == '0' )
        continue;

      // Get test num as a string
      std::string testNum = std::to_string( _idx + 1 );

      // Get full path of a test file
      std::stringstream fullTestPath;
      fullTestPath << INPUT_FILES << "/" << day << "/test_" << testNum << ".txt";

      // Run the test and print results
      _part == 0 ? print_test_result( testNum, TestedClass().task_1( fullTestPath.str() ) )
                 : print_test_result( testNum, TestedClass().task_2( fullTestPath.str() ) );
    }

    // Part 2: TESTS
    for( std::size_t _idx = 0; _idx < enables[ 1 ].size(); ++_idx )
    {
        if( enables[ 1 ][ _idx ] == '0' )
          continue;

        // Get test num as a string
        std::string testNum = std::to_string( _idx + 1 );

        // Get full path of a test file
        std::stringstream fullTestPath;
        fullTestPath << INPUT_FILES << "/" << day << "/task_" << testNum << ".txt";

        // Run the test and print results
        _part == 0 ? print_test_result( testNum, TestedClass().task_1( fullTestPath.str() ) )
                   : print_test_result( testNum, TestedClass().task_2( fullTestPath.str() ) );
    }
  }
}

//
//  std::cout << title << "\n";
//
//
//  if( test_1_enabled || task_1_enabled )
//    std::cout << "\n------------------- TASK 1: -------------------\n\n";
//
//  if( test_1_enabled )
//  {
//    auto resultTest1 = TestedClass().task_1( INPUT_FILES "/" + day + "/test_1.txt" );;
//    std::cout << "Res for TEST 1: " << resultTest1 << std::endl;
//  }
//
//  if( task_1_enabled )
//  {
//    int resultTest2 = TestedClass().task_1( INPUT_FILES "/" + day + "/task_1.txt" );;
//    std::cout << "Res for TASK 1: " << resultTest2 << std::endl;
//  }
//
//  if( test_2_enabled || task_2_enabled )
//    std::cout << "\n------------------- TASK 2: -------------------\n\n";
//
//  if( test_2_enabled )
//  {
//    auto resultTest1_2 = TestedClass().task_2( INPUT_FILES "/" + day + "/test_1.txt" );;
//    std::cout << "Res for TEST 2: " << resultTest1_2 << std::endl;
//  }
//
//  if( task_2_enabled )
//  {
//    auto resultTest2_2 = TestedClass().task_2( INPUT_FILES "/" + day + "/task_1.txt" );;
//    std::cout << "Res for TASK 2: " << resultTest2_2 << std::endl;
//  }
//}


} // namespace common
