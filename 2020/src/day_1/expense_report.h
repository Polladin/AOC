#pragma once

#include <string>
#include <vector>


class ExpenseReport
{
public:

    int task_1( const std::string & filename );
    int task_2( const std::string & filename );

private:

    std::vector< int > prepare_input( const std::string & filename );

};