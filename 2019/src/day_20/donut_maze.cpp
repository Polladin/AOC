#include "donut_maze.h"

#include <ctype.h>
#include <queue>
#include <limits>

#include "common/file_reader.h"

static const int BLACK = 0;
static const int WHITE = 1;


int DonutMaze::run_part_1( const std::string & fileName )
{
  t_field field = prepare_input( fileName );

  find_all_teleports( field );

  for ( const auto & _teleport : m_teleports )
    std::cout << "Tel : " << _teleport.first << " :: " << _teleport.second.first.x << " " << _teleport.second.first.y << " lvl:" << _teleport.second.second << "\n";

  for ( const auto & _teleport : m_teleportsCoords )
    std::cout << "Tel Coords : " << _teleport.second << " :: " << _teleport.first.x << " " << _teleport.first.y << "\n";


  BFS bfs( field, m_teleports, m_teleportsCoords);

  auto distance = bfs.bfs( m_teleports.find( "AA" )->second.first );

  t_coord zzCoord = m_teleports.find( "ZZ" )->second.first;

  std::cout << "Dist to ZZ : " << distance[ zzCoord.y ][ zzCoord.x ] << "\n";

  return 0;
}

DonutMaze::t_field DonutMaze::prepare_input( const std::string & fileName )
{
  return FileReader::read_file( fileName );
}

void DonutMaze::find_all_teleports( const t_field & field )
{  
  // Horizontal teleports
  for ( int y = 0; y < field.size(); ++y )
  {
    // Initialize previouse char
    char pChar = ' ';

    for ( int x = 0; x < field[ y ].size() - 1; ++x )
    {
      if (   !isalpha( field[ y ][ x     ] )
          || !isalpha( field[ y ][ x + 1 ] ) )
      {
        pChar = field[ y ][ x ];
        continue;
      }

      // Get coordinate
      const t_coord portalCoords =  pChar == '.' ? t_coord( x - 1, y ) 
                                                 : t_coord( x + 2, y );

      // Get portal name
      const std::string portalName = std::string( "" ) + field[ y ][ x ] + field[ y ][ x + 1 ];

      const int level = ( x == 0 || x == field[ y ].size() - 2 ) ? 1 : -1;

      // Add new teleport
      m_teleports.emplace( portalName, std::make_pair( portalCoords, level ) );
      m_teleportsCoords.emplace( portalCoords, portalName );

      // Update previuse char
      pChar = field[ y ][ x ];
    }
  }

  // Vertical teleports
  for ( int x = 0; x < field[ 0 ].size(); ++x )
  {
    // Initialize previouse char
    char pChar = ' ';

    for ( int y = 0; y < field.size() - 1; ++y )
    {
      if ( !isalpha( field[ y     ][ x ] )
        || !isalpha( field[ y + 1 ][ x ] ) )
      {
        pChar = field[ y ][ x ];
        continue;
      }

      // Get coordinate
      const t_coord portalCoords = pChar == '.' ? t_coord( x , y - 1 )
                                                : t_coord( x , y + 2 );

      // Get portal name
      const std::string portalName = std::string( "" ) + field[ y ][ x ] + field[ y + 1 ][ x ];

      // const int level = pChar == '.' ? 1 : -1;
      const int level = ( y == 0 || y == field.size() - 2 ) ? 1 : -1;

      // Add new teleport
      m_teleports.emplace( portalName, std::make_pair( portalCoords, level ) );
      m_teleportsCoords.emplace( portalCoords, portalName );

      // Update previuse char
      pChar = field[ y ][ x ];
    }
  }
}


std::vector< std::vector< int > > DonutMaze::BFS::bfs( const t_coord startPoint )
{
  // Color
  m_color = std::vector< std::vector< std::vector< int > > >(  2 * m_teleports.size()
                                                             , std::vector< std::vector< int > >(  m_field.size()
                                                                                                 , std::vector< int >( m_field[ 0 ].size(), BLACK ) ) );

  // Distance
  m_distance = std::vector< std::vector< std::vector< int > > >(  2 * m_teleports.size()
                                                                , std::vector< std::vector< int > >(  m_field.size()
                                                                                                     , std::vector< int >( m_field[ 0 ].size(), -1 ) ) );
  m_path = std::vector< std::vector< std::vector< std::string > > >(  2 * m_teleports.size()
                                                                    , std::vector< std::vector< std::string > >(  m_field.size()
                                                                                                                , std::vector< std::string >( m_field[ 0 ].size(), "" ) ) );

  // Initialize queue
  std::queue< std::pair< t_coord, int > > que;
  que.emplace( startPoint, m_teleports.size() );

  // Mark start pint as visited
  m_color[ 0 ][ startPoint.y ][ startPoint.x ] = WHITE;

  // Initialize distance;
  m_distance[ 0 ][ startPoint.y ][ startPoint.x ] = 0;

  while ( !que.empty() )
  {
    // Take next point
    t_coord currentPoint = que.front().first;
    int level = que.front().second;
    que.pop();

    // Get neighbors
    std::vector< std::pair< t_coord, int > > neighbors = get_neighbours( currentPoint, level );

    // Add new nodes into queue
    for ( const auto & _place : neighbors )
    {
      que.emplace( _place.first, _place.second );
      m_distance[ _place.second ][ _place.first.y ][ _place.first.x ] = m_distance[ level ][ currentPoint.y ][ currentPoint.x ] + 1;
    }
  }

  std::cout << "Path : " << m_path[ m_teleports.size() ][ m_teleports.find("ZZ")->second.first.y ][ m_teleports.find( "ZZ" )->second.first.x ] << "\n";
  std::cout << "Len(): " << m_path[ m_teleports.size() ][ m_teleports.find( "ZZ" )->second.first.y ][ m_teleports.find( "ZZ" )->second.first.x ].size() / 3 << "\n";
  return m_distance[ m_teleports.size() ];
}

