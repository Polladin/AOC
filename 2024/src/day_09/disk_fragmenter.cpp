
#include "disk_fragmenter.h"

#include <vector>
#include <list>
#include <assert.h>
#include <algorithm>

#include "common/file_reader.h"

namespace
{
struct Node
{
    int id;
    int length;
};

using FileSystem = std::list< Node >;

void add_to_file_system( const int fileId, const int length, FileSystem & filesystem )
{
    if ( length != 0 )
        filesystem.push_back( Node{ fileId, length } );
}

FileSystem prepare_input( const std::string & filename )
{
    std::vector< std::string > field = FileReader::read_file( filename );
    assert( field.size() == 1 && "Wrong input data" );

    FileSystem result;
    bool isFreeSpace { false };
    int fileID { 0 };

    for ( const char symbol_ : field[ 0 ] )
    {
        if ( isFreeSpace )
        {
            add_to_file_system( /*fileId*/ -1, symbol_ - '0', result );
            isFreeSpace = false;
        }
        else
        {
            add_to_file_system( fileID, symbol_ - '0', result );
            isFreeSpace = true;
            ++fileID;
        }
    }

    while ( result.size() > 0 && result.back().id == -1 )
    {
        result.pop_back();
    }

    return result;
}

FileSystem::iterator get_next_free_node( FileSystem::iterator fileSystemIt, const FileSystem::iterator fileSystemEnd )
{
    while ( ++fileSystemIt != fileSystemEnd && fileSystemIt->id != - 1 ) {}

    return fileSystemIt;
}

void add_file_to_node( Node & node, FileSystem::iterator freeFileSystemIt, FileSystem & filesystem )
{
    freeFileSystemIt->id = node.id;

    if ( node.length >= freeFileSystemIt->length )
    {
        node.length -= freeFileSystemIt->length;
    }
    else
    {
        filesystem.insert( std::next( freeFileSystemIt ),
                           Node{ -1, freeFileSystemIt->length - node.length } );

        freeFileSystemIt->length = node.length;
        node.length = 0;
    }
}

void insert_into_free_space( Node node, FileSystem & filesystem )
{
    auto fileSystemNodeIt = filesystem.begin();

    while ( node.length > 0 )
    {
        fileSystemNodeIt = get_next_free_node( fileSystemNodeIt, filesystem.end() );

        if ( fileSystemNodeIt == filesystem.end() )
        {
            break;
        }

        add_file_to_node( node, fileSystemNodeIt, filesystem );
    }

    if ( node.length > 0 )
    {
        filesystem.insert( filesystem.end(), node );
    }
}

bool has_any_free_node( FileSystem & filesystem )
{
    return get_next_free_node( filesystem.begin(), filesystem.end() ) != filesystem.end();
}

Node extract_last_node( FileSystem & filesystem )
{
    Node lastNode = filesystem.back();
    filesystem.pop_back();

    while ( filesystem.size() > 0 && filesystem.back().id == -1 )
    {
        filesystem.pop_back();
    }

    return lastNode;
}

void fragment( FileSystem & filesystem )
{
    while ( has_any_free_node( filesystem ) )
    {
        // Extract last node
        Node lastNode = extract_last_node( filesystem );

        insert_into_free_space( lastNode, filesystem );
    }
}

long long get_result( const FileSystem & filesystem )
{
    long long result { 0 };
    long long idx { 0 };

    for ( const auto & node_ : filesystem )
    {
        for ( long long nodeIdx = 0; nodeIdx < node_.length; ++nodeIdx )
        {
            if ( node_.id != -1 )
            {
                result += node_.id * idx;
            }
            ++idx;
        }
    }

    return result;
}

// --------------- STEP 2 ----------------------------

FileSystem::iterator get_node_iter( int nodeId, FileSystem & filesystem )
{
    auto it = std::find_if( filesystem.begin(), filesystem.end(),
                         [ nodeId ]( const Node & node ){ return node.id == nodeId; } );

    assert( it != filesystem.end() && "Can't find elem with id" );

    return it;
}

FileSystem::iterator find_new_place( FileSystem::iterator begin, FileSystem::iterator nodeToMoveIt )
{
    return std::find_if( begin, nodeToMoveIt,
                         [ nodeToMoveIt ]( const Node & node ){ return node.id == -1 && node.length >= nodeToMoveIt->length; } );
}

void add_file_to_node_2( FileSystem::iterator node, FileSystem::iterator freeFileSystemIt, FileSystem & filesystem )
{
    freeFileSystemIt->id = node->id;

    if ( node->length < freeFileSystemIt->length )
    {
        filesystem.insert( std::next( freeFileSystemIt ),
                           Node{ -1, freeFileSystemIt->length - node->length } );

        freeFileSystemIt->length = node->length;
    }

    // Clear node
    node->id = -1;
}

void fragment_2( FileSystem & filesystem )
{
    for ( int nodeId = filesystem.back().id; nodeId != 0; --nodeId )
    {
        auto nodeIter = get_node_iter( nodeId, filesystem );
        auto freeSpaceIt = find_new_place( filesystem.begin(), nodeIter );

        if ( freeSpaceIt != nodeIter )
        {
            add_file_to_node_2( nodeIter, freeSpaceIt, filesystem );
        }
    }
}

}// namespace

long long DiskFragmenter::task_1( const std::string & filename )
{
    FileSystem filesystem = prepare_input( filename );

    fragment( filesystem );

    return get_result( filesystem );
}

long long DiskFragmenter::task_2( const std::string & filename )
{
    FileSystem filesystem = prepare_input( filename );

    fragment_2( filesystem );

    return get_result( filesystem );
}
