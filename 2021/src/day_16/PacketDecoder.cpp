//
// Created by alexey on 28.12.2021.
//

#include "PacketDecoder.h"

#include <iostream>

#include "common/file_reader.h"
#include "Decoder.h"




int sum_versions( const Packet & packet )
{
  int res { packet.version };

  for ( const auto & _packet : packet.subPackets )
    res += sum_versions( _packet );

  return res;
}

int PacketDecoder::task_1( const std::string & filename )
{
  // Read the file
  std::vector< std::string > sInput = FileReader::read_file( filename );

  Packet packet = Decoder::decode( sInput[ 0 ] );

  return sum_versions( packet );
}

long long PacketDecoder::task_2( const std::string & filename )
{
  // Read the file
  std::vector< std::string > sInput = FileReader::read_file( filename );

  Packet packet = Decoder::decode( sInput[ 0 ] );

  return Decoder::calculate( packet );
}

long long PacketDecoder::test_task_2( const std::string & inputMessage )
{
  Packet packet = Decoder::decode( inputMessage );

  return Decoder::calculate( packet );
}
