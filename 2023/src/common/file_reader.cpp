
#include "file_reader.h"

#include <fstream>


std::vector<std::string> FileReader::read_file( const std::string & fileName )
{
  std::vector< std::string > lines;
  std::ifstream ifs ( fileName );

  if ( !ifs.is_open() )
  {
    throw "Don't able to open the file";
  }

  while ( !ifs.eof() )
  {
    std::string inLine;
    std::getline( ifs, inLine );

    lines.emplace_back( std::move( inLine ) );
  }

  return lines;
}
