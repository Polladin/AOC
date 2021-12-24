//
// Created by alexey on 21.12.2021.
//

#include "PassagePathing.h"

#include <vector>
#include <list>
#include <map>
#include <stack>
#include <queue>
#include <set>
#include <cctype>

#include "common/file_reader.h"
#include "common/common.h"


PassagePathing::Node & PassagePathing::add_node_name( const std::string & nodeName )
{
  // Try to find a node
  auto pNode = std::find_if( nodes.begin(), nodes.end(), [ &nodeName ]( const Node & node ){ return node.name == nodeName; } );

  // Is the node found
  if ( pNode != nodes.end() )
    return *pNode;

  // Add a new node
  return nodes.emplace_back( nodeName );
}

void PassagePathing::bind_node( Node & fromNode, Node & toNode )
{
  if ( std::find( fromNode.neighbours.begin(), fromNode.neighbours.end(), & toNode ) == fromNode.neighbours.end() )
    fromNode.neighbours.push_back( & toNode );
}

void PassagePathing::bind_node_both_direction( Node & fromNode, Node & toNode )
{
  bind_node( fromNode, toNode );
  bind_node( toNode, fromNode );
}

const PassagePathing::Node & PassagePathing::get_node( const std::string & nodeName ) const
{
  auto pNode = std::find_if( nodes.begin(), nodes.end(), [ &nodeName ]( const Node & node ){ return node.name == nodeName; } );

  if ( pNode == nodes.end() )
    throw std::runtime_error( "Node isn't found" );

  return *pNode;
}

void PassagePathing::prepare_input( const std::string & filename )
{
  // Read the file
  std::vector< std::string > sInput = FileReader::read_file( filename );

  for ( const auto & _line : sInput )
  {
    // Split 2 node names
    std::vector< std::string > nodeNames = common::split_line( _line, '-' );

    // Must be only 2 nodes
    if ( nodeNames.size() != 2 )
      throw std::runtime_error( "Size of split array must be 2" );

    // Get reference to the nodes
    bind_node_both_direction(  add_node_name( nodeNames[ 0 ] )
                             , add_node_name( nodeNames[ 1 ] ) );
  }

  startNode = & get_node( "start" );
  endNode   = & get_node( "end"   );
}

static bool is_capital( const std::string & str )
{
  return std::all_of( str.begin(), str.end(), []( const char ch ){ return std::isupper( ch ); } );
}

int PassagePathing::process_neighbour(  const Node * neighbour
                                      , const VisitedNode & currentNode
                                      , std::stack< VisitedNode > & nextPoints ) const
{
  // Start point
  if ( neighbour == startNode )
    return 0;

  // End Node, add +1 to paths
  if ( neighbour == endNode )
    return 1;

  // Is capital node
  if ( is_capital( neighbour->name ) )
  {
    nextPoints.emplace( neighbour, currentNode.visited, currentNode.visitedTwice );
    return 0;
  }

  const bool isLowercaseNodeVisited = currentNode.visited.count( neighbour->name ) > 0;

  // Is lowercase node and It's visited twice
  if ( isLowercaseNodeVisited && ( currentNode.visitedTwice || isPart1 ) )
    return 0;

  // Is lowercase node and it isn't visited twice
  nextPoints.emplace( neighbour, currentNode.visited, currentNode.visitedTwice || isLowercaseNodeVisited );
  nextPoints.top().visited.insert( neighbour->name );

  return 0;
}

int PassagePathing::depth_search() const
{
  int amountOfPaths { 0 };

  std::stack< VisitedNode > nextPoints;

  // Push the start
  nextPoints.emplace( startNode, std::set< std::string >() );

  while( !nextPoints.empty()  )
  {
    // Pop the first node from the stack
    VisitedNode currentNode = nextPoints.top();
    nextPoints.pop();

    // For all neighbours
    for ( const Node * _neighbour : currentNode.node->neighbours )
      amountOfPaths += process_neighbour( _neighbour, currentNode, nextPoints );
  }

  return amountOfPaths;
}


int PassagePathing::task_1( const std::string & filename )
{
  isPart1 = true;

  prepare_input( filename );

  return depth_search();
}

int PassagePathing::task_2( const std::string &filename )
{
  isPart1  = false;

  prepare_input( filename );

  return depth_search();
}
