#include "cryostasis.h"

#include <iostream>

#include "day_2/computer.h"


using t_field = std::vector< std::vector< long long > >;


t_field make_field( const std::vector< long long > & output )
{
  t_field screen;

  int currentLine = 0;
  screen.push_back( std::vector< long long >() );

  for ( auto _el : output )
  {
    if ( _el != 10 )
    {
      screen[ currentLine ].push_back( _el );
      continue;
    }

    // _el == 10
    screen.push_back( std::vector< long long >() );
    ++currentLine;

    screen[ currentLine ].reserve( screen[ 0 ].size() );
  }

  for ( auto & _line : screen )
    if ( _line.size() != screen[ 0 ].size() )
      _line.resize( screen[ 0 ].size(), -1 );

  return screen;
}


void print_image( const std::vector< long long > & output )
{
  t_field screen = make_field( output );

  for ( int y = 0; y < screen.size(); ++y )
  {
    for ( int x = 0; x < screen[ y ].size(); ++x )
    {
      std::cout << char( screen[ y ][ x ] );
    }
    std::cout << "\n";
  }

  std::cout << "\n";
}


std::queue< long long > modify_cmd( const std::string & strCmd )
{
    std::queue< long long > cmd;

    for ( auto _ch : strCmd )
        cmd.push( _ch );
    cmd.push( 10 );

    return cmd;
}

void print_cmd( const std::vector< long long > & out )
{
    for ( int i = 0; i < out.size(); ++i )
        std::cout << ( out[ i ] != 10 ? (char)(out[ i ] ) : '\n');
    std::cout << std::endl;
}


void Cryostasis::part_1( const std::string & fileName )
{
    Computer computer;

    computer.prepare_day_7_part_1( fileName );

    std::queue< long long > in;
    std::vector< long long > out;

    computer.run_day_7_part_1( in, out );

    print_cmd( out );

    std::string strCmd;

    std::cin >> strCmd;

    while ( strCmd != "exit" )
    {
        in = modify_cmd( strCmd );
        computer.run_day_7_part_1( in, out );

        print_cmd( out );
        std::getline( std::cin, strCmd );
    }

}
