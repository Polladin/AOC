#pragma once

#include <vector>
#include <array>
#include <string>


class ImageLayers
{

private:

  static const int IMAGE_WIDTH = 25;
  static const int IMAGE_HEIGHT = 6;

  using t_image = std::array< std::array< int, IMAGE_WIDTH >, IMAGE_HEIGHT >;
  using t_image_layers = std::vector< t_image >;

public:

  int run_part_1( const std::string & fileName );

  void run_part_2( const std::string & fileName );

private:

  t_image_layers prepare_input( const std::string & fileName );
  
  int get_next_color( std::string & input, int & pos );

  int calc_digit( const t_image & image, int digit );

  void merge_images( t_image & lhs, const t_image & rhs );

  void print_image( const t_image & image );
};