//
// Created by alexey on 28.12.2021.
//

#include "Decoder.h"

#include <stdexcept>
#include <algorithm>
#include <limits>

Packet decode_a_message( const std::string & message, std::size_t & pos );


std::string convert_to_bin( const std::string & message )
{
  std::string binMessage;

  for ( const char _ch : message )
  {
    switch( _ch )
    {
      case '0': binMessage += "0000"; break;
      case '1': binMessage += "0001"; break;
      case '2': binMessage += "0010"; break;
      case '3': binMessage += "0011"; break;
      case '4': binMessage += "0100"; break;
      case '5': binMessage += "0101"; break;
      case '6': binMessage += "0110"; break;
      case '7': binMessage += "0111"; break;
      case '8': binMessage += "1000"; break;
      case '9': binMessage += "1001"; break;

      case 'A': binMessage += "1010"; break;
      case 'B': binMessage += "1011"; break;
      case 'C': binMessage += "1100"; break;
      case 'D': binMessage += "1101"; break;
      case 'E': binMessage += "1110"; break;
      case 'F': binMessage += "1111"; break;

      default: throw std::runtime_error( "Wrong input data!" );
    }
  }

  return binMessage;
}


long long convert_bin_to_dec( const std::string & binVal )
{
  long long res = 0;

  for ( const char _ch : binVal )
    res = res * 2 + ( _ch == '1' ? 1 : 0 );

  return res;
}


long long get_value( const std::string & message, std::size_t & pos )
{
  std::string strValue;

  for ( bool isLast = false; !isLast; pos += 5 )
  {
    isLast = ( message[ pos ] == '0' );
    strValue += message.substr( pos + 1, 4 );
  }

  return convert_bin_to_dec( strValue );
}


std::vector< Packet > decode_operation( const std::string & message, std::size_t & pos )
{
  std::vector< Packet > subPackets;

  // Get I
  std::string lengthTypeID = message.substr( pos, 1 );

  // Choose total length in bits / number of sub-packets immediately contained
  const bool isLengthInBits = ( lengthTypeID == "0" );

  int length = static_cast< int >( convert_bin_to_dec( message.substr( pos + 1, isLengthInBits ? 15 : 11 ) ) );

  // Move forward
  pos += 1 + ( isLengthInBits ? 15 : 11 );

  if ( isLengthInBits )
  {
    std::size_t endPos = pos + length;
    while ( pos < endPos )
      subPackets.push_back( decode_a_message( message, pos ) );
  }
  else
  {
    for ( int _packetNum = 0; _packetNum < length; ++_packetNum )
      subPackets.push_back( decode_a_message( message, pos ) );
  }

  return subPackets;
}

Packet decode_a_message( const std::string & message, std::size_t & pos )
{
  int version = static_cast< int >( convert_bin_to_dec( message.substr( pos, 3 ) ) );
  int typeID  = static_cast< int >( convert_bin_to_dec( message.substr( pos + 3, 3 ) ) );

  // Move position forward
  pos += 6;

  // Literal message
  if ( typeID == 4 )
    return {  version, typeID, get_value( message, pos ) };

  // Operator
  return { version, typeID, decode_operation( message, pos ) };
}

Packet Decoder::decode( const std::string & message )
{
  std::vector< Packet > packets;

  // Convert the message to bin representation
  std::string binMessage = convert_to_bin( message );

  // Decode message
  std::size_t pos { 0 };

  return decode_a_message( binMessage, pos );
}

/////////////////////////////////////////////////////////////////////////////////
//                     CALCULATIONS
/////////////////////////////////////////////////////////////////////////////////

long long calc_packet( const Packet & packet );

// ----------------- SUM --------------------------
long long sum( const Packet & packet )
{
  long long res { 0 };

  for ( const Packet & _subPacket : packet.subPackets )
    res += calc_packet( _subPacket );

  return res;
}

// --------------- PRODUCT --------------------------
long long product( const Packet & packet )
{
  long long res { 1 };
  for ( const Packet & _subPacket : packet.subPackets )
    res *= calc_packet( _subPacket );

  return res;

}

// --------------- MINIMUM --------------------------
long long minimum( const Packet & packet )
{
  long long minVal = std::numeric_limits< long long >::max();

  for ( const Packet & _subPacket : packet.subPackets )
    minVal = std::min( minVal, calc_packet( _subPacket ) );

  return minVal;
}

// --------------- MAXIMUM --------------------------
long long maximum( const Packet & packet )
{
  long long maxVal = std::numeric_limits< long long >::min();

  for ( const Packet & _subPacket : packet.subPackets )
    maxVal = std::max( maxVal, calc_packet( _subPacket ) );

  return maxVal;
}

// --------------- GREATER --------------------------
long long greater( const Packet & packet )
{
  if ( packet.subPackets.size() != 2 )
    throw std::runtime_error( "GREATER must be contained 2 components but now is " + std::to_string( packet.subPackets.size() ) );

  return ( calc_packet( packet.subPackets[ 0 ] ) > calc_packet( packet.subPackets[ 1 ] ) ) ? 1 : 0;
}

// ---------------- LESS --------------------------
long long less( const Packet & packet )
{
  if ( packet.subPackets.size() != 2 )
    throw std::runtime_error( "LESS must be contained 2 components but now is " + std::to_string( packet.subPackets.size() ) );

  return ( calc_packet( packet.subPackets[ 0 ] ) < calc_packet( packet.subPackets[ 1 ] ) ) ? 1 : 0;
}

// ---------------- EQUAL --------------------------
long long equal( const Packet & packet )
{
  if ( packet.subPackets.size() != 2 )
    throw std::runtime_error( "EQUAL must be contained 2 components but now is " + std::to_string( packet.subPackets.size() ) );

  return ( calc_packet( packet.subPackets[ 0 ] ) == calc_packet( packet.subPackets[ 1 ] ) ) ? 1 : 0;
}

// ----------------- SUM --------------------------

long long calc_packet( const Packet & packet )
{
  switch( packet.typeId )
  {
    case 0: return sum    ( packet );
    case 1: return product( packet );
    case 2: return minimum( packet ) ;
    case 3: return maximum( packet );
    case 4: return packet.value;
    case 5: return greater( packet );
    case 6: return less   ( packet );
    case 7: return equal  ( packet );
  }

  throw std::runtime_error( "Wrong Type ID" );
}

long long Decoder::calculate( const Packet & packet )
{
  return calc_packet( packet );
}
