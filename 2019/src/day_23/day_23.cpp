
#include <iostream>
#include <thread>
#include <chrono>


#include "category_six.h"


void observer_func( std::shared_ptr< Communicator > & communicator )
{
    using namespace std::chrono_literals;

    while( 1 )
    {
        std::this_thread::sleep_for( 100ms );

        bool isQueEmpty = communicator->empty();

        std::this_thread::sleep_for( 1s );

        isQueEmpty = isQueEmpty && communicator->empty();

        if ( !isQueEmpty )
            continue;

        communicator->idle();
    }
}


int main()
{
    std::vector< std::thread > threads;

    std::cout << "Day 21: Springdroid Adventure\n\n";

    auto communicator = std::make_shared< Communicator >();

    for ( int compNum = 0; compNum < 50; ++compNum )
    {
        std::cout << "Boot computer : " << compNum << std::endl;
        threads.emplace_back( [ compNum, & communicator ](){ CategorySix( compNum, communicator ).run_part_1( INPUT_FILES "/day_23/task_1.txt" ); } );
    }

    std::thread observer( observer_func, std::ref( communicator ) );

    for ( auto & _thread : threads )
        _thread.join();



    return 0;
}
