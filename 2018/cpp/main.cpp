
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "task_22.h"
#include "task_24.h"


void task_22()
{
    std::vector<std::string> TEST_1
    { "0001222100"
        , "1101010101"
        , "1101010101"
        , "1100010001"
    };

    //std::cout << "Res 10x10 : " <<  Task22( 510, { 10, 10 }, 11, 11).get_score( 10, 10 ) << std::endl;
    std::cout << "Res 10x725 : " << Task22( 8787, { 10, 725 }, 11, 726 ).get_score( 10, 725 ) << std::endl;

    std::cout << "Min path 15x15 target(10, 10) : " << Task22( 510, { 10, 10 }, 15, 15 ).get_min_path() << std::endl;

    std::cout << "Min path 20x750 target(10, 725) : " << Task22( 8787, { 10, 725 }, 50, 750 ).get_min_path() << std::endl;

    //auto obj = Task22( 510, { 9, 0 }, 10, 4 );
    //obj.set_score( TEST_1 );
    //std::cout << obj.get_min_path() << std::endl;
}


void task_24()
{
    try{
        auto obj = Task24();
        obj.run( 82 );

        //int leftBoost = 0;
        //int rightBoost = 1050;

        //while ( leftBoost != rightBoost )
        //{
        //    std::cout << "Run with boost : " << ( rightBoost - leftBoost ) / 2 << std::endl;
        //    if ( ! Task24().run( ( rightBoost - leftBoost ) / 2) )
        //        leftBoost = ( rightBoost - leftBoost ) / 2;
        //    else
        //        rightBoost = ( rightBoost - leftBoost ) / 2;
        //}
        //std::cout << "Boost = " << rightBoost << std::endl;
    }
    catch ( const std::string & str )
    {
        std::cout << "ERROR : " << str << std::endl;
    }
}





int main()
{
    //task_22();

    task_24();

    std::cin.get();
}