std::vector< std::pair< t_coord, int > > DonutMaze::BFS::get_neighbours( const t_coord pos, int level )
{
  std::vector< std::pair< t_coord, int > > res;

  // RIGHT
  if (   m_color[ level ][ pos.y ][ pos.x + 1 ] == BLACK
      && m_field[ pos.y ][ pos.x + 1 ] == '.' )
  {
    res.emplace_back( t_coord( pos.x + 1, pos.y ), level );
    m_color[ level ][ pos.y ][ pos.x + 1 ] = WHITE;
    m_path[ level ][ pos.y ][ pos.x + 1 ] = m_path[ level ][ pos.y ][ pos.x ];
  }

  // LEFT
  if (   m_color[ level ][ pos.y ][ pos.x - 1 ] == BLACK
      && m_field[ pos.y ][ pos.x - 1 ] == '.' )
  {
    res.emplace_back( t_coord( pos.x - 1, pos.y ), level );
    m_color[ level ][ pos.y ][ pos.x - 1 ] = WHITE;
    m_path[ level ][ pos.y ][ pos.x - 1 ] = m_path[ level ][ pos.y ][ pos.x ];
  }

  // DOWN
  if (   m_color[ level ][ pos.y + 1 ][ pos.x ] == BLACK
      && m_field[ pos.y + 1 ][ pos.x ] == '.' )
  {
    res.emplace_back( t_coord( pos.x, pos.y + 1 ), level );
    m_color[ level ][ pos.y + 1 ][ pos.x ] = WHITE;
    m_path [ level ][ pos.y + 1 ][ pos.x ] = m_path[ level ][ pos.y ][ pos.x ];
  }

  // UP
  if (   m_color[ level ][ pos.y - 1 ][ pos.x ] == BLACK
      && m_field[ pos.y - 1 ][ pos.x ] == '.' )
  {
    res.emplace_back( t_coord( pos.x, pos.y - 1 ), level );
    m_color[ level ][ pos.y - 1 ][ pos.x ] = WHITE;
    m_path[ level ][ pos.y - 1][ pos.x ] = m_path[ level ][ pos.y ][ pos.x ];
  }

  // Teleports
  if (   isalpha( m_field[ pos.y + 1 ][ pos.x     ] ) || isalpha( m_field[ pos.y - 1 ][ pos.x      ] ) 
      || isalpha( m_field[ pos.y     ][ pos.x + 1 ] ) || isalpha( m_field[ pos.y     ][ pos.x  - 1 ] ) )
  {
    // Get all available teleports from this place
    auto pit = m_teleportsCoords.equal_range( pos );

    for ( auto it = pit.first; it != pit.second; ++it )
    {
      // Get all available places from the teleport
      auto pitTeleports = m_teleports.equal_range( it->second );

      for ( auto itTeleport = pitTeleports.first; itTeleport != pitTeleports.second; ++itTeleport )
      {
        if ( itTeleport->first == "ZZ" || itTeleport->first == "AA" )
          continue;

        if ( pos.x == itTeleport->second.first.x && pos.y == itTeleport->second.first.y )
          continue;

        int nextLevel = level - itTeleport->second.second;

        if ( nextLevel > m_teleports.size() )
          continue;

        std::string name = itTeleport->first;
        t_coord toCoords = itTeleport->second.first;

        if ( m_color[ nextLevel ][ itTeleport->second.first.y ][ itTeleport->second.first.x ] == BLACK )
        {
          res.emplace_back( t_coord( itTeleport->second.first.x, itTeleport->second.first.y ), nextLevel );
          m_color[ nextLevel ][ itTeleport->second.first.y ][ itTeleport->second.first.x ] = WHITE;
          m_path[ nextLevel ][ itTeleport->second.first.y ][ itTeleport->second.first.x ] = m_path[ level ][ pos.y ][ pos.x ] + "|" + itTeleport->first;
          //if ( m_path[ nextLevel ][ itTeleport->second.first.y ][ itTeleport->second.first.x ].substr( 0, 39 ) == "|XF|CK|ZH|WB|IC|RF|NM|LP|FD|XQ|WB|ZH|CK" )
          
          std::string endStr( "|OA|CJ|RE|IC|RF|NM|LP|FD|XQ|WB|ZH|CK|XF|OA|CJ|RE|IC|RF|NM|LP" );

          for ( int i = 3; i < endStr.size(); i += 3 )
            if( m_path[ nextLevel ][ itTeleport->second.first.y ][ itTeleport->second.first.x ] == endStr.substr( 0, i ) )
            std::cout << "Path : " << m_path[ nextLevel ][ itTeleport->second.first.y ][ itTeleport->second.first.x ] 
            << " d: " << m_distance[ level ][ pos.y ][ pos.x ] + 1 
            << " l: " << nextLevel << "\n";
        }
      }
    }
  }

  return res;
}
