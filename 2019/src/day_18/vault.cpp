
#include "vault.h"

#include "common/file_reader.h"

#include <queue>
#include <map>
#include <cctype>
#include <limits>

static const unsigned char BLACK = 0;
static const unsigned char WHITE = 1;


int Vault::run_part_1( const std::string & fileName )
{
  t_field vault = FileReader::read_file( fileName );

  // Initialize keys position and distance between keys
  fill_keys_distance( vault );

  std::unique_ptr< Node > head = std::make_unique< Node >( 0, "@" );

  return add_next_nodes( head, {}, vault );

  //std::pair< int, std::string > res = dfs( startPoint, vault );

  //std::cout << "Path : " << res.first << "  keys: " << res.second << "\n";

  //return 0;
}

int Vault::run_part_2( const std::string & fileName )
{
  t_field vault = FileReader::read_file( fileName );

  // Find pattern
  std::map< char, int > nodes = part_2_modify( vault );

  // std::unique_ptr< Node > head = std::make_unique< Node >( 0, "@" );

  //return add_next_nodes_2( head, nodes, vault );

  std::vector< char > robots{ '1', '2', '3', '4' };
  std::pair< std::string, int > path;

  return run_robots( vault, robots, path );
}

std::map<char, int> Vault::part_2_modify( t_field & field )
{
  std::map<char, int> res;

  t_coord startPoint = get_start_point( field );

  field[ startPoint.y     ][ startPoint.x     ] = '#';
  field[ startPoint.y + 1 ][ startPoint.x     ] = '#';
  field[ startPoint.y - 1 ][ startPoint.x     ] = '#';
  field[ startPoint.y     ][ startPoint.x + 1 ] = '#';
  field[ startPoint.y     ][ startPoint.x - 1 ] = '#';

  field[ startPoint.y + 1 ][ startPoint.x + 1 ] = '1';
  field[ startPoint.y - 1 ][ startPoint.x + 1 ] = '2';
  field[ startPoint.y - 1 ][ startPoint.x - 1 ] = '3';
  field[ startPoint.y + 1 ][ startPoint.x - 1 ] = '4';

  res.emplace( '1', 0 );
  res.emplace( '2', 0 );
  res.emplace( '3', 0 );
  res.emplace( '4', 0 );

  keysPosition[ '1' ] = t_coord( startPoint.x + 1, startPoint.y + 1 );
  keysPosition[ '2' ] = t_coord( startPoint.x + 1, startPoint.y - 1 );
  keysPosition[ '3' ] = t_coord( startPoint.x - 1, startPoint.y - 1 );
  keysPosition[ '4' ] = t_coord( startPoint.x - 1, startPoint.y + 1 );

  // Initialize keys position and distance between keys
  fill_keys_distance( field );

  field[ startPoint.y + 1 ][ startPoint.x + 1 ] = '.';
  field[ startPoint.y - 1 ][ startPoint.x + 1 ] = '.';
  field[ startPoint.y - 1 ][ startPoint.x - 1 ] = '.';
  field[ startPoint.y + 1 ][ startPoint.x - 1 ] = '.';

  return res;
}


std::map< char, int > Vault::get_distance_to_other_keys( t_coord startPoint, const t_field & field, bool & hasDoors )
{
  t_distance distance( compare_coords );
  std::map< char, int > distToKeys;

  hasDoors = false;

  // Initizlize colors
  t_color color( field.size(), std::vector< unsigned char >( field[ 0 ].size(), BLACK ) );

  // Create a queue for BFS and initialize by start point
  std::queue< t_coord > que;
  que.push( startPoint );

  // Mark start point as visited
  color[ startPoint.y ][ startPoint.x ] = WHITE;

  while ( !que.empty() )
  {
    t_coord currentPoint = que.front();
    que.pop();

    // Is a key
    if (   field[ currentPoint.y ][ currentPoint.x ] >= 'a' && field[ currentPoint.y ][ currentPoint.x ] <= 'z' 
        && !( currentPoint.x == startPoint.x && currentPoint.y == startPoint.y ) )
    {
      distToKeys.emplace( field[ currentPoint.y ][ currentPoint.x ], distance[ currentPoint ] );
    }

    if ( field[ currentPoint.y ][ currentPoint.x ] >= 'A' && field[ currentPoint.y ][ currentPoint.x ] <= 'Z' )
    {
      hasDoors = true;
      continue;
    }

    // Get next hops
    get_next_nodes( currentPoint, que, color, field, distance );
  }

  return distToKeys;
}

