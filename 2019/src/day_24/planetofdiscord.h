#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <set>
#include <iostream>

// -------------------------------- Map ----------------------------------

namespace {

    using t_field = std::vector< std::string >;

    struct t_point
    {
        std::size_t row { 0 }, col { 0 };
    };

    bool operator == ( const t_point & lhs, const t_point & rhs )
    {
        return lhs.row == rhs.row && lhs.col == rhs.col;
    }
}


class Map : public std::enable_shared_from_this< Map >
{
private:

    static const std::size_t BOTTOM_ROW_INSIDE  = 1;
    static const std::size_t BOTTOM_ROW_OUTSIDE = 4;

    static const std::size_t TOP_ROW_INSIDE  = 3;
    static const std::size_t TOP_ROW_OUTSIDE = 0;

    static const std::size_t LEFT_COL_INSIDE  = 3;
    static const std::size_t LEFT_COL_OUTSIDE = 0;

    static const std::size_t RIGHT_COL_INSIDE  = 1;
    static const std::size_t RIGHT_COL_OUTSIDE = 4;

    enum class t_direction
    {
          TOP
        , BOTTOM
        , RIGHT
        , LEFT
    };

    std::set< t_direction > all_directions = { t_direction::TOP, t_direction::BOTTOM, t_direction::LEFT, t_direction::RIGHT };

    std::map< t_direction, t_direction > inverse_direction = {   { t_direction::TOP   , t_direction::BOTTOM }
                                                               , { t_direction::BOTTOM, t_direction::TOP    }
                                                               , { t_direction::LEFT  , t_direction::RIGHT  }
                                                               , { t_direction::RIGHT , t_direction::LEFT   } };

public:

    Map( std::size_t rows, std::size_t cols )
        : m_field( rows, std::string( cols, '.' ) )
    {}

    Map( const t_field & field )
        : m_field { field }
    {}

    virtual void run_step()      = 0;
    virtual void end_step()      = 0;
    virtual int  calc_occupied() = 0;

    virtual void set_outside( const std::shared_ptr< Map > & outside ) = 0;
    virtual void set_inside ( const std::shared_ptr< Map > & inside  ) = 0;
    virtual void print_all() = 0;

    virtual std::shared_ptr< Map > get_outside() = 0;
    virtual std::shared_ptr< Map > get_inside()  = 0;

    bool is_occupied( const t_point & point ) const;
    int get_occupied( t_direction direction ) const;

    bool is_inside_neighbours ( t_direction direction, const t_point & point );
    bool is_outside_neighbours( t_direction direction, const t_point & point );

    int get_neighbours( const t_point & point );
    int get_neighbours( const t_point & point, t_direction direction );

    int get_outside_neighbours( t_direction direction );
    int get_inside_neighbours ( t_direction direction );
    int get_self_neighbours   ( t_direction direction, const t_point & point ) const;

    std::size_t get_rows() const { return m_field        .size(); }
    std::size_t get_cols() const { return m_field.front().size(); }

    t_point get_middle() const { return t_point{  .row = get_rows() / 2
                                                , .col = get_cols() / 2 }; }

protected:

    int get_occupied();
    void print();

    void calculate();
    void swap_fields() { std::swap( m_field, m_nextField ); }

private:

    bool is_need_to_create_outside() const;
    bool is_need_to_create_inside () const;

    std::shared_ptr< Map > create_outside();
    std::shared_ptr< Map > create_inside ();

    t_point get_point_for( const t_point & point, t_direction direction );

    t_field get_empty_field() const { return t_field( get_rows(), std::string( get_cols(), '.' ) ); }

    std::vector< t_point > get_all_points() const;

private:

    t_field m_field;
    t_field m_nextField;
};


// -------------------------------- Map Outside ----------------------------------

class MapOutside : public Map
{
public:

    MapOutside( std::size_t rows, std::size_t cols  ) : Map( rows, cols ) {}

    virtual void set_outside ( const std::shared_ptr< Map > & outside ) override { m_outside = outside; }
    virtual void set_inside  ( const std::shared_ptr< Map > & inside  ) override { m_inside  = inside;  }

    virtual std::shared_ptr< Map > get_outside() override { return m_outside;       }
    virtual std::shared_ptr< Map > get_inside()  override { return m_inside.lock(); }

    virtual void run_step()    override { calculate()  ; if ( m_outside ) m_outside->run_step()  ; }
    virtual void end_step()    override { swap_fields(); if ( m_outside ) m_outside->end_step(); }

    virtual int  calc_occupied() override { return get_occupied() + ( m_outside ? m_outside->calc_occupied() : 0 ); }

    virtual void print_all() override { print(); if ( m_outside ) m_outside->print_all(); };

private:
    std::shared_ptr< Map > m_outside;
    std::weak_ptr  < Map > m_inside;
};


// -------------------------------- Map Inside ----------------------------------

class MapInside : public Map
{
public:

    MapInside( std::size_t rows, std::size_t cols  ) : Map( rows, cols ) {}

    virtual void set_outside( const std::shared_ptr< Map > & outside ) override { m_outside = outside; }
    virtual void set_inside ( const std::shared_ptr< Map > & inside  ) override { m_inside  = inside;  }

    virtual std::shared_ptr< Map > get_outside() override { return m_outside.lock(); }
    virtual std::shared_ptr< Map > get_inside()  override { return m_inside;         }

    virtual void run_step() override { calculate()  ; if ( m_inside ) m_inside->run_step()  ; }
    virtual void end_step() override { swap_fields(); if ( m_inside ) m_inside->end_step(); }

    virtual int  calc_occupied() override { return get_occupied() + ( m_inside ? m_inside->calc_occupied() : 0 ); }

    virtual void print_all() override { print(); if ( m_inside ) m_inside->print_all(); }

private:
    std::weak_ptr  < Map > m_outside;
    std::shared_ptr< Map > m_inside;
};


// -------------------------------- Map Middle ----------------------------------

class MapMiddle : public Map
{
public:

    MapMiddle( const t_field & field ) : Map ( field ) {}

    virtual void set_outside ( const std::shared_ptr< Map > & outside ) override { m_outside = outside; }
    virtual void set_inside  ( const std::shared_ptr< Map > & inside  ) override { m_inside  = inside;  }

    virtual std::shared_ptr< Map > get_outside() override { return m_outside; }
    virtual std::shared_ptr< Map > get_inside()  override { return m_inside;  }

    virtual void run_step() override
    {
        calculate();

        if ( m_outside ) m_outside->run_step();
        if ( m_inside  ) m_inside ->run_step();

        swap_fields();

        if ( m_outside ) m_outside->end_step();
        if ( m_inside  ) m_inside ->end_step();
    }

    virtual void end_step() override {}

    virtual int  calc_occupied() override
    {
        return get_occupied() + ( m_outside ? m_outside->calc_occupied() : 0 )
                              + ( m_inside  ? m_inside ->calc_occupied() : 0 );
    }

    virtual void print_all() override
    {
        std::cout << "-------------- PRINT ----------------------" << std::endl;
        print();

        std::cout << " --- OUTSIDE --- " << std::endl;

        if ( m_outside ) m_outside->print_all();

        std::cout << " --- INSIDE --- " << std::endl;

        if ( m_inside ) m_inside->print_all();
    }

private:
    std::shared_ptr< Map > m_outside { nullptr };
    std::shared_ptr< Map > m_inside  { nullptr };
};






// -------------------------------- Planet of Discord ----------------------------------

class PlanetofDiscord
{

public:

    long long part_1( const std::string & fileName );

    int part_2( const std::string & fileName );

};

