//
// Created by alexey on 24.12.2021.
//

#include "ExtendedPolymerization.h"

#include <map>
#include <unordered_map>
#include <sstream>
#include <list>

#include "common/file_reader.h"
#include "common/common.h"

using t_dict = std::unordered_map< std::string, char >;
using t_chars_amount = std::vector< long long >;
using t_processing = std::map< std::string, std::vector< t_chars_amount > >;


std::tuple< t_dict, std::string > prepare_input( const std::string & filename )
{
  std::string formula;
  t_dict dict;

  // Read the file
  std::vector< std::string > sInput = FileReader::read_file( filename );

  formula = sInput[ 0 ];

  for ( std::size_t _idx = 2; _idx < sInput.size(); ++_idx )
  {
    std::vector< std::string > _rule = common::split_line( sInput[ _idx ], '-' );
    const std::string _left = common::trim( _rule[ 0 ] );
    const char        _right = _rule[ 1 ].back();

    dict.emplace( _left, _right );
  }

  return { dict, formula };
}

t_processing prepare_processing( const t_dict & rules )
{
  t_processing processing;

  for ( const auto & _rule : rules )
  {
    t_chars_amount amount ( 40, 0 );
    ++amount[ _rule.first[ 0 ]  - 'A'];
    ++amount[ _rule.first[ 1 ]  - 'A'];

    processing[ _rule.first ].emplace_back( amount );
  }

  return processing;
}

void sum_arrays( t_chars_amount & toArray, const t_chars_amount & fromArray )
{
  for ( std::size_t i = 0; i < toArray.size(); ++i )
    toArray[ i ] += fromArray[ i ];
}

t_chars_amount get_array_for_string( const std::string & str )
{
  t_chars_amount amount( 40, 0 );

  for ( const auto _ch : str )
    ++amount[ _ch - 'A' ];

  return amount;
}

void add_to_amount( t_chars_amount & amount, const char chLeft, const char chRight, const std::size_t idx, const t_processing & processing)
{
  std::string str { "xx" };

  str[ 0 ] = chLeft;
  str[ 1 ] = chRight;

  auto it = processing.find( str );
  sum_arrays( amount, ( it != processing.end() ) ? it->second[ idx ] : get_array_for_string( str ) );
}

void process_dynamic( const std::size_t currentIdx, t_processing & processing, const t_dict & rules )
{
  for ( const auto & _rule : rules )
  {
    t_chars_amount amount( 40, 0 );

    add_to_amount( amount, _rule.first[ 0 ], _rule.second    , currentIdx, processing );
    add_to_amount( amount, _rule.second    , _rule.first[ 1 ], currentIdx, processing );

    --amount[ _rule.second - 'A'];

    if ( amount[ _rule.second - 'A'] <= 0 )
      throw std::runtime_error( "Wrong amount!" );

    processing[ _rule.first ].push_back( amount );
  }
}

void print_amount( const t_chars_amount & amount )
{
  for ( std::size_t _idx = 0; _idx < amount.size(); ++_idx )
    if ( amount[ _idx ] > 0 )
      std::cout << char( 'A' + _idx ) << ": " << amount[ _idx ] << ", ";
  std::cout << "\n";
}

void print_processing( const t_processing & processing )
{
  std::cout << "Print processing:\n";
  for ( const auto & _elem : processing )
  {
    std::cout << "\t" << _elem.first << " -> ";
    print_amount( _elem.second.back() );
    std::cout << "\n";
  }
}

t_processing calc_dynamic( const std::size_t steps, const t_dict & rules )
{
  t_processing processing = prepare_processing( rules );

  for ( std::size_t _step = 0; _step < steps; ++_step )
  {
    process_dynamic( _step, processing, rules );
//    print_processing( processing );
  }

  return processing;
}

t_chars_amount get_amount_for_str( const std::string & str, const t_processing & processing )
{
  auto it = processing.find( str );

  if ( it != processing.end() )
    return it->second.back();

  return get_array_for_string( str );
}

long long calc_result( const std::string & formula, const std::size_t steps, const t_dict & rules )
{
  t_processing processing = calc_dynamic( steps, rules );

  t_chars_amount amount( 40, 0 );

  sum_arrays( amount, get_amount_for_str( formula.substr( 0, 2 ), processing ) );

  for ( std::size_t idx = 2; idx < formula.size(); ++idx )
  {
    sum_arrays( amount, get_amount_for_str( formula.substr( idx - 1, 2 ), processing ) );

    --amount[ formula[ idx - 1 ] - 'A' ];
  }

//  print_amount( amount );

  std::sort( amount.begin(), amount.end() );

  for ( std::size_t i = 0; i < amount.size(); ++i  )
    if ( amount[ i ] > 0 )
      return amount.back() - amount[ i ];

  throw std::runtime_error( "Min val is not found!" );
}


long long ExtendedPolymerization::task_1( const std::string & filename )
{
  auto [ rules, formula ] = prepare_input( filename );

  return calc_result( formula, 10, rules );
}

long long ExtendedPolymerization::task_2( const std::string & filename )
{
  auto [ rules, formula ] = prepare_input( filename );

  return calc_result( formula, 40, rules );
}
