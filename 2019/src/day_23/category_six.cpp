#include "category_six.h"

#include <iostream>


// -----------------------------------  Communicator  -----------------------------------------

Communicator::Communicator()
{
    for ( int compNum = 0; compNum < 50; ++compNum )
        computers[ compNum ].push( compNum );
}

long long Communicator::get( long long computerNum )
{
    std::lock_guard lock( mutex );

//    std::cout << "Try get to computer : " << computerNum << std::endl;

    if ( computerNum < 0 || computerNum >= 50 )
        return -1;

    auto & computerQueue = computers[ computerNum ];

    if ( computerQueue.empty() )
        return -1;

    long long res = computerQueue.front();
    computerQueue.pop();

    return res;
}

void Communicator::set( long long computerNum, long long val_1, long long val_2 )
{
    std::lock_guard lock( mutex );

//    std::cout << "Try set for computer : " << computerNum << " vals: " << val_1 << ", " << val_2 << std::endl;

    if ( computerNum == 255 )
    {
        output = std::make_pair( val_1, val_2 );
        return;
    }

    if ( computerNum < 0 || computerNum >= 50 )
        return;

    auto & computerQueue = computers[ computerNum ];

    computerQueue.push( val_1 );
    computerQueue.push( val_2 );
}

bool Communicator::empty()
{
    std::lock_guard lock( mutex );

    for ( std::size_t compNum = 0; compNum < 50; ++compNum )
        if ( !computers[ compNum ].empty() )
            return false;

    return true;
}

void Communicator::idle()
{
    std::lock_guard lock( mutex );

    computers[ 0 ].push( output.first );
    computers[ 0 ].push( output.second );

    std::cout << "Idle push: " << output.first << " " << output.second << std::endl;

    if ( idleY.first == output.second )
        ++idleY.second;
    else
        idleY = std::make_pair( output.second, 1ll );

    if ( idleY.second == 2 )
        std::cout << "Result : " << idleY.first << std::endl;
}


// -----------------------------------  CategorySix  -----------------------------------------

long long CategorySix::input()
{
    return m_communicator->get( m_computerNum );
}

void CategorySix::output( long long val )
{
    m_output.push_back( val );

    if ( m_output.size() != 3 )
        return;

    m_communicator->set( m_output[ 0 ], m_output[ 1 ], m_output[ 2 ] );

    m_output.clear();
}
