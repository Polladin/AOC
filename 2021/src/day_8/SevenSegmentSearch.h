//
// Created by alexey on 08.12.2021.
//

#ifndef ADVENTOFCODE2021_SEVENSEGMENTSEARCH_H
#define ADVENTOFCODE2021_SEVENSEGMENTSEARCH_H

#include <string>
#include <vector>


class SevenSegmentSearch
{
private:

  void prepare_input( const std::string & filename );

  int get_result( std::size_t idx );

public:
  int task_1( const std::string & filename );

  int task_2( const std::string & filename );

private:

  std::vector< std::vector< std::string > > left;
  std::vector< std::vector< std::string > > right;

};


#endif //ADVENTOFCODE2021_SEVENSEGMENTSEARCH_H
