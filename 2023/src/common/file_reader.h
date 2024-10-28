#pragma once

#include <vector>
#include <string>

/**************************************************
*                  File Reader
***************************************************/
class FileReader
{

public:

  static std::vector< std::string > read_file( const std::string & fileName );

};