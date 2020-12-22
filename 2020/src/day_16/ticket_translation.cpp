//
// Created by alexey on 21.12.2020.
//

#include "ticket_translation.h"

#include <vector>
#include <stdexcept>
#include <regex>
#include <algorithm>
#include <numeric>

#include "common/file_reader.h"


using t_ticket = std::vector< int >;

struct Rule
{
  std::string name;
  std::vector< std::pair< int, int > > allowed;
};

enum class CurrentAction
{
    READ_RULES
  , READ_YOUR_TICKET
  , READ_NEARBY_TICKETS
};

Rule get_rule( const std::string & rule )
{
  Rule res;

  std::regex getRule( R"(([\S ]+): (\d+)-(\d+) or (\d+)-(\d+))" );
  std::smatch match;

  std::regex_match( rule, match, getRule );

  res.name = match[ 1 ];
  res.allowed.emplace_back( std::stoi( match[ 2 ] ), std::stoi( match[ 3 ] ) );
  res.allowed.emplace_back( std::stoi( match[ 4 ] ), std::stoi( match[ 5 ] ) );

  return res;
}

t_ticket get_ticket( std::string line )
{
 t_ticket res;

 std::regex getVal("(\\d+)" );
 std::smatch match;

 while( std::regex_search( line, match, getVal ) )
 {
   res.push_back( std::stoi( match[ 1 ] ) );
   line = match.suffix();
 }

 return res;
}

std::vector< t_ticket > prepare_input( const std::string & filename, std::vector< Rule > & rules, t_ticket & yourTicket )
{
  std::vector< std::string > sInput = FileReader::read_file( filename );
  std::vector< t_ticket > tickets;

  CurrentAction action { CurrentAction::READ_RULES };

  for ( const auto & _line : sInput )
  {
    if( _line.empty() )
      continue;

    if ( _line == "your ticket:" )
    {
      action = CurrentAction::READ_YOUR_TICKET;
      continue;
    }

    if ( _line == "nearby tickets:" )
    {
      action = CurrentAction::READ_NEARBY_TICKETS;
      continue;
    }

    switch( action )
    {
      case CurrentAction::READ_RULES:
        rules.push_back( get_rule( _line ) );
        break;

      case CurrentAction::READ_YOUR_TICKET:
        yourTicket = get_ticket( _line );
        continue;

      case CurrentAction::READ_NEARBY_TICKETS:
        tickets.emplace_back( get_ticket( _line ) );
        break;
    }
  }

  return tickets;
}

bool is_fit( const Rule & rule, int val )
{
  return std::any_of( rule.allowed.begin(), rule.allowed.end(),
                      [ val ]( const std::pair< int, int > & _allowPart ){ return ( val >= _allowPart.first && val <= _allowPart.second ); } );
}

bool is_fit( const std::vector< Rule > & rules, int val )
{
  return std::any_of( rules.begin(), rules.end(), [ val ]( const Rule & _rule ){ return is_fit( _rule, val ); } );
}


bool is_good_ticket( const t_ticket & ticket, std::vector< Rule > rules )
{
  return std::all_of( ticket.begin(), ticket.end(), [ &rules ]( int _val ) { return is_fit( rules, _val ); } );
}


int TicketTranslation::task_1( const std::string & filename )
{
  std::vector< Rule > rules;
  t_ticket yourTicket;
  std::vector< t_ticket > tickets = prepare_input( filename, rules, yourTicket );

  int res { 0 };

  for ( const auto & _ticket : tickets )
  {
    for( auto _val : _ticket )
    {
      if ( !is_fit( rules, _val ) )
        res += _val;
    }
  }

  return res;
}

std::size_t get_field_num( const Rule & rule, const std::vector< t_ticket > & tickets, bool & onlyOneRuleFit, const std::vector< std::size_t > & usedFields )
{
  std::vector< std::size_t > fittedFields;

  for( std::size_t fieldIdx = 0; fieldIdx < tickets[ 0 ].size(); ++fieldIdx )
  {
    if ( std::find( usedFields.begin(), usedFields.end(), fieldIdx ) != usedFields.end() )
      continue;

    if ( std::all_of( tickets.begin(), tickets.end(), [ fieldIdx, &rule ]( const t_ticket & _ticket ){ return is_fit( rule, _ticket[ fieldIdx ] ); } ) )
      fittedFields.push_back( fieldIdx );
  }

  onlyOneRuleFit = fittedFields.size() == 1;

  return fittedFields[ 0 ];
}

long long TicketTranslation::task_2( const std::string &filename )
{
  std::vector< Rule > rules;
  t_ticket yourTicket;
  std::vector< t_ticket > tickets = prepare_input( filename, rules, yourTicket );
  tickets.push_back( yourTicket );

  // Exclude wrong tickets
  std::vector< t_ticket > goodTickets;
  auto itEnd = std::remove_if( tickets.begin(), tickets.end(), [ &rules ]( const t_ticket & ticket ){ return !is_good_ticket( ticket, rules); } );
  tickets.erase( itEnd, tickets.end() );

  std::vector< std::pair< std::string, std::size_t > > fields;
  std::vector< std::size_t > usedFields;

  while( !rules.empty() )
  {
    bool isUniqueRules = false;
    for ( std::size_t idx = 0; idx < rules.size(); ++idx )
    {
      std::size_t fieldNum = get_field_num( rules[ idx ], tickets, isUniqueRules, usedFields );
      if ( isUniqueRules )
      {
        usedFields.push_back( fieldNum );
        fields.emplace_back( rules[ idx ].name, fieldNum );
        rules.erase( rules.begin() + idx );
        break;
      }
    }
    if ( !isUniqueRules )
      throw std::invalid_argument( "Govnokidishe" );
  }

  // Calculate result
  long long res { 1 };
  for ( const auto & _field : fields )
    if ( _field.first.find( "departure" ) != std::string::npos )
      res *= yourTicket[ _field.second ];

  return res;
}
