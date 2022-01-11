//
// Created by alexey on 28.12.2021.
//

#ifndef ADVENTOFCODE2021_DECODER_H
#define ADVENTOFCODE2021_DECODER_H

#include <vector>
#include <string>


struct Packet
{
  Packet( int _version, int _typeId )
    : version { _version }
    , typeId { _typeId }
  {}

  Packet( int _version, int _typeId, long long val )
    : version { _version }
    , typeId { _typeId }
    , value { val }
  {}

  Packet( int _version, int _typeId, std::vector< Packet > && subPackets )
          : version { _version }
          , typeId { _typeId }
          , subPackets { std::move( subPackets ) }
  {}

  int version;
  int typeId;

  long long value { 0 };
  std::vector< Packet > subPackets;
};


class Decoder
{
public:

  static Packet decode ( const std::string & message );
  static long long calculate( const Packet & packet );
};


#endif //ADVENTOFCODE2021_DECODER_H
