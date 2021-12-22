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

// ----------------- Node ------------------------
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

// ----------------- VisitedNode ------------------------
struct VisitedNode
{
  VisitedNode( const Node * _node, std::set< std::string > _visited, bool _visitedTwice = false )
          : node { _node }
          , visited { std::move( _visited )  }
          , visitedTwice { _visitedTwice }
  {}

  const Node * node;
  std::set< std::string > visited;
  bool visitedTwice { false };
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

void bind_node_both_direction( Node & fromNode, Node & toNode )
{
  bind_node( fromNode, toNode );
  bind_node( toNode, fromNode );
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
    bind_node_both_direction(  add_node_name( nodeNames[ 0 ], nodes )
                             , add_node_name( nodeNames[ 1 ], nodes ) );
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



bool is_capital( const std::string & str )
{
  return std::all_of( str.begin(), str.end(), []( const char ch ){ return std::isupper( ch ); } );
}


int depth_search( const t_nodes & nodes, const bool isPart1 )
{
  int amountOfPaths { 0 };

  // Get start & end points
  const auto & startNode = get_node( "start", nodes );
  const auto & endNode   = get_node( "end"  , nodes );

  std::stack< VisitedNode > nextPoints;

  // Push the start
  nextPoints.emplace( & startNode, std::set< std::string >() );

  while( !nextPoints.empty()  )
  {
    // Pop the first node from the stack
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

      const bool isLowercaseNodeVisited = currentNode.visited.count( _neighbour->name ) > 0;

      // Is lowercase node and It's visited twice
      if ( isLowercaseNodeVisited && ( currentNode.visitedTwice || isPart1 ) )
        continue;

      // Is lowercase node and it isn't visited twice
      {
        nextPoints.emplace( _neighbour, currentNode.visited, currentNode.visitedTwice || isLowercaseNodeVisited );
        nextPoints.top().visited.insert( _neighbour->name );
      }
    }
  }

  return amountOfPaths;
}


int PassagePathing::task_1( const std::string & filename )
{
  t_nodes nodes = prepare_input( filename );

  return depth_search( nodes, true /* is part 1 */ );
}

int PassagePathing::task_2( const std::string &filename )
{
  t_nodes nodes = prepare_input( filename );

  return depth_search( nodes, false /* is part 1 */ );
}
