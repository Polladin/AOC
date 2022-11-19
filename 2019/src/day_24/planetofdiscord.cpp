#include "planetofdiscord.h"

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <ranges>

#include "common/file_reader.h"


void print_field( const t_field & field )
{
    for ( const auto & _line : field )
        std::cout << _line << "\n";

    std::cout << "\n";
}

// -------------------------------- Map ----------------------------------

void Map::print()
{
    print_field( m_field );
}

void Map::calculate()
{
    m_nextField = get_empty_field();

    for ( const t_point & point : get_all_points() )
    {
//        std::cout << "Get neighbours -> for point [" << point.row << ", " << point.col << "]" << std::endl;

        int neighbors = get_neighbours( point );

//        std::cout << "Get neighbours <- neighbours: " << neighbors << std::endl;

        // A bug dies (becoming an empty space) unless there is exactly one bug adjacent to it.
        if ( m_field[ point.row ][ point.col ] == '#' )
        {
            if( neighbors  == 1 )
                m_nextField[ point.row ][ point.col ] = '#';

            continue;
        }

        // An empty space becomes infested with a bug if exactly one or two bugs are adjacent to it
        if ( neighbors == 1 || neighbors == 2 )
            m_nextField[ point.row ][ point.col ] = '#';
    }
}

int Map::get_occupied()
{
    int occupied { 0 };

    for ( const t_point & point : get_all_points() )
        occupied += ( m_field[ point.row ][ point.col ] == '#' ? 1 : 0 );

    return occupied;
}

bool Map::is_need_to_create_outside() const
{
    int occupied_border { 0 };

    for ( auto _direction : all_directions )
        occupied_border += get_occupied( _direction );

    return occupied_border > 0;
}

bool Map::is_need_to_create_inside() const
{
    static const std::vector< t_point > points_affected_to_inside_field = { { 1, 2 }, { 2, 1 }, { 2, 3 }, { 3, 2 } };

    int occupied_border { 0 };

    for ( const auto & _point : points_affected_to_inside_field )
        occupied_border += ( is_occupied( _point ) ? 1 : 0 );

     return occupied_border > 0;
}

bool Map::is_occupied( const t_point & point ) const
{
    if ( point == get_middle() )
        throw "Wrong point";

    return ( m_field[ point.row ][ point.col ] == '#' );
}

int Map::get_occupied( t_direction direction ) const
{
    static const auto _get_left  = []( const std::string & line ){ return line.front(); };
    static const auto _get_right = []( const std::string & line ){ return line.back() ; };

    static const auto _calc_col = []( const t_field & field, auto get_func )
    {
        int res { 0 };

        for( const auto & _line : field )
            res += ( get_func( _line ) == '#' ? 1 : 0 );

        return res;
    };

    switch( direction )
    {
    case t_direction::TOP    : return std::ranges::count( m_field.front(), '#' );
    case t_direction::BOTTOM : return std::ranges::count( m_field.back() , '#' );
    case t_direction::LEFT   : return _calc_col( m_field, _get_left  );
    case t_direction::RIGHT  : return _calc_col( m_field, _get_right );
    }

    throw "Wrong Directions";
}

bool Map::is_inside_neighbours( t_direction direction, const t_point & point )
{
    switch( direction )
    {
    case t_direction::TOP    : return point.row == TOP_ROW_INSIDE    && point.col == get_cols() / 2;
    case t_direction::BOTTOM : return point.row == BOTTOM_ROW_INSIDE && point.col == get_cols() / 2;
    case t_direction::LEFT   : return point.col == LEFT_COL_INSIDE   && point.row == get_rows() / 2;
    case t_direction::RIGHT  : return point.col == RIGHT_COL_INSIDE  && point.row == get_rows() / 2;
    }

    throw "Wrong Directions";
}

