//
// Created by alexey on 15.01.2022.
//

#include "Snailfish.h"

#include <vector>
#include <stdexcept>
#include <iostream>
#include <functional>
#include <limits>

#include "common/file_reader.h"


struct Node
{
  explicit Node ( Node * i_parent )
    : parent { i_parent }
  {}

  Node * left  { nullptr };
  Node * right { nullptr };
  Node * parent { nullptr };

  int leftNum  { -1 };
  int rightNum { -1 };
};

// Function declaration
bool split( Node * node );


Node * create_snail_node( const std::string & strMath, std::size_t & idx, Node * parent = nullptr )
{
  if ( strMath[ idx ] != '[' )
    throw std::runtime_error( "Wrong index for '[' create_snail_node function with idx: " + std::to_string( idx ) + " str: " + strMath );

  // Create new node
  Node * newNode = new Node( parent );

  // Left number/node
  ++idx;

  // left
  if ( strMath[ idx ] == '[' )
    newNode->left = create_snail_node( strMath, idx, newNode );
  else
    newNode->leftNum = strMath[ idx ] - '0';

  // Comma
  ++idx;

  if ( strMath[ idx ] != ',' )
    throw std::runtime_error( "Wrong index for ',' create_snail_node function with idx: " + std::to_string( idx ) + " str: " + strMath );

  // Right number/node
  ++idx;

  if ( strMath[ idx ] == '[' )
    newNode->right = create_snail_node( strMath, idx, newNode );
  else
    newNode->rightNum = strMath[ idx ] - '0';

  // ']'
  ++idx;

  if ( strMath[ idx ] != ']' )
    throw std::runtime_error( "Wrong index for ']' create_snail_node function with idx: " + std::to_string( idx ) + " str: " + strMath );

  return newNode;
}

Node * convert_to_node( const std::string & strMath )
{
  std::size_t idx = 0;
  return create_snail_node( strMath, idx );
}

void print_node( Node * node )
{
  // Print left
  std::cout << '[';
  if ( node->left != nullptr )
    print_node( node->left );
  else
    std::cout << node->leftNum;
  std::cout << ", ";

  // Print right
  if ( node->right != nullptr )
    print_node( node->right );
  else
    std::cout << node->rightNum;
  std::cout << "]";
}

Node * find_nearest_node( Node * node, bool findLeft )
{
  auto next_node = findLeft ? []( Node * node ){ return node->left;  }
                            : []( Node * node ){ return node->right; };

  Node * parent = node->parent;
  Node * child = node;

  while ( parent != nullptr && child == next_node( parent ) )
  {
    child = parent;
    parent = parent->parent;
  }

  return parent;
}

Node * find_node_with_number( Node * node, bool findLeft )
{
  auto next_node = findLeft ? []( Node * node ){ return node->left;  }
                            : []( Node * node ){ return node->right; };

  while ( next_node( node ) != nullptr )
    node = next_node( node );

  return node;
}

void add_to_next_number( Node * node, int number, bool findLeft )
{
  Node * parent = find_nearest_node( node, findLeft );

  // Node isn't found
  if ( parent == nullptr )
    return;

  // If left is number
  if ( findLeft && parent->left == nullptr )
  {
    parent->leftNum += number;
    return;
  }

  // If right is number
  if ( !findLeft && parent->right == nullptr )
  {
    parent->rightNum += number;
    return;
  }

  // Get left/right node
  parent = findLeft ? parent->left : parent->right;

  // Get right/left number
  parent = find_node_with_number( parent, !findLeft );

  if ( findLeft )
    parent->rightNum += number;
  else
    parent->leftNum += number;
}


void do_explode( Node * node )
{
  // Explode Left
  add_to_next_number( node, node->leftNum, /* findLeft */ true  );
  add_to_next_number( node, node->rightNum, /* findLeft */ false );

  Node * parent = node->parent;

  if ( parent->left == node )
  {
    parent->left = nullptr;
    parent->leftNum = 0;
  }
  else
  {
    parent->right = nullptr;
    parent->rightNum = 0;
  }

  delete node;
}

bool explode( Node * head, Node * node, int nesting = 0 )
{
  if ( nesting == 4 && ( node->left != nullptr || node->right != nullptr ) )
    throw std::runtime_error( "Nesting problem" );

  if ( nesting < 4 )
  {
    if ( node->left != nullptr && explode( head, node->left, nesting + 1 ) )
      return true;

    if ( node->right != nullptr && explode( head, node->right, nesting + 1 ) )
      return true;

    return false;
  }

  // Nesting == 4
  do_explode( node );

  return true;
}

Node * get_new_split_node( int number, Node * parent )
{
  Node * newNode = new Node( parent );
  newNode->leftNum = number / 2;
  newNode->rightNum = ( number + 1 ) / 2;

  return newNode;
}

bool split( Node * node )
{
  if ( node->left != nullptr && split( node->left ) )
    return true;

  // Left
  if ( node->left == nullptr && node->leftNum > 9 )
  {
    node->left = get_new_split_node( node->leftNum, node );
    node->leftNum = -1;
    return true;
  }

  if ( node->right != nullptr && split( node->right ) )
    return true;

  // Right
  if ( node->right == nullptr && node->rightNum > 9 )
  {
    node->right = get_new_split_node( node->rightNum, node );
    node->rightNum = -1;
    return true;
  }

  return false;
}

Node * add_nodes( Node * lhs, Node * rhs )
{
  Node * head = new Node( nullptr );

  head->left = lhs;
  head->right = rhs;

  lhs->parent = head;
  rhs->parent = head;

  return head;
}

int magnitude( Node * node )
{
  // Left
  int res = 3 * ( node->left == nullptr ? node->leftNum : magnitude( node->left ) );

  // Right
  res += 2 * ( node->right == nullptr ? node->rightNum : magnitude( node->right ) );

  return res;
}

void normalize( Node * head )
{
  while ( explode( head, head ) || split( head ) )
  { }
}

int Snailfish::task_1( const std::string &filename )
{
  // Read the file
  std::vector< std::string > sInput = FileReader::read_file( filename );

  Node * head = convert_to_node( sInput[ 0 ] );

  for ( std::size_t idx = 1; idx < sInput.size(); ++idx )
  {
    head = add_nodes( head, convert_to_node( sInput[ idx ] ) );
    normalize( head );
  }

  print_node( head );
  std::cout << "\n\n";

  return magnitude( head );
}

int Snailfish::task_2( const std::string &filename )
{
  std::vector< std::string > sInput = FileReader::read_file( filename );
  int maxScore = std::numeric_limits< int >::min();

  for ( std::size_t _idx1 = 0; _idx1 < sInput.size(); ++_idx1 )
  {
    for ( std::size_t _idx2 = 0; _idx2 < sInput.size(); ++_idx2 )
    {
      if ( _idx1 == _idx2 )
        continue;

      Node * head = add_nodes( convert_to_node( sInput[ _idx1 ] ), convert_to_node( sInput[ _idx2 ] ) );
      normalize( head );
      maxScore = std::max( maxScore, magnitude( head ) );
    }
  }

  return maxScore;
}
