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


struct Node
{
  explicit Node( std::string _name ) : name { _name } {}

  std::string name;
  std::list< Node * > neighbours;

  void print() const
  {
    std::cout << "Node " << name << " : ";
    for ( auto _neighbours : neighbours )
      std:: cout << _neighbours->name << ", ";
    std::cout << "\n";
  }
};

using t_nodes = std::list< Node >;


Node & add_node_name( const std::string & nodeName, t_nodes & nodes )
{
  // Try to find a node
  auto pNode = std::find_if( nodes.begin(), nodes.end(), [ &nodeName ]( const Node & node ){ return node.name == nodeName; } );

  // Is the node found
  if ( pNode != nodes.end() )
    return *pNode;

  // Add a new node
  return nodes.emplace_back( nodeName );
}

void bind_node( Node & fromNode, Node & toNode )
{
  if ( std::find( fromNode.neighbours.begin(), fromNode.neighbours.end(), & toNode ) == fromNode.neighbours.end() )
    fromNode.neighbours.push_back( & toNode );
}

t_nodes prepare_input( const std::string & filename )
{
  t_nodes nodes;

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
    Node & firstNode  = add_node_name( nodeNames[ 0 ], nodes );
    Node & secondNode = add_node_name( nodeNames[ 1 ], nodes );

    // Add links
    bind_node( firstNode, secondNode );
    bind_node( secondNode, firstNode );
  }

  return nodes;
}

const Node & get_node( const std::string & nodeName, const t_nodes & nodes )
{
  auto pNode = std::find_if( nodes.begin(), nodes.end(), [ &nodeName ]( const Node & node ){ return node.name == nodeName; } );

  if ( pNode == nodes.end() )
    throw std::runtime_error( "Node isn't found" );

  return *pNode;
}

struct VisitedNode
{
  VisitedNode( const Node * _node, std::set< std::string > _visited )
    : node { _node }
    , visited { std::move( _visited ) }
  {}

  VisitedNode( const Node * _node, std::set< std::string > _visited, bool _visitedTwice )
    : node { _node }
    , visited { std::move( _visited ) }
    , visitedTwice { _visitedTwice }
  {}

  const Node * node;
  std::set< std::string > visited;
  bool visitedTwice { false };
};

bool is_capital( const std::string & str )
{
  return std::all_of( str.begin(), str.end(), []( const char ch ){ return std::isupper( ch ); } );
//  for ( const auto _ch : str )
//    if ( _ch < 'A' || _ch > 'Z' )
//      return false;
//
//  return true;
}

int depth_search( const t_nodes & nodes )
{
  int amountOfPaths { 0 };
  std::set< std::string > visited;

  // Get start & end points
  const auto & startNode = get_node( "start", nodes );
  const auto & endNode   = get_node( "end"  , nodes );

  std::stack< VisitedNode > nextPoints;

  // Push the start
  visited.insert( startNode.name );
  nextPoints.emplace( & startNode, visited );

  while( !nextPoints.empty()  )
  {
    // Pop the first node from the queue
    VisitedNode currentNode = nextPoints.top();
    nextPoints.pop();

    // For all neighbours
    for ( const Node * _neighbour : currentNode.node->neighbours )
    {
      // End Node
      if ( _neighbour == & endNode )
      {
        ++amountOfPaths;
        continue;
      }

      // Is capital node
      if ( is_capital( _neighbour->name ) )
      {
        nextPoints.emplace( _neighbour, currentNode.visited );
        continue;
      }

      // Is lowercase node and It's visited
      if ( currentNode.visited.count( _neighbour->name ) )
        continue;

      // Is lowercase node and it isn't visited
      {
        std::set< std::string > newVisitedNodes = currentNode.visited;
        newVisitedNodes.insert( _neighbour->name );
        nextPoints.emplace( _neighbour, newVisitedNodes );
      }
    }
  }

  return amountOfPaths;
}

int depth_search_task_2( const t_nodes & nodes )
{
  int amountOfPaths { 0 };
  std::set< std::string > visited;

  // Get start & end points
  const auto & startNode = get_node( "start", nodes );
  const auto & endNode   = get_node( "end"  , nodes );

  std::stack< VisitedNode > nextPoints;

  // Push the start
  visited.insert( startNode.name );
  nextPoints.emplace( & startNode, visited );

  while( !nextPoints.empty()  )
  {
    // Pop the first node from the queue
    VisitedNode currentNode = nextPoints.top();
    nextPoints.pop();

    // For all neighbours
    for ( const Node * _neighbour : currentNode.node->neighbours )
    {
      // Start point
      if ( _neighbour == & startNode )
        continue;

      // End Node
      if ( _neighbour == & endNode )
      {
        ++amountOfPaths;
        continue;
      }

      // Is capital node
      if ( is_capital( _neighbour->name ) )
      {
        nextPoints.emplace( _neighbour, currentNode.visited, currentNode.visitedTwice );
        continue;
      }

      // Is lowercase node and It's visited
      if ( currentNode.visited.count( _neighbour->name ) )
      {
        if ( currentNode.visitedTwice )
          continue;

        std::set< std::string > newVisitedNodes = currentNode.visited;
        newVisitedNodes.insert( _neighbour->name );
        nextPoints.emplace( _neighbour, newVisitedNodes, true );

        continue;
      }

      // Is lowercase node and it isn't visited
      {
        std::set< std::string > newVisitedNodes = currentNode.visited;
        newVisitedNodes.insert( _neighbour->name );
        nextPoints.emplace( _neighbour, newVisitedNodes, currentNode.visitedTwice );
      }
    }
  }

  return amountOfPaths;
}


int PassagePathing::task_1( const std::string & filename )
{
  t_nodes nodes = prepare_input( filename );

  return depth_search( nodes );
}

int PassagePathing::task_2( const std::string &filename )
{
  t_nodes nodes = prepare_input( filename );

  return depth_search_task_2( nodes );
}
