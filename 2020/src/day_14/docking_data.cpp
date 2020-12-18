//
// Created by alexey on 18.12.2020.
//

#include "docking_data.h"

#include <vector>
#include <map>
#include <regex>
#include <iostream>
#include <bitset>

#include "common/file_reader.h"


struct t_load_to_mem
{
  std::string mask;
  std::string value;
};

using t_memory = std::map< uint64_t, t_load_to_mem >;


std::string int_to_str( const std::string & intVal )
{
  return std::bitset< 64 >( std::stoull( intVal ) ).to_string();
}


t_memory prepare_input( const std::string & filename )
{
  t_memory output;

  // Read the file
  std::vector< std::string > sInput = FileReader::read_file( filename );

  const std::regex regexpMask(R"(mask = (\S+))");
  const std::regex regexpMem(R"(mem\[(\d+)\] = (\d+))" );
  std::smatch regexMatch;
  std::string mask;

  for ( const auto & _line : sInput )
  {
    // Read mask
    if( std::regex_match( _line, regexMatch, regexpMask ) )
    {
      mask = regexMatch[ 1 ];
      continue;
    }

    // Read memory
    if ( !std::regex_match( _line, regexMatch, regexpMem ) )
      throw std::invalid_argument( "Invalid input data" );

    output[ std::stoull( regexMatch[ 1 ] ) ] = t_load_to_mem{ mask, int_to_str( regexMatch[ 2 ] ) };
  }

  return output;
}


std::vector< std::pair< std::string, t_load_to_mem > > prepare_input_2( const std::string & filename )
{
  std::vector< std::pair< std::string, t_load_to_mem > > output;

  // Read the file
  std::vector< std::string > sInput = FileReader::read_file( filename );

  const std::regex regexpMask(R"(mask = (\S+))");
  const std::regex regexpMem(R"(mem\[(\d+)\] = (\d+))" );
  std::smatch regexMatch;
  std::string mask;

  for ( const auto & _line : sInput )
  {
    // Read mask
    if( std::regex_match( _line, regexMatch, regexpMask ) )
    {
      mask = regexMatch[ 1 ];
      continue;
    }

    // Read memory
    if ( !std::regex_match( _line, regexMatch, regexpMem ) )
      throw std::invalid_argument( "Invalid input data" );

    output.emplace_back( int_to_str ( regexMatch[ 1 ] ), t_load_to_mem{ mask, int_to_str( regexMatch[ 2 ] ) } );
  }

  return output;
}


uint64_t str_to_int( const std::string & strValue )
{
  uint64_t resInt { 0 };

  for ( std::size_t idx = 0; idx < strValue.size(); ++idx )
    resInt += ( ( uint64_t) ( strValue[ idx ] - '0' ) ) << ( strValue.size() - idx - 1 );

  return resInt;
}

uint64_t apply_mask( const std::string & val, const std::string & mask )
{
  std::string result ( std::min( val.size(), mask.size() ), '0' );

  auto [ itVal, itMask, itResult ] = std::tuple{ val.rbegin(), mask.rbegin(), result.rbegin() };
  for ( ;   ( itVal    != val.rend()    )
         && ( itMask   != mask.rend()   )
         && ( itResult != result.rend() );
        ++itVal, ++itMask, ++itResult       )
  {
    *itResult = ( *itMask == 'X' ) ? *itVal : *itMask;
  }

  return str_to_int( result );
}


uint64_t DockingData::task_1( const std::string &filename )
{
  t_memory commands = prepare_input( filename );
  std::map< uint64_t, uint64_t > mem;

  uint64_t res { 0 };

  for ( const auto & _memSlot : commands )
  {
    mem[ _memSlot.first ] = apply_mask( _memSlot.second.value, _memSlot.second.mask );
    res += mem[ _memSlot.first ];
  }

  return res;
}

void write_to_mem( std::string address, std::map< uint64_t, uint64_t > & mem, uint64_t value )
{
  for ( std::size_t idx = 0; idx < address.size(); ++idx )
  {
    if ( address[ idx ] != 'X' )
      continue;

    address[ idx ] = '0';
    write_to_mem( address, mem, value );

    address[ idx ] = '1';
    write_to_mem( address, mem, value );

    return;
  }

  mem[ str_to_int( address ) ] =  value;
}

std::string apply_mask_2( const std::string & val, const std::string & mask )
{
  std::string result ( std::min( val.size(), mask.size() ), '0' );

  auto [ itVal, itMask, itResult ] = std::tuple{ val.rbegin(), mask.rbegin(), result.rbegin() };
  for ( ;   ( itVal    != val.rend()    )
            && ( itMask   != mask.rend()   )
            && ( itResult != result.rend() );
            ++itVal, ++itMask, ++itResult       )
  {
    *itResult = ( *itMask == '0' ) ? *itVal : *itMask;
  }

  return result;
}

uint64_t DockingData::task_2( const std::string &filename )
{
  std::vector< std::pair< std::string, t_load_to_mem > > commands = prepare_input_2( filename );
  std::map< uint64_t, uint64_t > mem;

  for ( const auto & _memSlot : commands )
  {
    // apply mask
    std::string address = apply_mask_2( _memSlot.first, _memSlot.second.mask );

    // write to mem
    write_to_mem( address, mem, str_to_int( _memSlot.second.value ) );
  }

  uint64_t res { 0 };
  for ( const auto & _slot : mem )
  {
    res += _slot.second;
  }

  return res;
}
