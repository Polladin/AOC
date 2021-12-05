//
// Created by alexey on 04.12.2021.
//

#ifndef ADVENTOFCODE2021_GIANTSQUID_H
#define ADVENTOFCODE2021_GIANTSQUID_H

#include <string>
#include <vector>
#include <optional>


class GiantSquid
{
private:

  // ---------------  Board --------------------------
  struct Board
  {
    struct BoardNumber
    {
      explicit BoardNumber( int i_num ) : num { i_num } {}
      int num;
      bool marked { false };
    };

    void add_line( const std::vector< BoardNumber > & line ) { field.push_back( line ); }

    std::vector< std::vector< BoardNumber > > field;
  };

private:

  void prepare_input( const std::string & filename );

  static std::vector< Board::BoardNumber > get_board_line( const std::string & str );

  void mark_numbers_on_boards( int num );

  [[nodiscard]] std::optional< int > search_winner() const;

  [[nodiscard]] int get_sum_unmarked_numbers( std::size_t boardIdx ) const;

  [[maybe_unused]] void print_board( const Board & board ) const;

public:

  int task_1( const std::string & filename );
  int task_2( const std::string & filename );

private:

  std::vector< int > m_randomNumbers;
  std::vector< Board > m_boards;

};


#endif //ADVENTOFCODE2021_GIANTSQUID_H
