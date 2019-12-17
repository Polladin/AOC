#pragma once

#include <string>
#include <vector>
#include <map>


class Stoichiometry
{
private:

  struct t_element
  {
    t_element(){}
    t_element( const std::string & _name, long long _val)
      : name{ _name }, val( _val )
    {}

    std::string name{""};
    long long val{0};
  };

  using t_formula = std::vector< t_element >;
  using t_reaction = std::map< std::string, std::pair< t_element, t_formula > >;
  using t_cost_element = std::pair< t_element, long long >;
  using t_element_cost = std::map< std::string, t_cost_element >;
  using t_products = std::map< std::string, long long >;

  class Producer
  {
  public:

    Producer( const std::string & rawMaterialName )
      : m_rawMaterialName{ rawMaterialName }
    {}

    void produce( const std::string & elementName, long long quantity, t_reaction & reactions );
    
    long long get_raw_materials() { return m_usedRawMaterials; }

  private:

    void add_product( const std::string & name, long long quantity );
    long long  how_many_product( const std::string & name );
    void remove_product( const std::string & name, long long quantity );
    void set_product( const std::string & name, long long quantity );

  private:

    long long m_usedRawMaterials{ 0 };
    std::string m_rawMaterialName;

    t_products m_products;
  };


public:
  
  long long run_part_1( const std::string & fileName );
  long long run_part_2( const std::string & fileName );

private:

  t_reaction prepare_input_( const std::string & fileName );
  t_element read_element( std::string & line );

private:

  t_element_cost costs;
  t_reaction reactions;

};