bool Map::is_outside_neighbours(t_direction direction, const t_point &point)
{
    switch( direction )
    {
    case t_direction::TOP    : return point.row == TOP_ROW_OUTSIDE   ;
    case t_direction::BOTTOM : return point.row == BOTTOM_ROW_OUTSIDE;
    case t_direction::LEFT   : return point.col == LEFT_COL_OUTSIDE  ;
    case t_direction::RIGHT  : return point.col == RIGHT_COL_OUTSIDE ;
    }

    throw "Wrong Directions";
}

int Map::get_neighbours( const t_point & point )
{
    int res { 0 };

    for ( auto _direction : all_directions )
        res += get_neighbours( point, _direction );

    return res;
}

int Map::get_neighbours( const t_point & point, t_direction direction )
{
//    if ( point.row == 1 && point.col == 0 )
//        std::cout << "The point!" << std::endl;

    if ( is_outside_neighbours( direction, point ) )
        return get_outside_neighbours( direction );

    if ( is_inside_neighbours( direction, point ) )
        return get_inside_neighbours( direction );

    return get_self_neighbours( direction, point );
}

int Map::get_outside_neighbours( t_direction direction )
{
    std::shared_ptr< Map > outside = get_outside();

    if ( outside )
        return outside->is_occupied( get_point_for( get_middle(), direction ) );

    if ( is_need_to_create_outside() )
        outside = create_outside();

    return 0;
}

int Map::get_inside_neighbours( t_direction direction )
{
    std::shared_ptr< Map > inside = get_inside();

    if ( inside )
        return inside->get_occupied( inverse_direction[ direction ] );

    if ( is_need_to_create_inside() )
        inside = create_inside();

    return 0;
}

int Map::get_self_neighbours( t_direction direction, const t_point & point ) const
{
    switch( direction )
    {
    case t_direction::TOP    : return m_field[ point.row - 1 ][ point.col     ] == '#' ? 1 : 0;
    case t_direction::BOTTOM : return m_field[ point.row + 1 ][ point.col     ] == '#' ? 1 : 0;
    case t_direction::LEFT   : return m_field[ point.row     ][ point.col - 1 ] == '#' ? 1 : 0;
    case t_direction::RIGHT  : return m_field[ point.row     ][ point.col + 1 ] == '#' ? 1 : 0;
    }

    throw "Wrong Directions";
}


std::shared_ptr< Map > Map::create_outside()
{
    auto outside = std::make_shared< MapOutside >( get_rows(), get_cols() );

    set_outside( outside );
    outside->set_inside( shared_from_this() );

    return outside;
}

std::shared_ptr< Map > Map::create_inside()
{
    auto inside = std::make_shared< MapInside >( get_rows(), get_cols() );

    set_inside( inside );
    inside->set_outside( shared_from_this() );

    return inside;
}

t_point Map::get_point_for( const t_point & point, t_direction direction )
{
    t_point result = point;

    switch( direction )
    {
    case t_direction::TOP    : if ( result.row     == 0          ) throw "Wrong get point";
    case t_direction::BOTTOM : if ( result.row + 2 == get_rows() ) throw "Wrong get point";
    case t_direction::LEFT   : if ( result.col     == 0          ) throw "Wrong get point";
    case t_direction::RIGHT  : if ( result.col + 2 == get_cols() ) throw "Wrong get point";
    }

    switch( direction )
    {
    case t_direction::TOP    : --result.row; break;
    case t_direction::BOTTOM : ++result.row; break;
    case t_direction::LEFT   : --result.col; break;
    case t_direction::RIGHT  : ++result.col; break;
    }

    return result;
}

std::vector<t_point> Map::get_all_points() const
{
    std::vector< t_point > res;

    for ( std::size_t _row = 0; _row < get_rows(); ++_row )
        for ( std::size_t _col = 0; _col < get_cols(); ++_col )
            if ( t_point { .row = _row, .col = _col } != get_middle() )
                res.emplace_back( _row, _col );

    return res;
}


// -------------------------------- Planet of Discord ----------------------------------