int Vault::add_next_nodes( std::unique_ptr< Node >& head, std::map< char, int > nextNodes, const t_field & field )
{
  const bool isKeyHasDoor = keysWithDoor.count( head->path.back() ) != 0;

  // If it's a start point OR a key with door need to refresh nextNodes
  if ( isKeyHasDoor || head->path == "@" )
  {
    //nextNodes = get_distance_to_other_keys( keysPosition[ head->path.back() ], field );
    bool hasDoors;
    std::map<char, int> additionalNodes = get_distance_to_other_keys( keysPosition[ head->path.back() ], field, hasDoors );

    for ( const auto & _node : additionalNodes )
      if ( nextNodes.count( _node.first ) == 0 )
        nextNodes.insert( _node );
  }

  if ( nextNodes.size() == 0 )
  {
    //std::cout << "Path : " << head->path << " cost: " << head->dist << "\n";
    return head->dist;
  }

  // add to cache
  std::string cacheKey{ head->path.back() };
  int minDist = std::numeric_limits< int >::max();

  // Make cache key
  for ( const auto & node : nextNodes )
    cacheKey += node.first;

  auto it = cache.find( cacheKey );
  if ( it != cache.end() )
  {
    std::unique_ptr< Node > newNode = std::make_unique< Node >( head->dist + it->second, head->path + "_CACHE_" );
    head->childs.emplace_back( std::move( newNode ) );
    return head->dist + it->second;
  }

  // 
  for ( const auto & node : nextNodes )
  {
    int distToNode = head->dist + keysDistance[ head->path.back() ][ node.first ];

    // Create the new node
    std::unique_ptr< Node > newNode = std::make_unique< Node > (  distToNode, head->path + node.first );

    // Make a copy from the field
    t_field copyField = field;

    // Remove the key and the door from the map
    t_coord pos = keysPosition[ node.first ];
    copyField[ pos.y ][ pos.x ] = '.';
    open_doors( node.first, copyField );

    // Exclude the key
    std::map< char, int > nodes = nextNodes;
    nodes.erase( node.first );

    minDist = std::min( minDist, add_next_nodes( newNode, nodes, copyField ) );

    head->childs.emplace_back( std::move( newNode ) );
  }

  // Add to cache
  cache[ cacheKey ] = minDist - head->dist;
  //std::cout << "Add to cache: " << cacheKey << " : " << cache[ cacheKey ] << "\n";

  return minDist;
}

int Vault::add_next_nodes_2( std::unique_ptr<Node>& head, std::map<char, int> nextNodes, const t_field & field )
{
  const bool isKeyHasDoor = keysWithDoor.count( head->path.back() ) != 0;

  std::cout << "Field: \n";
  for ( int y = 0; y < field.size(); ++y )
  {
    for ( int x = 0; x < field[ y ].size(); ++x )
      std::cout << field[ y ][ x ];
    std::cout << "\n";
  }
  std::cout << "\n";

  std::cout << "Next nodes before: ";
  for ( const auto & el : nextNodes )
    std::cout << el.first << " ";
  std::cout << "\n";

  // If it's a start point OR a key with door need to refresh nextNodes
  if ( isKeyHasDoor || ( head->path.back() >= '1' && head->path.back() <= '4' ) ) // || head->path == "@"
  {
    bool hasDoors;
    std::map<char, int> additionalNodes = get_distance_to_other_keys( keysPosition[ head->path.back() ], field, hasDoors );

    if ( additionalNodes.size() == 0 && hasDoors && ( head->path.back() >= '1' && head->path.back() <= '4' ) )
      return std::numeric_limits< int >::max();

    if ( additionalNodes.size() == 0 && hasDoors )
    {
      // 
    }

    for ( const auto & _node : additionalNodes )
      if ( nextNodes.count( _node.first ) == 0 )
        nextNodes.insert( _node );
  }

  std::cout << "Next nodes after: ";
  for ( const auto & el : nextNodes )
    std::cout << el.first << " ";
  std::cout << "\n\n";

  if ( nextNodes.size() == 0 )
  {
    std::cout << "Path : " << head->path << " cost: " << head->dist << "\n";
    return head->dist;
  }

  int minDist = std::numeric_limits< int >::max();

  for ( const auto & node : nextNodes )
  {
    int distToNode = -1; // head->dist + keysDistance[ head->path.back() ][ node.first ];
    for ( auto it = head->path.rbegin(); it != head->path.rend(); ++it )
      if ( keysDistance[ *it ][ node.first ] != -1 )
        distToNode = head->dist + keysDistance[ *it ][ node.first ];
    
    std::cout << "Node - Path : " << head->path << " cost: " << head->dist << "\n";

    // Create the new node
    std::unique_ptr< Node > newNode = std::make_unique< Node >( distToNode, head->path + node.first );

    // Make a copy from the field
    t_field copyField = field;

    // Remove the key and the door from the map
    t_coord pos = keysPosition[ node.first ];
    copyField[ pos.y ][ pos.x ] = '.';
    open_doors( node.first, copyField );

    // Exclude the key
    std::map< char, int > nodes = nextNodes;
    nodes.erase( node.first );

    minDist = std::min( minDist, add_next_nodes_2( newNode, nodes, copyField ) );

    head->childs.emplace_back( std::move( newNode ) );
  }

  return minDist;
}

