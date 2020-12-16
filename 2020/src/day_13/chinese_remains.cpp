//
// Created by alexey on 16.12.2020.
//

#include "chinese_remains.h"

#include <algorithm>
#include <functional>
#include <numeric>
#include <iostream>


long long calc_inverse( long long A, long long C )
{
    long long B = 1;

    while ( ( A * B ) % C != 1 )
    {
        ++B;
//        if( B >= C )
//            throw std::invalid_argument( "Not co-prime numbers" );
    }
    return B;
}

uint64_t xgcd( uint64_t a, uint64_t b )
{
  if ( b == 1 )
    return 1;

  uint64_t olb_b = b;
  uint64_t r = 0;
  uint64_t s = 1;
  while ( a > 1 )
  {
    uint64_t q = a / b;
    uint64_t _a = a;
    a = b;
    b = _a % b;
    uint64_t _r = r;
    r = s - q * r;
    s = _r;
  }
  if ( s < 0 )
    s += olb_b;

  return s;
}

long long ChineseRemains::calculate( const std::vector< long long > & a, const std::vector< long long > & m )
{
    // Calculate M
    uint64_t M = std::accumulate( m.begin(), m.end(), 1ll, std::multiplies<>() );

    std::cout << "M: " << M << "\n";

    // Calculate b
    std::vector< uint64_t > b ( a.size() );
    for ( std::size_t idx = 0; idx < b.size(); ++idx )
    {
      b[ idx ] = M / m[ idx ];
//      b[ idx ] = 1;
//      for ( std::size_t idx2 = 0; idx2 < m.size(); ++idx2 )
//        if ( idx != idx2 )
//          b[ idx ] *= m[ idx2 ];
    }

    // Calculate b' = b^-1 ( mod m )
    std::vector< long long > bInverse ( b.size() );
    for ( std::size_t idx = 0; idx < bInverse.size(); ++idx )
    {
        bInverse[ idx ] = calc_inverse( b[ idx ], m[ idx ] ) % m[ idx ]; //xgcd( b[ idx ], m[ idx ] );// calc_inverse( b[ idx ], m[ idx ] ) % m[ idx ];
        std::cout << "n = " << m[ idx ] << " a = " << a[ idx ] << " n_i = " << b[ idx ] << " s_i = " << bInverse[ idx ] << "\n";
    }
    std::cout << "\n";

    // x = Sum (a b bInverse) ( mod M )
    uint64_t res { 0 };
    std::cout << "Res : ";
    for ( std::size_t idx = 0; idx < bInverse.size(); ++idx )
    {
      std::cout << res << " ";
        res += a[ idx ] * b[ idx ] * bInverse[ idx ];
    }
    std::cout << res << "\n";
    res = res % M;
  std::cout << "Res: " << res << "\n";

    return res;
}
