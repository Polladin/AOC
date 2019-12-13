#pragma once

#include <string>
#include <vector>


class Game
{

private:

  struct t_cell
  {
    t_cell( int _x, int _y, int _val )
      : x{ _x }, y{ _y }, val{ _val }
    {}

    int x, y, val;
  };

  using t_field = std::vector< std::vector< int > >;

public:

  int run_part_1( const std::string & fileName );

  int run_part_2( const std::string & fileName );

private:

  void print_field( const std::vector< long long > & gameOutput );
  void print_field( const t_field & field );
  void print_symbol( int val );

  void set_field( const std::vector< long long > & gameOutput, t_field & field );

  std::pair< int, int > get_max_coords( const std::vector< t_cell > & coords );
  
  int get_val( const std::vector< t_cell > & coords, int x, int y );
  
  void apply_step( const std::vector<long long>& gameOutput, t_field & field );

private:

  int score { 0 };
  int ballDirection = 0;
  std::pair< int, int > ball;
  std::pair< int, int > paddle;

};