int Vault::run_robots( const t_field & field, const std::vector< char > & robots, const std::pair< std::string, int > & path )
{
  //std::cout << "New Path: " << path.first << " cost : " << path.second << "\n";

  std::string cacheKey;
  auto keys = get_all_keys( field );

  for ( const auto & _robot : robots )
    cacheKey += _robot;

  // Make cache key
  for ( const auto & node : keys )
    cacheKey += node.first;

  if ( cache.count( cacheKey ) != 0 )
    return path.second + cache[ cacheKey ];

  int minDist = std::numeric_limits< int >::max();

  bool isNoWay = true;

  //std::cout << "Field: \n";
  //for ( int y = 0; y < field.size(); ++y )
  //{
  //  for ( int x = 0; x < field[ y ].size(); ++x )
  //    std::cout << field[ y ][ x ];
  //  std::cout << "\n";
  //}
  //std::cout << "\n";

  for ( int robotNum = 0; robotNum < robots.size(); ++robotNum )
  {
    bool hasDoors;

    // Get available keys
    std::map< char, int > availableKeys = get_distance_to_other_keys( keysPosition[ robots[ robotNum ] ], field, hasDoors );

    if ( availableKeys.size() == 0 )
      continue;

    isNoWay = false;

    // For each key calc a minDist
    for ( const auto _key : availableKeys )
    {
      // Make a copy from the field
      t_field copyField = field;
      std::vector< char > copyRobots = robots;
      std::pair< std::string, int > copyPath = path;
      
      copyRobots[ robotNum ] = _key.first;
      
      // Pick up the key
      t_coord pos = keysPosition[ _key.first ];
      copyField[ pos.y ][ pos.x ] = '.';
      open_doors( _key.first, copyField );

      // Add to path
      copyPath.first += _key.first;
      copyPath.second += keysDistance[ robots[ robotNum ] ][ _key.first ];

      minDist = std::min( minDist, run_robots( copyField, copyRobots, copyPath ) );
    }
  }

  if ( isNoWay )
  {
    //std::cout << "Found Path: " << path.first << " cost : " << path.second << "\n";
    return path.second;
  }

  //std::cout << "Add to cahce key: " << cacheKey << " cost : " << minDist - path.second << "\n";
  cache[ cacheKey ] = minDist - path.second;

  return minDist;
}


void Vault::get_next_nodes( const t_coord & currentPoint, std::queue< t_coord >& que, t_color & color, const t_field & field, t_distance & dist )
{
  std::set< t_coord, decltype( compare_coords ) > neighborNodes( compare_coords );

  // Get neighbors nodes
  if ( currentPoint.x  + 1 < color[ 0 ].size() )
    neighborNodes.emplace( currentPoint.x + 1, currentPoint.y );
  if ( currentPoint.x > 0 )
    neighborNodes.emplace( currentPoint.x - 1, currentPoint.y );
  if ( currentPoint.y + 1 < color.size() )
    neighborNodes.emplace( currentPoint.x, currentPoint.y + 1 );
  if ( currentPoint.y > 0 )
    neighborNodes.emplace( currentPoint.x, currentPoint.y - 1 );

  // Add nodes to queue
  for ( const auto & _node : neighborNodes )
  {
    if ( color[ _node.y ][ _node.x ] == WHITE )
      continue;

    if (   field[ _node.y ][ _node.x ] == '.' 
        || ( field[ _node.y ][ _node.x ] >= 'a' && field[ _node.y ][ _node.x ] <= 'z' ) 
        || ( field[ _node.y ][ _node.x ] >= 'A' && field[ _node.y ][ _node.x ] <= 'Z' )
        || ( field[ _node.y ][ _node.x ] >= '1' && field[ _node.y ][ _node.x ] <= '4' )
        || field[ _node.y ][ _node.x ] == '@' )
    {
      que.push( _node );
      dist[ _node ] = dist[ currentPoint ] + 1;
      color[ _node.y ][ _node.x ] = WHITE;
    }
  }
}

