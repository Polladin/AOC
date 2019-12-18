
#include "oxygen.h"

#include <map>
#include <queue>


static const int NOT_VISITED = -1;
static const int BLACK = 0;
static const int WHITE = 1;

static const int UP = 1;
static const int DOWN = 2;
static const int LEFT = 3;
static const int RIGHT = 4;

static std::map< int, int > REVERSE_DIRECTION =
{
    { UP   , DOWN  }
  , { DOWN , UP    }
  , { RIGHT, LEFT  }
  , { LEFT , RIGHT }
};


int Oxygen::run_part_1( const std::string & fileName )
{
  comp.prepare_day_7_part_1( fileName );

  std::vector< int > pathToOxygen;
  t_coord oxygenCoordinate( 0, 0 );

  bfs( oxygenCoordinate, std::vector< int > (), pathToOxygen, oxygenCoordinate );

  comp.prepare_day_7_part_1( fileName );

  return bfs( oxygenCoordinate, pathToOxygen, pathToOxygen, oxygenCoordinate );
}

int Oxygen::bfs( const t_coord & startCoordinate, std::vector< int > pathToStartNode, std::vector< int > & pathToOxygen, t_coord & oxygenCoordinate )
{
  // How to return in start position
  t_back_path backPath( compare_coords );

  // Alredy viewed nodes
  t_colors colors( compare_coords );

  std::queue< t_coord > que;
  
  // Push the start node and initialize backPath
  que.push( startCoordinate );
  backPath[ startCoordinate ] = std::vector< int >();
  colors[ startCoordinate ] = 0;

  // Move robot to start Node
  std::for_each( pathToStartNode.begin(), pathToStartNode.end(), []( int & x ){ x = REVERSE_DIRECTION[ x ]; } );
  move_robot( pathToStartNode );

  while ( !que.empty() )
  {
    // Pop the node
    t_coord currentNode = que.front();
    que.pop();

    // Move robot to current Node
    std::vector< int > pathToNode( backPath[ currentNode ].begin(), backPath[ currentNode ].end() );
    std::for_each( pathToNode.begin(), pathToNode.end(), []( int & x ){ x = REVERSE_DIRECTION[ x ]; } );
    move_robot( pathToNode );

    // Push not visited neighbor nodes
    // returns is Ozygen found
    if ( push_not_visited_nodes( currentNode, colors, backPath, que ) )
      break;

    // Move robot to start point
    std::vector< int > pathToStart( backPath[ currentNode ].rbegin(), backPath[ currentNode ].rend() );
    move_robot( pathToStart );
  }

  print_map( colors, startCoordinate );

  // Find the longest path
  int maxSize = 0;

  // Find node with color == 2
  for ( const auto & _elem : colors )
  {
    maxSize = std::max( maxSize, (int)backPath[ _elem.first ].size() );

    if ( _elem.second != 2 )
      continue;

    pathToOxygen = backPath[ _elem.first ];
    oxygenCoordinate = _elem.first;
  }

  return maxSize;
}

bool Oxygen::push_not_visited_nodes( const t_coord & currentNode, t_colors & colors, t_back_path & backPath, std::queue< t_coord > & que )
{
  // Get node neighbors
  std::vector< std::pair< t_coord, int > > neighbors = get_neighbors( currentNode );

  for ( const std::pair< t_coord, int > & _nextNode : neighbors )
  {
    if ( get_color( colors, _nextNode.first ) != NOT_VISITED )
      continue;

    // Try to visit it
    int visitedNode = visit_node( _nextNode );

    // Add node to queue
    if ( visitedNode != 0 )
      que.push( _nextNode.first );

    // Add reverse path how to return in the start pos
    backPath[ _nextNode.first ] = backPath[ currentNode ];
    backPath[ _nextNode.first ].push_back( REVERSE_DIRECTION[ _nextNode.second ] );

    // Mark node as visited
    colors[ _nextNode.first ] = visitedNode;

    /*if ( visitedNode == 2 )
      return true;*/
  }
  return false;
}

void Oxygen::move_robot( const std::vector<int> & directions )
{
  std::vector< long long > out;

  for ( auto _dir : directions )
  {
    std::queue< long long > in;
    in.push( _dir );

    comp.run_day_7_part_1( in, out );
  }
}

int Oxygen::visit_node( std::pair<t_coord, int> node )
{
  std::queue< long long > in;
  std::vector< long long > out;

  in.push( node.second );

  comp.run_day_7_part_1( in, out );

  int resCode = out.front();

  if ( resCode != 0 /* not filled cell */ )
  {
    // return back to current node
    in = std::queue< long long >();
    in.push( REVERSE_DIRECTION[ node.second ] );

    comp.run_day_7_part_1( in, out );
  }

  return resCode;
}

int Oxygen::get_color( const t_colors & colors, const t_coord & pos )
{
  auto it = colors.find( pos );
  if ( it == colors.end() )
    return NOT_VISITED;

  return it->second;
}

std::vector< std::pair< t_coord, int > > Oxygen::get_neighbors( const t_coord & pos )
{
  std::vector< std::pair< t_coord, int > > res = 
  {  { { pos.x - 1, pos.y     }, LEFT  }
   , { { pos.x + 1, pos.y     }, RIGHT } 
   , { { pos.x    , pos.y + 1 }, UP    } 
   , { { pos.x    , pos.y - 1 }, DOWN  } };

  return res;
}


