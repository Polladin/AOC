

#include <functional>


std::function< bool( const std::pair< int, int > &, const std::pair< int, int > & ) > 
  compare_pairs =
    []( const std::pair< int, int > & lhs, const std::pair< int, int > & rhs )
    { return lhs.first == rhs.first ? lhs.second < rhs.second
                                    : lhs.first < rhs.first;    
    };