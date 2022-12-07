#include "no_space_left_on_device.h"

#include <vector>
#include <memory>

#include "common/file_reader.h"
#include "common/common.h"


struct Folder
{
    Folder( const std::string & i_name )
        : name{ i_name }
    {}

    Folder( const std::string & i_name, const std::shared_ptr< Folder > & ownerFolder )
        : name{ i_name }
        , prevFolder{ ownerFolder }
    {}

    std::string name;
    std::vector< std::pair< std::string, long long > > files;

    std::weak_ptr< Folder > prevFolder;
    std::vector< std::shared_ptr< Folder > > folders;
};

void add_folder( const std::string & folderName, std::shared_ptr< Folder > & currentFolder )
{
    currentFolder->folders.push_back( std::make_shared< Folder >( folderName, currentFolder ) );
}

void cd( const std::string & cmd, std::shared_ptr< Folder > & currentFolder, const std::shared_ptr< Folder > & root )
{
    const std::string nextFolderName = cmd.substr( 5 );

    if ( nextFolderName == "/" )
    {
        currentFolder = root;
        return;
    }

    if ( nextFolderName.starts_with("..") )
    {
        currentFolder = currentFolder->prevFolder.lock();
        return;
    }

    for ( const auto & _folder : currentFolder->folders )
    {
        if ( _folder->name == nextFolderName )
        {
            currentFolder = _folder;
            return;
        }
    }

    throw "Unknow folder name";
}

std::size_t ls( std::size_t idx, const std::vector< std::string > & sInput, std::shared_ptr< Folder > & currentFolder )
{
    for( ; idx < sInput.size() && sInput[ idx ][ 0 ] != '$'; ++idx )
    {
        const std::string & line = sInput[ idx ];

        if ( line.starts_with( "dir " ) )
        {
            add_folder( line.substr( 4 ), currentFolder );
            continue;
        }

        // Add a file
        const auto splittedLine = common::split_line( line, ' ' );

        std::string fileName = splittedLine[ 1 ];

        currentFolder->files.emplace_back( splittedLine[ 1 ], std::stoll( splittedLine[ 0 ] ) );
    }

    return idx - 1;
}

std::shared_ptr< Folder > prepare_input( const std::string & filename )
{
    std::vector< std::string > sInput = FileReader::read_file( filename );

    std::shared_ptr< Folder > root = std::make_shared< Folder >( "/" );
    std::shared_ptr< Folder > currentFolder { root };

    for ( std::size_t idx = 0; idx < sInput.size(); ++idx )
    {
        if ( sInput[ idx ].starts_with( "$ cd" ) )
        {
            cd( sInput[ idx ], currentFolder, root );
        }
        else if ( sInput[ idx ].starts_with("$ ls") )
        {
            idx = ls( idx + 1, sInput, currentFolder );
        }
        else
        {
            throw "Wrong command!";
        }
    }

    return root;
}

long long get_folder_size( const std::shared_ptr< Folder > & root )
{
    long long res { 0 };

    for ( const auto & _file : root->files )
        res += _file.second;

    for ( const auto & _folder : root->folders )
        res += get_folder_size( _folder );

    return res;
}

long long get_folders_size_with_limit( const std::shared_ptr< Folder > & root, long long limit )
{
    long long res = 0;

    for ( const auto & _folder : root->folders )
    {
       const long long folderSize = get_folder_size( _folder );

       if ( folderSize <= limit )
           res += folderSize;

       res += get_folders_size_with_limit( _folder, limit );
    }

    return res;
}

void get_folders_list( const std::shared_ptr< Folder > & root, std::vector< long long > & folderSizes )
{
    folderSizes.push_back( get_folder_size( root ) );

    for ( const auto & _folder : root->folders )
        get_folders_list( _folder, folderSizes );
}

long long NoSpaceLeftOnDevice::task_1( const std::string & filename )
{
    std::shared_ptr< Folder > root = prepare_input( filename );

    return get_folders_size_with_limit( root, 100000 );
}

long long NoSpaceLeftOnDevice::task_2( const std::string & filename )
{
    const long long totalSpace         = 70000000ll;
    const long long atLeastUnusedSpace = 30000000ll;

    std::shared_ptr< Folder > root = prepare_input( filename );

    const long long freeSpace = totalSpace - get_folder_size( root );
    const long long needToFree = atLeastUnusedSpace - freeSpace;

    std::vector< long long > foldersList;
    get_folders_list( root, foldersList );

    std::sort( foldersList.begin(), foldersList.end() );

    auto it = std::lower_bound( foldersList.begin(), foldersList.end(), needToFree );

    return *it;
}
