//
// Created by alexpall on 16.12.2020.
//

#include "shuttle_search.h"

#include <vector>
#include <iostream>
#include <regex>

#include "common/file_reader.h"
#include "common/common.h"


struct InputData
{
    int currentTimeId;
    std::vector< int > busIDs;
};


InputData prepare_input( const std::string & filename )
{
  // Read the file
  std::vector<std::string> sInput = FileReader::read_file( filename );

  InputData data;
  data.currentTimeId = std::stoi( sInput[ 0 ] );

  std::regex getBusIDs(R"((\d+))");
  std::smatch searchResult;

  while( std::regex_search( sInput[ 1 ], searchResult, getBusIDs ) )
  {
    data.busIDs.push_back( std::stoi( searchResult[ 0 ] ) );
    sInput[ 1 ] = searchResult.suffix().str();
  }

  return data;
}




int ShuttleSearch::task_1( const std::string & filename )
{
  InputData input = prepare_input( filename );

  std::vector< std::pair< int, int > > nearestBuses;

  for ( int _busId : input.busIDs )
  {
    int nearesTimeStamp = input.currentTimeId / _busId * _busId;
    if ( nearesTimeStamp < input.currentTimeId )
      nearesTimeStamp += _busId;

    nearestBuses.emplace_back( nearesTimeStamp, _busId );
  }

  std::sort( nearestBuses.begin(), nearestBuses.end(),
             []( const std::pair< int, int > & lhs, const std::pair< int, int > & rhs )
               { return lhs.first < rhs.first; } );

  return ( nearestBuses[ 0 ].first - input.currentTimeId ) * nearestBuses[ 0 ].second;
}
#include<bits/stdc++.h>

using namespace std;
const int N = 20;
long long GCD(long long a, long long b) { return (b == 0) ? a : GCD(b, a % b); }
inline long long LCM(long long a, long long b) { return a / GCD(a, b) * b; }
inline long long normalize(long long x, long long mod) { x %= mod; if (x < 0) x += mod; return x; }
struct GCD_type { long long x, y, d; };

GCD_type ex_GCD(long long a, long long b)
{
  if (b == 0) return {1, 0, a};
  GCD_type pom = ex_GCD(b, a % b);
  return {pom.y, pom.x - a / b * pom.y, pom.d};
}

//int main()
//{
//  ios_base::sync_with_stdio(0);
//  cin.tie(0);
//  cin >> t;
//  for(int i = 1; i <= t; i++) cin >> a[i] >> n[i], normalize(a[i], n[i]);
//  ans = a[1];
//  lcm = n[1];
//  for(int i = 2; i <= t; i++)
//  {
//    auto pom = ex_GCD(lcm, n[i]);
//    int x1 = pom.x;
//    int d = pom.d;
//    if((a[i] - ans) % d != 0) return cerr << "No solutions" << endl, 0;
//    ans = normalize(ans + x1 * (a[i] - ans) / d % (n[i] / d) * lcm, lcm * n[i] / d);
//    lcm = LCM(lcm, n[i]); // you can save time by replacing above lcm * n[i] /d by lcm = lcm * n[i] / d
//  }
//  cout << ans << " " << lcm << endl;
//
//  return 0;
//}


long long ShuttleSearch::task_2( const std::string &filename )
{
  int testCases;
  int t = 3;
  long long a[] = { 0, 0, 2, 3 }, n[] = { 0, 17, 13, 19 }, ans, lcm;

  for(int i = 1; i <= t; i++) normalize(a[i], n[i]);

  ans = a[1];
  lcm = n[1];
  for(int i = 2; i <= t; i++)
  {
    auto pom = ex_GCD(lcm, n[i]);
    int x1 = pom.x;
    int d = pom.d;
    if((a[i] - ans) % d != 0) return cerr << "No solutions" << endl, 0;
    ans = normalize(ans + x1 * (a[i] - ans) / d % (n[i] / d) * lcm, lcm * n[i] / d);
    lcm = LCM(lcm, n[i]); // you can save time by replacing above lcm * n[i] /d by lcm = lcm * n[i] / d
  }
  cout << ans << " " << lcm << endl;

//  // 17,x,13,19 is 3417.
//  std::vector< long long > a { 0, 2, 3 };
//  std::vector< long long > n { 17, 13, 19 };
//  std::vector< long long > m ( a.size(), 0 );
//  std::vector< long long > mi ( a.size(), 0 );
//  long long Y { 0 };
//
//  long long M { 1 };
//
//  for( auto _num : n )
//    M *= _num;                   // calculating M = n1 * n2 * ....
//
//  std::cout << "\nM = " << M << std::endl;
//  for( std::size_t idx = 0; idx < a.size(); ++idx )
//  {
//    m[ idx ] = M / n[ idx ];              //calculating m1 = M/n1 ,m2=M/n2,.....
//    std::cout << "m" << idx << " = " << m[ idx ] << std::endl;
//  }
//
//  for( std::size_t idx = 0; idx < a.size(); ++idx )
//  {
//    mi[ idx ] = m[ idx ] % n[ idx ];  //calculating m1' = m1 MOD n1 ,m2'=m2 MOD n2,.....
//    std::cout << "m" << idx << " inverse = "<< mi[ idx ] <<std::endl;
//  }
//
//  for( std::size_t idx = 0; idx < a.size(); ++idx )
//  {
//    Y = Y + ( a[ idx ] * m[ idx ] * mi[ idx ] ); //calculating Final Value of Y
//  }
//  std::cout << "Y = " << Y << std::endl;
//  Y = Y % M;
//  std::cout << "Chinese Remainder ( Y MOD M ) :- " << Y << std::endl; //displaying OUTPUT
}
