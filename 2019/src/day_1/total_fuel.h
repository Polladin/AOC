#pragma once


#include <string>
#include <vector>


/**************************************************
*                  Total Fuel
***************************************************/
class TotalFuel
{

public:

  void run_part_1( const std::string & inputFile );
  void run_part_2( const std::string & inputFile );

private:

  std::vector< int > prepare_input( const std::string & inputFile );

  int calculate_result_fuel_mass_part_1( const std::vector< int > & input );
  int calculate_result_fuel_mass_part_2( const std::vector< int > & input );

  int calculate_tatal_mass( int fuelMass );
};