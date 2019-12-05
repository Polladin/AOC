#include "total_fuel.h"

#include "common/file_reader.h"

#include <iostream>


void TotalFuel::run_part_1( const std::string & inputFile )
{
  // Read input values
  std::vector< int > inputs = prepare_input( inputFile );

  // Calculate result
  int result = calculate_result_fuel_mass_part_1( inputs );
  
  // Print results
  std::cout << "Result: " << result << std::endl;
}


void TotalFuel::run_part_2( const std::string & inputFile )
{
  // Read input values
  std::vector< int > inputs = prepare_input( inputFile );

  // Calculate fuel
  int result = calculate_result_fuel_mass_part_2( inputs );

  // Print results
  std::cout << "Result: " << result << std::endl;
}


std::vector<int> TotalFuel::prepare_input( const std::string & inputFile )
{
  // Read the file
  std::vector< std::string > sInputs = FileReader::read_file( inputFile );

  // Convert input data from string to int
  std::vector< int > inputs;
  inputs.reserve( sInputs.size() );

  for ( const auto & _line : sInputs )
    inputs.push_back( std::stoi( _line ) );

  return inputs;
}


int TotalFuel::calculate_result_fuel_mass_part_1( const std::vector< int >& input )
{
  int result = 0;

  for ( auto mass : input )
  {
    int fuel = static_cast< int >( mass / 3.0 ) - 2;
    result += fuel;
  }

  return result;
}


int TotalFuel::calculate_result_fuel_mass_part_2( const std::vector< int >& input )
{
  int result = 0;

  for ( auto mass : input )
  {
    int fuel = static_cast< int >( mass / 3.0 ) - 2;
    fuel += calculate_tatal_mass( fuel );

    result += fuel;
  }

  return result;
}


int TotalFuel::calculate_tatal_mass( int fuelMass )
{
  int additionalFuels = 0;

  while ( fuelMass > 0 )
  {
    fuelMass = static_cast< int >( fuelMass / 3.0 ) - 2;
    additionalFuels += fuelMass > 0 ? fuelMass : 0;

    std::cout << "fuelMass: " << fuelMass << "   additionalFuels: " << additionalFuels << "\n";
  }

  return additionalFuels;
}

