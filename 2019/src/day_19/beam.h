#pragma once

#include "day_2/computer.h"
#include "common/common.h"

#include <string>
#include <array>

static const int XMAX = 300;
static const int YMAX = 200;



class Beam
{

public:

  int run_part_1( const std::string & fileName );

private:

   void get_beam( int x_offset, int y_offset, Computer & comp, const std::vector< long long > & memory );

  int count_hor( int idx, const std::array< std::array< int, YMAX >, XMAX> & field );

  int count_vert( int idx, const std::array< std::array< int, YMAX >, XMAX> & field );

  std::pair< bool, t_coord > is_found( const std::array< std::array< int, YMAX >, XMAX> & field );

private:

  std::array< std::array< int, YMAX >, XMAX > field;

};