#pragma once

#include <string>
#include <vector>


class PasswordPhilosophy
{
private:

    struct Record
    {
        int low;
        int high;
        char symbol;
        std::string password;
    };

public:

    int task_1( const std::string & filename );
    int task_2( const std::string & filename );

private:

    std::vector< Record > prepare_input( const std::string & filename );

};