void Vault::open_doors( char key, t_field & field )
{
  char door = std::toupper( key );

  for ( int y = 0; y < field.size(); ++y )
    for ( int x = 0; x < field[ y ].size(); ++x )
      if ( field[ y ][ x ] == door )
        field[ y ][ x ] = '.';
}

t_coord Vault::get_start_point( const t_field & field )
{
  for ( int y = 0; y < field.size(); ++y )
  {
    for ( int x = 0; x < field[ y ].size(); ++x )
    {
      if ( field[ y ][ x ] == '@' )
      {
        // field[ y ][ x ] = '.';
        return{ x, y };
      }
    }
  }
  
  throw "Start point not found!";
}

void Vault::print_field( const t_field & field )
{
  for ( int y = 0; y < field.size(); ++y )
  {
    for ( int x = 0; x < field[ y ].size(); ++x )
    {
      std::cout << field[ y ][ x ];
    }
    std::cout << "\n";
  }

  std::cout << "\n";
}

void Vault::fill_keys_distance( const t_field & field )
{
  // Initialize the array with keys distance
  for ( int i = 0; i < COUNT_LETTERS; ++i )
    for ( int j = 0; j < COUNT_LETTERS; ++j )
      keysDistance[ i ][ j ] = -1;

  // Copy the field
  t_field copyField = field;

  // Find positions for all keys
  keysPosition = get_all_keys( copyField );

  // Remove all doors
  remove_all_doors( copyField );

  // Calculate distence for each key
  for ( const auto & _key : keysPosition )
  {
    bool hasDoors;

    // Get distance from the key to all other keys
    std::map< char, int > dist = get_distance_to_other_keys( _key.second, copyField, hasDoors );

    // Update distance array
    for ( const auto _dist : dist )
    {
      keysDistance[ _key.first  ][ _dist.first ] = _dist.second;
      keysDistance[ _dist.first ][ _key.first  ] = _dist.second;
    }
  }

  for ( char i = '1'; i <= '4'; ++i )
  {
    keysDistance[ i ][ '@' ] = 0;
    keysDistance[ '@' ][ i ] = 0;
  }

  //// print array
  //for ( int i = 0; i < COUNT_LETTERS; ++i )
  //{
  //  for ( int j = 0; j < COUNT_LETTERS; ++j )
  //    std::cout << keysDistance[ i ][ j ] << " ";
  //  std::cout << "\n";
  //}
}

void Vault::remove_all_doors( t_field & field )
{
  for ( int y = 0; y < field.size(); ++y )
    for ( int x = 0; x < field[ y ].size(); ++x )
      if ( field[ y ][ x ] >= 'A' && field[ y ][ x ] <= 'Z' )
        field[ y ][ x ] = '.';
}

std::map< char, t_coord > Vault::get_all_keys( const t_field & field )
{
  std::map< char, t_coord > res;

  for ( int y = 0; y < field.size(); ++y )
  {
    for ( int x = 0; x < field[ y ].size(); ++x )
    {
      // A key
      if ( field[ y ][ x ] >= 'a' && field[ y ][ x ] <= 'z' )
        res.emplace( field[ y ][ x ], t_coord( x, y ) );

      // A Door
      if ( field[ y ][ x ] >= 'A' && field[ y ][ x ] <= 'Z' )
        keysWithDoor.insert( std::tolower( field[ y ][ x ] ) );

      // The start point
      if ( field[ y ][ x ] == '@' || ( field[ y ][ x ] >= '1' && field[ y ][ x ] <= '4' ) )
        res.emplace( field[ y ][ x ], t_coord( x, y ) );
    }
  }
  return res;
}

bool Vault::is_key_in_path( char key, const std::string & path )
{
  return std::find( path.begin(), path.end(), key ) != path.end();
}



