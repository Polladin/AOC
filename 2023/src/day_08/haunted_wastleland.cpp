
#include "haunted_wastleland.h"

#include "common/file_reader.h"
#include "common/common.h"

#include <memory>
#include <regex>
#include <map>

struct Node
{
    std::string left;
    std::string right;
};

using Nodes = std::unordered_map< std::string, Node >;

struct Field
{
    Nodes nodes;
    std::string path;
};


Field prepare_input( const std::string & filename )
{
    // Read the file
    std::vector< std::string > sInput = FileReader::read_file( filename );

    Field result;

    result.path = sInput[ 0 ];

    for ( std::size_t lineIdx = 2; lineIdx < sInput.size() - 1; ++lineIdx )
    {
        std::regex word_regex( R"((\w+) = \((\w+), (\w+)\))" );
        std::smatch _match;

        std::regex_match( sInput[ lineIdx ], _match, word_regex );

        if ( _match.size() != 4 )
        {
          throw std::runtime_error( std::string( "Input is wrong: " ) + sInput[ lineIdx ] );
        }

        std::string nodeFrom = _match[ 1 ];
        std::string left = _match[ 2 ];
        std::string right = _match[ 3 ];

        result.nodes[ nodeFrom ] = Node{ left, right };
    }

    return result;
}

long long HauntedWastleland::task_1( const std::string & filename )
{
    Field field = prepare_input( filename );

    int steps { 0 };
    std::string currentNode { "AAA" };

    auto isLeftStep = [&]()
    {
        return field.path[ steps % field.path.size() ] == 'L';
    };

    while( currentNode != "ZZZ" )
    {
        currentNode = isLeftStep() ? field.nodes[ currentNode ].left
                                   : field.nodes[ currentNode ].right;
        ++steps;
    }

    return steps;
}

std::vector< std::string > get_starting_nodes(const Nodes & nodes)
{
    std::vector< std::string > result;

    for ( const auto & _node : nodes )
    {
        if ( _node.first.back() == 'A' )
        {
            result.push_back( _node.first );
        }
    }

    return result;
}

bool is_all_on_z(const std::vector< std::string > & nodes )
{
    return std::all_of( nodes.begin(), nodes.end(),
                        []( const std::string & node)
                        {
                            return node.back() == 'Z';
                        });
}

struct PathInfo
{
    long long offset;
    long long diff;
};

bool isAll( long long steps, const std::vector< PathInfo > & pathInfos)
{
    for( std::size_t idx = 0; idx < pathInfos.size(); ++idx )
    {
        if ( ( steps - pathInfos[ idx ].offset ) % pathInfos[ idx ].diff != 0 )
        {
            return false;
        }
    }

    return true;
}

long long HauntedWastleland::task_2( const std::string & filename )
{
    Field field = prepare_input( filename );

    std::vector< std::string > currentNodes = get_starting_nodes( field.nodes );

    auto isLeftStep = [&]( long long steps )
    {
        return field.path[ steps % field.path.size() ] == 'L';
    };

    std::vector< PathInfo > pathInfos;

    for( std::size_t pathIdx = 0; pathIdx < currentNodes.size(); ++pathIdx )
    {
        std::string  curNode = currentNodes[ pathIdx ];

        std::vector< std::size_t > wins;
        long long steps { 0 };

        while( wins.size() < 3 )
        {
            for( std::size_t idx = 0; idx < currentNodes.size(); ++idx )
            {
                curNode = isLeftStep( steps ) ? field.nodes[ curNode ].left
                                              : field.nodes[ curNode ].right;

                ++steps;

                if (curNode.back() == 'Z')
                {
                    wins.push_back( steps );
                }
            }
        }

        pathInfos.emplace_back( wins[ 0 ], wins[ 1 ] - wins[ 0 ] );

        std::cout << "Id: " << pathIdx << " steps: " << wins[ 0 ] << ", " << wins[ 1 ] << ", " << wins[ 2 ]
                  << " Diff: " << wins[ 1 ] - wins[ 0 ] << ", " << wins[ 2 ] - wins[ 1 ]
                << " Win0: " << wins[ 0 ] << " Win1: " << wins[ 1 ] <<  std::endl;
    }

    std::size_t maxDiff { 0 };

    for( std::size_t idx = 1; idx < pathInfos.size(); ++idx )
    {
        if ( pathInfos[ idx ].diff > pathInfos[ maxDiff ].diff )
        {
            maxDiff = idx;
        }
    }

    for ( long long steps = pathInfos[ maxDiff ].offset; true; steps += pathInfos[ maxDiff ].offset )
    {
        if ( isAll( steps, pathInfos ) )
        {
            std::cout << "WIN: " << steps << std::endl;
            break;
        }
    }

    return 0;
}
