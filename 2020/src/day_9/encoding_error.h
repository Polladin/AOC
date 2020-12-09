#pragma once

#include <string>


class EncodingError
{
public:

    long long task_1( const std::string & filename, std::size_t preamble = 25 );

    long long task_2( const std::string & filename );
};

