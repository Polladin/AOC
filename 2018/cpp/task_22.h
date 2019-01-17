#pragma once

#include <vector>
#include <fstream>
#include <string>


class Task22
{
public:

    using t_position = std::pair<std::size_t, std::size_t>;
    using t_field_calc = std::vector<std::vector<long>>;
    using t_field_score = std::vector<std::vector<int>>;
    using t_field_marked = std::vector<std::vector<bool>>;

    struct NextHop
    {
        enum class TOOL_TYPES { T, G, N };

        NextHop( int i_len, const Task22::t_position & i_pos, const TOOL_TYPES i_tools, int i_switchTools, int i_movement )
            : length{ i_len }
            , pos{ i_pos }
            , tools{ i_tools }
            , switchTools{ i_switchTools }
            , movement{ i_movement }
        {}

        int length;
        Task22::t_position pos;
        TOOL_TYPES tools;

        int switchTools = 0;
        int movement = 0;
    };

    Task22( unsigned long i_depth, const t_position & i_target_pos, size_t max_x, size_t max_y );

    void fill_field( std::size_t max_x, std::size_t max_y );

    long get_score( std::size_t max_x, std::size_t max_y );

    int get_min_path();

    std::vector<t_position> get_neighbor_cells( const t_position & currentPos );

    std::vector<NextHop> get_next_hops( const NextHop & currentHop, const std::vector<t_position> & neighborsPos );

    void set_score( std::vector<std::string> initScore);

public:

    unsigned depth;
    t_position target_pos;

    t_field_calc field_calc;
    t_field_score field_score;

    std::ofstream ofs{ "out.txt" };

};


