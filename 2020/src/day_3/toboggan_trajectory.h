#pragma once

#include <string>
#include <vector>


class TobogganTrajectory
{
private:

    using t_field = std::vector< std::vector< int > >;

public:

    int task_1( const std::string & filename );
    long long task_2( const std::string & filename, const std::vector< std::pair< int, int > > & offsets );

private:

    t_field prepare_input( const std::string & filename );

};
