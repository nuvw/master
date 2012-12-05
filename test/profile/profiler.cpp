#include <ggc/algorithm>
#include <ggc/node>

#include "utility/console.hpp"

using utility::console::write_line;

struct profiler
{
  void initiate( int nodes )
  {
    write_line( "Profile for %1% points:", nodes );
    write_line( ">" );

    size = nodes;
    states_total = 0;
    edges_total = 0;
  }

  void iterate( int iteration, int states, int edges )
  {
    float states_ub = states_upper_bound( 2*iteration );

    write_line( 
      "> Iteration %|2|: %|8| states (%|.2f|), %|8| edges",
      iteration,
      states,
      states / states_ub,
      edges );

    states_total += states;
    states_ub_total += states_ub;
    edges_total += edges;
  }

  void finalize( int states )
  {
    float states_ub = states_upper_bound( size );

    write_line( "> Finally: %|13| states (%|.2f|)",
      states,
      states / states_ub );

    states_total += states;
    states_ub_total += states_ub;
  }

  ~profiler()
  {
    write_line( ">" );
    write_line(
      "> %|8| states total (%|.2f|), %|8| edges total",
      states_total,
      states_total / states_ub_total,
      edges_total );
    write_line( "" ); 
  }

  float binomial_coefficient_ish( int n, int k )
  {
    float result = 1;

    for( int i = 1; i <= n; ++i ) result *= i;
    for( int i = 1; i <= k; ++i ) result /= i;
    for( int i = 1; i <= (n-k); ++i ) result /= i;
   
    return result;
  }

  float states_upper_bound( int matched )
  {
    return binomial_coefficient_ish( size, matched )
      * std::max( matched, 1 ); 
  }

  int size;
  int states_total;
  float states_ub_total;
  int edges_total;
};

int main()
{
  typedef node<int> node_t;
  typedef std::vector<node_t> test_t;
  typedef algorithm<node_t, int> algorithm_t;

  std::mt19937 engine;
  std::uniform_int_distribution<int> dist( 0, 1000 );
  auto random = std::bind( dist, engine );

  for( int size = 0; size <= 30; size += 2 )
  {
    test_t test;
    for( int i = 0; i < size; ++i )
    {
      test.push_back( node_t( random(), random() ) );
    }

    profiler p;
    algorithm_t( test.begin(), test.end() ).run( p );
  }
}

