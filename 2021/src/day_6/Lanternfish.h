//
// Created by alexey on 07.12.2021.
//

#ifndef ADVENTOFCODE2021_LANTERNFISH_H
#define ADVENTOFCODE2021_LANTERNFISH_H

#include <vector>


class Lanternfish
{
private:

  static std::vector< long long > grow_fish( const std::vector< long long > & fish );

public:

  long long task_1( const std::vector< int > & fish, int days );
};


#endif //ADVENTOFCODE2021_LANTERNFISH_H
