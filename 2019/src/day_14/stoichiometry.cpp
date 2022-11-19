
#include "stoichiometry.h"

#include "common/file_reader.h"

#include <sstream>
#include <set>
#include <map>


long long Stoichiometry::run_part_1( const std::string & fileName )
{
  reactions = prepare_input_( fileName );

  Producer prod( "ORE" );
  prod.produce( "FUEL", 1, reactions );

  return prod.get_raw_materials();
}

long long Stoichiometry::run_part_2( const std::string & fileName )
{
  reactions = prepare_input_( fileName );

  Producer prod( "ORE" );
  prod.produce( "FUEL", 1, reactions );

  long long rawMaterials = prod.get_raw_materials();
  long long minFuels = 1000000000000ll / rawMaterials;
  long long offset = 10000;

  while ( rawMaterials <= 1000000000000ll || offset != 1 )
  {
    if ( rawMaterials > 1000000000000ll )
      offset = offset > 10 ? offset / 10 : 1;

    Producer prod( "ORE" );
    prod.produce( "FUEL", minFuels + offset, reactions );

    rawMaterials = prod.get_raw_materials();

    if ( rawMaterials <= 1000000000000ll )
      minFuels += offset;
  }

  return minFuels;
}


Stoichiometry::t_reaction Stoichiometry::prepare_input_( const std::string & fileName )
{
  t_reaction res;

  // Read the file
  std::vector< std::string > sInputs = FileReader::read_file( fileName );

  for ( const auto & _line : sInputs )
  {
    // formula
    std::string sFormula = _line.substr( 0,  _line.find( "=>" ) );

    // reaction result
    std::string sReactionResult = _line.substr( _line.find( "=>" ) + 2 );

    std::string _tmpLine;

    // Get formula
    t_formula formula;
    std::istringstream iss( sFormula );
    while ( std::getline( iss, _tmpLine, ',' ) )
      formula.push_back( read_element( _tmpLine ) );

    // Get result
    t_element reactionResult = read_element( sReactionResult );

    res.emplace( reactionResult.name, std::make_pair( reactionResult, formula ) );
  }

  return res;
}

Stoichiometry::t_element Stoichiometry::read_element( std::string & line )
{
  std::istringstream iss( line );

  long long val;
  std::string name;

  iss >> val >> name;

  return{ name, val };
}


void Stoichiometry::Producer::produce( const std::string & elementName, long long quantity, t_reaction & reactions )
{
  // Stop recursion (raw materials is not produced)
  if ( elementName == m_rawMaterialName )
  {
    m_usedRawMaterials += quantity;
    return;
  }

  // Get already produced elements
  long long existProducts = how_many_product( elementName );

  // Is elements enought
  if ( existProducts >= quantity )
  {
    remove_product( elementName, quantity );
    return;
  }

  // Quantity elements need to produce
  long long needToProduce = quantity - existProducts;

  // Produce element by the formula
  std::pair< t_element, t_formula > & formula = reactions[ elementName ];

  // Calculate formula multiplier
  long long formulaMultiplier = needToProduce / formula.first.val + ( needToProduce % formula.first.val != 0 ? 1 : 0 );

  for ( const auto & _element : formula.second )
    produce( _element.name, formulaMultiplier * _element.val, reactions );

  // Produced elements can be more than needed
  long long totalQuantity = formulaMultiplier * formula.first.val + existProducts;

  // Update storage
  set_product( elementName, totalQuantity - quantity );
}

void Stoichiometry::Producer::add_product( const std::string & name, long long quantity )
{
  auto it = m_products.find( name );

  if ( it == m_products.end() )
    m_products[ name ] = quantity;
  else
    ( *it ).second += quantity;
}

long long Stoichiometry::Producer::how_many_product( const std::string & name )
{
  auto it = m_products.find( name );

  if ( it == m_products.end() )
    return 0;
  
  return ( *it ).second;
}

void Stoichiometry::Producer::remove_product( const std::string & name, long long quantity )
{
  m_products[ name ] -= quantity;
}

void Stoichiometry::Producer::set_product( const std::string & name, long long quantity )
{
  m_products[ name ] = quantity;
}
