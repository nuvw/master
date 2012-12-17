#include <cmath>
#include <functional>
#include <iostream>
#include <random>
#include <set>

#include <ggc/algorithm>
#include <ggc/node>

double log2( double x )
{
  return std::log( x ) / std::log( 2 );
}

int main()
{
  typedef node<int> node_t;
  typedef std::set<node_t> nodes_t;
  typedef algorithm<node_t, int> algo_t;

  std::size_t const n_max = 26;
  int const reps = 10;

  std::mt19937 engine;
  std::uniform_int_distribution<int> dist( 0, 1000 );
  auto random = std::bind( dist, engine );

  for( std::size_t n = 0; n <= n_max; n += 2 )
  {
    double pm_S = 0.0;
    double log_pm_S = 0.0;

    for( int i = 0; i < reps; ++i )
    {
      nodes_t nodes;
      while( nodes.size() != n )
      {
        auto c1 = random();
        auto c2 = random();

        nodes.insert( node_t( c1, c2 ) );
      }

      auto result = algo_t( nodes.begin(), nodes.end() ).run();

      pm_S += result;
      log_pm_S += log2( result );
    }

    pm_S /= reps;
    log_pm_S /= reps;

    std::cout << "|S| = " << n << std::endl;
    std::cout << "E[pm(S)] = " << pm_S << std::endl;
    std::cout << "E[log pm(S)] = " << log_pm_S << std::endl;
    std::cout << "2^E[log pm(S)] = "
      << std::pow( 2, log_pm_S ) << std::endl;
    std::cout << std::endl;
  }
}

