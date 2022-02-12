//
// Created by alexey on 25.01.2022.
//

#include "ReactorReboot.h"

#include <vector>
#include <regex>
#include <set>
#include <optional>
#include <iostream>
#include <list>
#include <iostream>

#include "common/file_reader.h"

struct Block
{
  Block() = default;

  Block( std::pair< int, int > && i_x, std::pair< int, int > && i_y, std::pair< int, int > && i_z )
    : x { std::move( i_x ) }, y { std::move( i_y ) }, z { std::move( i_z ) }
  {}

  Block( std::pair< int, int > i_x, std::pair< int, int > i_y, std::pair< int, int > i_z )
          : x { std::move( i_x ) }, y { std::move( i_y ) }, z { std::move( i_z ) }
  {}

  bool isOn { true };

  std::pair< int, int > x;
  std::pair< int, int > y;
  std::pair< int, int > z;
};

void print_cube( const Block & cube )
{
  std::cout << "Cube isOn:" << cube.isOn << " x:" << cube.x.first << ".." << cube.x.second
            << " y:" << cube.y.first << ".." << cube.y.second
            << " z:" << cube.z.first << ".." << cube.z.second << "\n";
}


struct Comp
{
  bool operator() ( const std::tuple< int, int, int > & lhs, const std::tuple< int, int, int > & rhs ) const
  {
    if ( std::get< 0 >( lhs ) != std::get< 0 >( rhs ) )
      return std::get< 0 >( lhs ) < std::get< 0 >( rhs );

    if ( std::get< 1 >( lhs ) != std::get< 1 >( rhs ) )
      return std::get< 1 >( lhs ) < std::get< 1 >( rhs );

    return std::get< 2 >( lhs ) < std::get< 2 >( rhs );
  };
};

using t_block_turns = std::set< std::tuple< int, int, int >, Comp >;


std::vector< Block > prepare_input( const std::string & filename )
{
  // Read the file
  std::vector< std::string > sInput = FileReader::read_file( filename );

  std::vector< Block > blocks;

  for ( const std::string & _line : sInput )
  {
    std::regex word_regex(R"((\S+) x=([-]?\d+)..([-]?\d+),y=([-]?\d+)..([-]?\d+),z=([-]?\d+)..([-]?\d+))");
    std::smatch _match;
    std::regex_match( _line, _match, word_regex );

    if ( _match.size() != 8 )
      throw std::runtime_error( std::string( "Input is wrong: " ) + _line );

    Block block;

    block.isOn = ( _match[ 1 ] == "on" );
    block.x    = std::make_pair( std::stoi( _match[ 2 ] ), std::stoi( _match[ 3 ] ) );
    block.y    = std::make_pair( std::stoi( _match[ 4 ] ), std::stoi( _match[ 5 ] ) );
    block.z    = std::make_pair( std::stoi( _match[ 6 ] ), std::stoi( _match[ 7 ] ) );

    blocks.push_back( std::move( block ) );
  }

  return blocks;
}

void on_blocks( const Block & block, t_block_turns & blocksOn )
{
  if (   block.x.first < -50 || block.x.second > 50
      || block.y.first < -50 || block.y.second > 50
      || block.z.first < -50 || block.z.second > 50 )
    return;

  for ( int x = block.x.first; x <= block.x.second; ++x )
    for ( int y = block.y.first; y <= block.y.second; ++y )
      for ( int z = block.z.first; z <= block.z.second; ++z )
        blocksOn.emplace( x, y, z );
}

void off_blocks( const Block & block, t_block_turns & blocksOn )
{
  if (   block.x.first < -50 || block.x.second > 50
      || block.y.first < -50 || block.y.second > 50
      || block.z.first < -50 || block.z.second > 50 )
    return;

  for ( int x = block.x.first; x <= block.x.second; ++x )
    for ( int y = block.y.first; y <= block.y.second; ++y )
      for ( int z = block.z.first; z <= block.z.second; ++z )
        blocksOn.erase( std::make_tuple( x, y, z ) );
}

long long get_on_cubes( const std::vector< Block > & blocks )
{
  t_block_turns blocksOn;

  for ( const auto & _block : blocks )
  {
    if ( _block.isOn )
      on_blocks( _block, blocksOn );
    else
      off_blocks( _block, blocksOn );
  }

  return blocksOn.size();
}

long long ReactorReboot::task_1( const std::string & filename )
{

  return get_on_cubes( prepare_input( filename ) );
}

// --------------------------- TASK 2 -----------------------------

using t_any_const_coordinate = std::function< const std::pair< int, int > & ( const Block & ) >;
using t_any_coordinate       = std::function< std::pair< int, int > & ( Block & ) >;

