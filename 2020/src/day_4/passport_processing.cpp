
#include "passport_processing.h"

#include <regex>
#include <iostream>
#include <map>
#include <functional>
#include <set>

#include "common/file_reader.h"


//  byr (Birth Year) - four digits; at least 1920 and at most 2002.
static bool compare_byr( const std::string & str)
{
  int val = std::stoi(str);
  return (val >= 1920 && val <= 2002);
}

//  iyr (Issue Year) - four digits; at least 2010 and at most 2020.
static bool compare_iyr( const std::string & str )
{
  int val = std::stoi(str);
  return (val >= 2010 && val <= 2020);
}

//  eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
static bool compare_eyr( const std::string & str )
{
  int val = std::stoi( str );
  return ( val >= 2020 && val <= 2030 );
}

//  hgt (Height) - a number followed by either cm or in:
//    If cm, the number must be at least 150 and at most 193.
//    If in, the number must be at least 59 and at most 76.
static bool compare_hgt( const std::string & str )
{
  int height = std::stoi( str.substr( 0,str.size() - 2 ) );
  std::string type = str.substr( str.size() - 2 );

  if ( type == "cm" )
  {
    return ( height >= 150 && height <= 193 );
  }
  else if ( type == "in" )
  {
    return ( height >= 59 && height <= 76 );
  }

  return false;
}

//  hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
static bool compare_hcl( const std::string & str )
{
  if ( str.size() != 7 || str[0] != '#' )
    return false;

  for ( std::size_t idx = 1; idx < str.size(); ++idx )
    if (   ( str[ idx ] < '0' || str[ idx ] > '9' )
        && ( str[ idx ] < 'a' || str[ idx ] > 'f' ) )
      return false;

  return true;
}

//  ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
static bool compare_ecl( const std::string & str )
{
  static std::set< std::string > allowedEcl { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };

  return ( allowedEcl.find( str ) != allowedEcl.end() );
}

//  pid (Passport ID) - a nine-digit number, including leading zeroes.
static bool compare_pid( const std::string & str )
{
  if ( str.size() != 9 )
    return false;

  return std::all_of( str.begin(), str.end(), isdigit );
}

//  cid (Country ID) - ignored, missing or not.
static bool compare_cid( const std::string & )
{
  return true;
}


bool PassportProcessing::is_valid( const t_record & record )
{
  //"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"
  static std::map< std::string, std::function< bool ( const std::string & ) > > validator
          { { "byr", compare_byr }
          , { "iyr", compare_iyr }
          , { "eyr", compare_eyr }
          , { "hgt", compare_hgt }
          , { "hcl", compare_hcl }
          , { "ecl", compare_ecl }
          , { "pid", compare_pid }
          , { "cid", compare_cid }
          };

  try {
    return validator[record.first](record.second);
  } catch( ... )
  {
    return false;
  }
}


bool PassportProcessing::is_all_mandatory_fields_presented( const t_records & records )
{
  static std::vector< std::string > mandatoryFields = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };

  for ( const auto &_mandatory_field : mandatoryFields )
  {
    if( !std::any_of( records.begin(), records.end(), [ &_mandatory_field ]( const t_record & _rec ){ return _rec.first == _mandatory_field; }) )
      return false;
  }

  return true;
}


int PassportProcessing::task_1(const std::string &filename)
{
  t_passport passports = prepare_input( filename );

  std::vector< std::string > mandatoryFields = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };

  int validatedPassports { 0 };

  for ( const auto & _passport : passports )
  {
    if ( is_all_mandatory_fields_presented( _passport ) )
      ++validatedPassports;
  }

  return validatedPassports;
}


int PassportProcessing::task_2(const std::string &filename)
{
  t_passport passports = prepare_input(filename);

  int validatedPassports { 0 };

  for ( const auto & _passport : passports )
  {
    if (   is_all_mandatory_fields_presented( _passport )
        && std::all_of( _passport.begin(), _passport.end(), is_valid ) )
      ++validatedPassports;
  }

  return validatedPassports;
}


PassportProcessing::t_passport PassportProcessing::prepare_input(const std::string &filename)
{
  t_passport passports;

  // Read the file
  std::vector< std::string > sInputs = FileReader::read_file( filename );

  t_records records;
  for ( auto _line : sInputs )
  {
    if ( _line.find( ':' ) == std::string::npos )
    {
      passports.push_back( records );
      records.clear();
      continue;
    }

    std::regex wordRegex(R"(([^\s]+):([^\s]+))");
    std::smatch searchResult;

    while( std::regex_search(_line, searchResult, wordRegex) )
    {
      if (searchResult.size() != 3)
        throw std::invalid_argument("Must be 3 arguments");

      records.emplace_back(searchResult[1], searchResult[2]);

      _line = searchResult.suffix().str();
    }
  }

  return passports;
}
