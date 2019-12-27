#include "beam.h"

#include <array>
#include <iostream>
#include <fstream>


const int x_step = 20;
const int y_step = 20;


int Beam::run_part_1( const std::string & fileName )
{
  Computer comp;
  auto memory = comp.prepare_day_7_part_1( fileName );

  get_beam( 0, 0, comp, memory );

  //std::cout << "\nField:\n";

  int xoffset = 0;
  int yoffset = 0;

  while ( true )
  {
    get_beam( xoffset, yoffset, comp, memory );

    while ( field[ 0 ][ 100 ] != 0 || count_hor( 100, field ) == 0 || field[ XMAX - 1 ][ 100 ] != 0 )
    {
      xoffset += x_step;
      get_beam( xoffset, yoffset, comp, memory );
    }

    //while ( field[ XMAX - 1 ][ 100 ] != 0 )
    //{
    //  xoffset -= x_step;
    //  get_beam( xoffset, yoffset, comp, memory );
    //}


    auto res = is_found( field );

    std::cout << "X offset : " << xoffset << "  Y offset : " << yoffset << "\n";
    {
      std::ofstream ofs( "beam.txt" );

      for ( int y = 0; y < YMAX; ++y )
      {
        for ( int x = 0; x < XMAX; ++x )
          ofs << field[ x ][ y ];
        ofs << "\n";
      }
    }

    if ( res.first )
      return ( res.second.x + xoffset ) * 10000 + res.second.y + yoffset;

    //xoffset += XMAX - 100;
    yoffset += 20;

    

    //std::cin.get();
  }

  return 0;
}

void Beam::get_beam( int x_offset, int y_offset, Computer & comp, const std::vector< long long > & memory )
{
  std::queue< long long > input;
  std::vector< long long > out;

  for ( int x = 0; x < XMAX; ++x )
  {
    for ( int y = 0; y < YMAX; ++y )
    {
      input = std::queue< long long >();
      input.push( x + x_offset );
      input.push( y + y_offset );

      comp.reset_program( memory );
      comp.run_day_7_part_1( input, out );

      field[ x ][ y ] = out[ 0 ];
    }
  }
}

int Beam::count_hor( int idx, const std::array<std::array<int, YMAX>, XMAX>& field )
{
  int res = 0;

  for ( int x = 0; x < XMAX; ++x )
    res += field[ x ][ idx ];

  return res;
}

int Beam::count_vert( int idx, const std::array<std::array<int, YMAX>, XMAX>& field )
{
  int res = 0;

  for ( int y = 0; y < YMAX; ++y )
    res += field[ idx ][ y ];

  return res;
}

std::pair< bool, t_coord > Beam::is_found( const std::array<std::array<int, YMAX>, XMAX>& field )
{
  for ( int y = 0; y < YMAX - 100; ++y )
  {
    for ( int x = XMAX - 100; x > 0; --x )
    {
      bool isHor = true;

      for ( int i = 0; i < 100; ++i )
        if ( field[ x + i ][ y ] != 1 )
          isHor = false;

      for ( int i = 0; i < 100; ++i )
        if ( field[ x ][ y + i ] != 1 )
          isHor = false;

      if ( isHor )
        return{ true, t_coord(x, y) };
    }
  }

  return{ false, t_coord( 0, 0 ) };
}