t_field read_input( const std::string & fileName )
{
    // Read the file
    t_field sInputs = FileReader::read_file( fileName );

//    const std::size_t rowSize = sInputs.size();
    const std::size_t colSize = sInputs[ 0 ].size();

    // Insert top empty line
    sInputs.insert( sInputs.begin(), std::string( colSize, '.' ) );

    // Insert bottom empty line
    sInputs.push_back( std::string( colSize, '.' ) );

    // Insert left and right empty line
    for ( auto & _line : sInputs )
    {
        _line.insert( 0, "." );
        _line.append( 1, '.' );
    }

    return sInputs;
}

t_field get_empty_field( std::size_t row, std::size_t col )
{
    return t_field( row, std::string( col, '.' ) );
}

long long get_neighbors( const t_field & field, std::size_t row, std::size_t col )
{
    long long res = 0;

//    for ( std::size_t _row = row - 1; _row <= row + 1; ++_row )
//        for ( std::size_t _col = col - 1; _col <= col + 1; ++_col )
//            if ( !( _row == row && _col == col ) )
//                res += ( field[ _row ][ _col ] == '#' ? 1 : 0 );

    if ( field[ row - 1 ][ col     ] == '#' )
        ++res;
    if ( field[ row + 1 ][ col     ] == '#' )
        ++res;
    if ( field[ row     ][ col - 1 ] == '#' )
        ++res;
    if ( field[ row     ][ col + 1 ] == '#' )
        ++res;

    return res;
}

t_field evaluate( const t_field & field )
{
    t_field result  = get_empty_field( field.size(), field[ 0 ].size() );

    for ( std::size_t _row = 1; _row < field.size() - 1; ++_row )
    {
        for ( std::size_t _col = 1; _col < field[ 0 ].size() - 1; ++_col )
        {
            long long neighbors = get_neighbors( field, _row, _col );

            // A bug dies (becoming an empty space) unless there is exactly one bug adjacent to it.
            if ( field[ _row ][ _col ] == '#' )
            {
                if( neighbors  == 1 )
                    result[ _row ][ _col ] = '#';

                continue;
            }

            // An empty space becomes infested with a bug if exactly one or two bugs are adjacent to it
            if ( neighbors == 1 || neighbors == 2 )
                result[ _row ][ _col ] = '#';
        }
    }

    return result;
}

bool is_fields_equal( const t_field & lhs, const t_field & rhs )
{
    for ( std::size_t idx = 0; idx < lhs.size(); ++idx )
        if ( lhs[ idx ] != rhs[ idx ] )
            return false;

    return true;
}

bool is_second_appear( const std::vector< t_field > storedFields, const t_field & field )
{
    for ( const auto & _storedField : storedFields )
        if ( is_fields_equal( _storedField, field ) )
            return true;

    return false;
}


long long calc_result( const t_field & field )
{
    long long res = 0;
    long long mult = 1;

    for ( std::size_t _row = 1; _row < field.size() - 1; ++_row )
    {
        for ( std::size_t _col = 1; _col < field[ 0 ].size() - 1; ++_col )
        {
            if ( field[ _row ][ _col ] == '#' )
                res += mult;

            mult *= 2;
        }
    }

    return res;
}

long long PlanetofDiscord::part_1( const std::string & fileName )
{
    t_field field = read_input( fileName );

    std::vector< t_field > storedFields;

    while ( !is_second_appear( storedFields, field ) )
    {
//        print_field( field );

        storedFields.push_back( field );

        field = evaluate( field );
    }

    print_field( field );

    return calc_result( field );
}

int PlanetofDiscord::part_2( const std::string & fileName )
{
    t_field field = FileReader::read_file( fileName );

    auto map = std::make_shared< MapMiddle >( field );
//    map->print_all();

    for ( int idx = 0 ; idx < 200; ++idx )
    {
        map->run_step();
//        map->print_all();
    }

//    map->print_all();

    std::cout << "Result : " << map->calc_occupied() << "\n";

    return map->calc_occupied();
}