static std::array< t_any_const_coordinate, 3 > any_const_coordinate =
        {
           []( const Block & block ) -> const std::pair< int, int > & { return block.x; }
         , []( const Block & block ) -> const std::pair< int, int > & { return block.y; }
         , []( const Block & block ) -> const std::pair< int, int > & { return block.z; }
        };

static std::array< t_any_coordinate, 3 > any_coordinate =
        {
           []( Block & block ) -> std::pair< int, int > & { return block.x; }
         , []( Block & block ) -> std::pair< int, int > & { return block.y; }
         , []( Block & block ) -> std::pair< int, int > & { return block.z; }
        };

long long get_cube_amount(  const std::pair< int, int > & x
                          , const std::pair< int, int > & y
                          , const std::pair< int, int > & z )
{
  return ( long long )( ( x.second - x.first + 1 ) )
                      * ( y.second - y.first + 1 )
                      * ( z.second - z.first + 1 );
}

long long get_cube_amount( const Block & block )
{
  return get_cube_amount( block.x, block.y, block.z );
}

bool isIntersected( const Block & lhs, const Block & rhs )
{
  for ( auto & _coordinate : any_const_coordinate )
    if (  _coordinate( lhs ).second < _coordinate( rhs ).first
       || _coordinate( lhs ).first  > _coordinate( rhs ).second )
      return false;

  return true;
}

bool isIntersected( const std::list< Block > & lhs, const Block & rhs )
{
  auto funcIntersection = [ &rhs ]( const Block & cube ){ return isIntersected( cube, rhs ); };

  return std::all_of( lhs.begin(), lhs.end(), funcIntersection );
}

bool isInside( const Block & lhs, const Block & rhs )
{
  if (   lhs.x.first <= rhs.x.first && lhs.x.second >= rhs.x.second
      && lhs.y.first <= rhs.y.first && lhs.y.second >= rhs.y.second
      && lhs.z.first <= rhs.z.first && lhs.z.second >= rhs.z.second )
    return true;

  return false;
}

bool isInside( const std::list< Block > & lhs, const Block & rhs )
{
  auto funcInside = [ &rhs ]( const Block & cube ){ return isInside( cube, rhs ); };

  return std::any_of( lhs.begin(), lhs.end(), funcInside );
}


Block split_block( const Block & lhs, Block & rhs )
{
  Block newCube;

  newCube.isOn = rhs.isOn;

  for ( std::size_t _idx = 0; _idx < 3; ++_idx )
  {

    if(    any_const_coordinate[ _idx ]( rhs ).first  <  any_const_coordinate[ _idx ]( lhs ).first
        && any_const_coordinate[ _idx ]( rhs ).second >=  any_const_coordinate[ _idx ]( lhs ).first )
    {
      if ( _idx != 0 )
        newCube.x = rhs.x;
      if ( _idx != 1 )
        newCube.y = rhs.y;
      if ( _idx != 2 )
        newCube.z = rhs.z;

      any_coordinate[ _idx ]( newCube ) = std::make_pair( any_const_coordinate[ _idx ]( lhs ).first, any_const_coordinate[ _idx ]( rhs ).second );

      any_coordinate[ _idx ]( rhs ).second = any_const_coordinate[ _idx ]( lhs ).first - 1;

      return newCube;
    }

    if(    any_const_coordinate[ _idx ]( rhs ).second > any_const_coordinate[ _idx ]( lhs ).second
        && any_const_coordinate[ _idx ]( rhs ).first  <= any_const_coordinate[ _idx ]( lhs ).second )
    {
      if ( _idx != 0 )
        newCube.x = rhs.x;
      if ( _idx != 1 )
        newCube.y = rhs.y;
      if ( _idx != 2 )
        newCube.z = rhs.z;

      any_coordinate[ _idx ]( newCube ) = std::make_pair( any_const_coordinate[ _idx ]( rhs ).first, any_const_coordinate[ _idx ]( lhs ).second );

      any_coordinate[ _idx ]( rhs ).first = any_const_coordinate[ _idx ]( lhs ).second + 1;

       return newCube;
    }
  }

  throw std::runtime_error("The Intersection hasn't been found");
}


bool split( const Block & cube, std::list< Block > & lNewCube )
{
//  std::cout << "Split with cube: ";
//  print_cube( cube );

  for ( auto itNewCube = lNewCube.begin(); itNewCube != lNewCube.end(); )
  {
    if ( isInside( cube, *itNewCube ) )
    {
//      std::cout << "Remove cube:";
//      print_cube( *itNewCube );
      itNewCube = lNewCube.erase( itNewCube );
      continue;
    }

    if ( !isIntersected( cube, *itNewCube ) )
    {
      ++itNewCube;
      continue;
    }

    // Split block
//    std::cout << "\tSplit       : ";
//    print_cube( *itNewCube );

    lNewCube.push_back( split_block( cube, *itNewCube ) );

//    std::cout << "\tSplit first : ";
//    print_cube( *itNewCube );
//    std::cout << "\tSplit second: ";
//    print_cube( lNewCube.back() );
  }

  return true;
}

