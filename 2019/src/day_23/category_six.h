#pragma once

#include <memory>
#include <vector>
#include <queue>
#include <optional>
#include <list>
#include <mutex>

#include "day_2/computer.h"

// -----------------------------------  Communicator  -----------------------------------------
class Communicator
{
public:

    Communicator();

    long long get( long long computerNum );

    void set( long long computerNum, long long val_1, long long val_2 );

    bool empty();

    void idle();

private:

    std::array< std::queue< long long >, 50 > computers;

    std::pair< long, long > output;
    std::pair< long long, int > idleY { 0, 0 };
    std::mutex mutex;
};


// -----------------------------------  CategorySix  -----------------------------------------
class CategorySix : public Computer
{

public:

    CategorySix( int initComputerNum, const std::shared_ptr< Communicator > & initCommunicator )
        : Computer( /* initDay23 */ true )
        , m_computerNum{ initComputerNum }
        , m_communicator{ initCommunicator }
    {}

protected:

    virtual long long input()                 override;

    virtual void      output( long long val ) override;

private:

    const int m_computerNum;

    std::vector< long long > m_output;

    std::shared_ptr< Communicator > m_communicator;

};

