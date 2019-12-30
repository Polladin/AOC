#include "springdroid.h"

#include <iostream>

#include "day_2/computer.h"


int Springdroid::run_part_1( const std::string & fileName )
{
  Computer comp;

  comp.prepare_day_7_part_1( fileName );

  std::queue< long long > input;
  std::vector< long long >  output;

  comp.run_day_7_part_1( input, output );

  for ( auto _el : output )
    std::cout << char( _el );
  std::cout << "\n";

  push_to_input( "OR D J", input );

  push_to_input( "OR A T", input );
  push_to_input( "AND B T", input );
  push_to_input( "AND C T", input );

  push_to_input( "NOT T T", input );
  push_to_input( "AND T J", input );

  push_to_input( "WALK", input );

  comp.run_day_7_part_1( input, output );

  for ( auto _el : output )
    std::cout << char(_el);
  std::cout << "\n";

  for ( auto _el : output )
    std::cout <<  _el;
  std::cout << "\n";

  return 0;
}


int Springdroid::run_part_2( const std::string & fileName )
{
  Computer comp;

  comp.prepare_day_7_part_1( fileName );

  std::queue< long long > input;
  std::vector< long long >  output;

  comp.run_day_7_part_1( input, output );

  for ( auto _el : output )
    std::cout << char( _el );
  std::cout << "\n";

  push_to_input( "OR D J", input );
  push_to_input( "AND H J", input );
  
  push_to_input( "OR A T", input );
  push_to_input( "AND B T", input );
  push_to_input( "AND C T", input );

  push_to_input( "NOT T T", input );
  push_to_input( "AND T J", input );

  push_to_input( "AND D T", input );
  push_to_input( "AND E T", input );

  push_to_input( "OR T J", input );


  push_to_input( "RUN", input );

  comp.run_day_7_part_1( input, output );

  for ( auto _el : output )
    std::cout << char( _el );
  std::cout << "\n";

  for ( auto _el : output )
    std::cout << _el;
  std::cout << "\n";

  return 0;
}


void Springdroid::push_to_input( const std::string & str, std::queue< long long > & input )
{
  for ( auto _el : str )
    input.push( _el );

  input.push( 10 );
}
