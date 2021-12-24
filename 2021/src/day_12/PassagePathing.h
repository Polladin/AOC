//
// Created by alexey on 21.12.2021.
//

#ifndef ADVENTOFCODE2021_PASSAGEPATHING_H
#define ADVENTOFCODE2021_PASSAGEPATHING_H

#include <string>
#include <iostream>
#include <list>
#include <set>
#include <stack>


class PassagePathing
{
private:

  // ----------------- Node ------------------------
  struct Node
  {
    explicit Node( std::string _name ) : name { std::move( _name ) } {}

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

public:

  int task_1( const std::string & filename );
  int task_2( const std::string & filename );

private:

  [[ nodiscard ]]
  const Node & get_node( const std::string & nodeName ) const;

  Node & add_node_name( const std::string & nodeName );

  void prepare_input( const std::string & filename );

  void bind_node( Node & fromNode, Node & toNode );
  void bind_node_both_direction( Node & fromNode, Node & toNode );

  [[ nodiscard ]]
  int depth_search() const;
  int process_neighbour(  const Node * neighbour, const VisitedNode & currentNode , std::stack< VisitedNode > & nextPoints ) const;

private:

  bool isPart1 { true };

  t_nodes nodes;

  const Node * startNode;
  const Node * endNode;
};


#endif //ADVENTOFCODE2021_PASSAGEPATHING_H
