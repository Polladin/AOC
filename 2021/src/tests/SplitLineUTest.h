//
// Created by alexey on 08.12.2021.
//

#include "common/common.h"


class SplitLineUTests
{
public:

  SplitLineUTests()
  {
    std::string test_1 { "abc | cdb" };

    std::vector< std::string > res_1 = common::split_line( test_1, '|' );

    std::cout << "Left: " << common::trim( res_1[ 0 ] ) << " Right: " << common::trim( res_1[ 1 ] ) << "\n";

    std::string test_2 { "be cfbegad cbdgef fgaecd cgeb fdcge agebfd fecdb fabcd edb | fdgacbe cefdb cefbgd gcbe" };

    std::vector< std::string > part_1 = common::split_line( test_2, '|' );
    std::vector< std::string > left   = common::split_line( common::trim( part_1[ 0 ] ), ' ' );
    std::vector< std::string > right  = common::split_line( common::trim( part_1[ 1 ] ), ' ' );

    std::cout << "Left: \n";
    for ( const auto & _elem : left )
      std::cout << _elem << ", ";
    std::cout << "\nRight: \n";
    for ( const auto & _elem : right )
      std::cout << _elem << ", ";
    std::cout << "\n";
  }
};