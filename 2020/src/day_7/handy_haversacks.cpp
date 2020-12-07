
#include "handy_haversacks.h"

#include <map>
#include <set>
#include <vector>
#include <string>
#include <regex>
#include <iostream>

#include "common/file_reader.h"


using t_bag_collection = std::map< std::string, std::vector< std::pair< std::string, int > > >;


t_bag_collection prepare_input( const std::string & filename )
{
  // Read the file
  std::vector< std::string > sInputs = FileReader::read_file( filename );

  t_bag_collection bagCollection;

  for ( auto & _line : sInputs )
  {
    // light red bags contain 1 bright white bag, 2 muted yellow bags.
    std::regex wordRegexBagContainer(R"((\w+ \w+) bags contain)");
    std::regex wordRegexContainedBags(R"((\d+) (\w+ \w+) bag)");
    std::smatch searchResult;

    std::regex_search(_line, searchResult, wordRegexBagContainer);
    if (searchResult.size() != 2)
      throw std::invalid_argument("Must be 2 arguments");

    std::string bagContainer = searchResult[1];

    _line = searchResult.suffix().str();

    std::vector< std::pair< std::string, int > > _bags;
    while( std::regex_search(_line, searchResult, wordRegexContainedBags) )
    {
      _bags.emplace_back( searchResult[2], std::stoi( searchResult[1] ) );
      _line = searchResult.suffix().str();
    }

//    std::cout << "Bag: " << bagContainer << " contains :\n";
//    for ( const auto & _bag : _bags )
//      std::cout << "\t- " << _bag.first << " * " << _bag.second << "\n";

    bagCollection[ bagContainer ] = _bags;
  }

  return bagCollection;
}


int HandyHaversacks::task_1(const std::string &filename)
{
  t_bag_collection bags = prepare_input( filename );

  std::set< std::string > containsTheBag { "shiny gold" };

  for ( int idx = 0; idx < bags.size() - 1; ++idx )
  {
    std::size_t containsTheBagSize = containsTheBag.size();

    for (const auto &_bagContainer : bags)
    {
      for ( const auto & _bag : _bagContainer.second )
      {
        if ( containsTheBag.count( _bag.first ) )
          containsTheBag.insert( _bagContainer.first );
      }
    }

    if ( containsTheBagSize == containsTheBag.size() )
      break;
  }

  return containsTheBag.size() - 1;
}


int get_number_nested_bags( t_bag_collection & bagCollection, const std::string & bagName )
{
  int res { 1 };

  for ( const auto & _bag : bagCollection[ bagName ] )
    res += get_number_nested_bags( bagCollection, _bag.first ) * _bag.second;

  return res;
}


int HandyHaversacks::task_2(const std::string &filename)
{
  t_bag_collection bags = prepare_input( filename );
  return get_number_nested_bags( bags, "shiny gold") - 1;
}