void remove_inside_cubes( std::list< Block > & cubes, const Block & newCube )
{
  for( auto it = cubes.begin(); it != cubes.end();)
  {
    it = isInside( newCube, *it ) ? cubes.erase( it )
                                  : std::next( it );
  }
}

void on_cube( std::list< Block > & cubes, const Block & newCube )
{
  std::list< Block > lNewCube { newCube };

  remove_inside_cubes( cubes, newCube );

  for( auto & _cube : cubes )
    split( _cube, lNewCube );

  cubes.insert( cubes.end(), lNewCube.begin(), lNewCube.end() );
}

void split_off_cube( const Block & cube, const Block & offCube, std::list< Block > & cubes )
{
  // Front
  if ( cube.y.first != offCube.y.first )
    cubes.emplace_back( cube.x, std::make_pair( cube.y.first, offCube.y.first - 1 ), cube.z );

  // Back
  if ( cube.y.second != offCube.y.second )
    cubes.emplace_back( cube.x, std::make_pair( offCube.y.second + 1, cube.y.second ), cube.z );

  // Top
  if ( cube.z.second != offCube.z.second )
    cubes.emplace_back( cube.x, offCube.y, std::make_pair( offCube.z.second + 1, cube.z.second ) );

  // Bottom
  if ( cube.z.first != offCube.z.first )
    cubes.emplace_back( cube.x, offCube.y, std::make_pair( cube.z.first, offCube.z.first - 1 ) );

  // Right
  if ( cube.x.first != offCube.x.first )
    cubes.emplace_back( std::make_pair( cube.x.first, offCube.x.first - 1 ), offCube.y, offCube.z );

  // Left
  if ( cube.x.second != offCube.x.second )
    cubes.emplace_back( std::make_pair( offCube.x.second + 1, cube.x.second ), offCube.y, offCube.z );
}

void turn_off_inside_cubes( std::list< Block > & cubes, const Block & offCube )
{
  for ( auto it = cubes.begin(); it != cubes.end(); )
  {
    if ( !isInside( *it, offCube ) )
    {
      ++it;
      continue;
    }

    split_off_cube( *it, offCube, cubes );

    it = cubes.erase( it );
  }
}

bool is_intersected( const std::list< Block > & cubes, const std::list< Block > & lOffCubes )
{
  for ( const auto & _cube : cubes )
    for ( const auto & _offCube : lOffCubes )
      if ( isIntersected( _cube, _offCube ) )
        return true;

  return false;
}

void remove_intersection_off_cubes( std::list< Block > & cubes, std::list< Block > & lOffCubes )
{
  for ( auto itOff = lOffCubes.begin(); itOff != lOffCubes.end(); ++itOff )
  {
//    std::cout << "Off sub cube: ";
//    print_cube( *itOff );

    for ( auto _cube : cubes )
    {
      while( isIntersected( _cube, *itOff ) && !isInside( _cube, *itOff ) )
      {
//        std::cout << "\tCube           : ";
//        print_cube( _cube );
//        std::cout << "\tOffCube        : ";
//        print_cube( *itOff );
        lOffCubes.push_back( split_block( _cube, *itOff ));
//        std::cout << "\tOffCube first  : ";
//        print_cube( *itOff );
//        std::cout << "\tOffCube second : ";
//        print_cube( lOffCubes.back() );
      }
    }
  }
}

void off_cube( std::list< Block > & cubes, const Block & offCube )
{
  std::list< Block > lOffCubes { offCube };

  while ( is_intersected( cubes, lOffCubes ) )
  {
    // Split OffCubes to non-intersected
    remove_intersection_off_cubes( cubes, lOffCubes );

    // If inside
    for ( auto &_offCube: lOffCubes )
      turn_off_inside_cubes( cubes, _offCube );
  }
}

long long calculate_cubes_amount( const std::list< Block > & cubes )
{
  long long res { 0 };

  for ( const auto & _cube : cubes )
    res += get_cube_amount( _cube );

  return res;
}

long long run( const std::vector< Block > & blocks )
{
  std::list< Block > cubes;

  for ( const auto & _newCube : blocks )
  {
//    print_cube( _newCube );

    if ( _newCube.isOn )
      on_cube( cubes, _newCube );
    else
      off_cube( cubes, _newCube );
  }

//  std::cout << "All cubes:\n";
//  for ( const auto & _cube : cubes )
//    print_cube( _cube );

  return calculate_cubes_amount( cubes );
}

long long ReactorReboot::task_2( const std::string & filename )
{
  return run( prepare_input( filename ) );
}
