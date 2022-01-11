//
// Created by alexey on 28.12.2021.
//

#ifndef ADVENTOFCODE2021_PACKETDECODER_H
#define ADVENTOFCODE2021_PACKETDECODER_H

#include <string>

class PacketDecoder
{
public:

  int task_1( const std::string & filename );
  long long task_2( const std::string & filename );
  long long test_task_2( const std::string & inputMessage );

};


#endif //ADVENTOFCODE2021_PACKETDECODER_H
