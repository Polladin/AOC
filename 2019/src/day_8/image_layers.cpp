
#include "image_layers.h"

#include "common/file_reader.h"

#include <limits>
#include <iostream>


int ImageLayers::run_part_1( const std::string & fileName )
{
  t_image_layers imageLayers = prepare_input( fileName );

  int minVal = std::numeric_limits< int >::max();
  int numLayer;

  for ( int _layer = 0; _layer < imageLayers.size(); ++_layer )
  {
    int zeros = calc_digit( imageLayers[ _layer ], 0 );
    if ( zeros < minVal )
    {
      numLayer = _layer;
      minVal = zeros;
    }
  }

  return calc_digit( imageLayers[ numLayer ], 1 ) * calc_digit( imageLayers[ numLayer ], 2 );
}

void ImageLayers::run_part_2( const std::string & fileName )
{
  t_image_layers imageLayers = prepare_input( fileName );

  for ( int _layer = 1; _layer < imageLayers.size(); ++_layer )
    merge_images( imageLayers[ 0 ], imageLayers[ _layer ] );

  print_image( imageLayers[ 0 ] );
}



ImageLayers::t_image_layers ImageLayers::prepare_input( const std::string & fileName )
{
  // Read the file
  std::vector< std::string > sInputs = FileReader::read_file( fileName );

  t_image_layers imageLayers;
  int pos = 0;

  while ( pos < sInputs[ 0 ].size() )
  {
    // Read new image
    t_image newImage;

    for ( int row = 0; row < IMAGE_HEIGHT; ++row )
      for ( int col = 0; col < IMAGE_WIDTH; ++col )
        newImage[ row ][ col ] = get_next_color( sInputs[ 0 ], pos );
  
    // Add new layer
    imageLayers.emplace_back( std::move( newImage ) );
  }
  
  return imageLayers;
}


int ImageLayers::get_next_color( std::string & input, int & pos )
{
  if ( pos >= input.size() )
    throw "Not enought inputs";

  int res = input[ pos ] - '0';
  ++pos;

  return res;
}


int ImageLayers::calc_digit( const t_image & image, int digit )
{
  int res = 0;

  for ( int row = 0; row < IMAGE_HEIGHT; ++row )
    for ( int col = 0; col < IMAGE_WIDTH; ++col )
      res += ( image[ row ][ col ] == digit ) ? 1 : 0;

  return res;
}


void ImageLayers::merge_images( t_image & lhs, const t_image & rhs )
{
  for ( int row = 0; row < IMAGE_HEIGHT; ++row )
    for ( int col = 0; col < IMAGE_WIDTH; ++col )
      if ( lhs[ row ][ col ] == 2 )
        lhs[ row ][ col ] = rhs[ row ][ col ];
}


void ImageLayers::print_image( const t_image & image )
{
  std::cout << "Image :\n";

  for ( int row = 0; row < IMAGE_HEIGHT; ++row )
  {
    for ( int col = 0; col < IMAGE_WIDTH; ++col )
    {
      std::cout << ( ( image[ row ][ col ] == 0 ) ? " " : "x" );
    }
    std::cout << "\n";
  }
  std::cout << "\n\n";
}
