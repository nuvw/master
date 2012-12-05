#include "utility/console.hpp"

#include "algorithm.hpp"
#include "node.hpp"

using utility::console::write_line;

struct profiler
{
  profiler( int size )
  : size( size )
  {
    write_line( "Profile for %1% points:", size );
  }

  void report_iteration( int iteration, int states, int edges )
  {
    write_line( "> Iteration %|2|: %|8| states (%|.2f|), %|8| edges",
      iteration,
      states,
      states / states_upper_bound( iteration ),
      edges );
  }

  void report_final( int states )
  {
    write_line( "> Done: %|16| states (%|.2f|)",
      states,
      states / states_upper_bound( size / 2 ) );
  }

  ~profiler()
  {
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

  float states_upper_bound( int iteration )
  {
    return binomial_coefficient_ish( size, 2*iteration )
      * std::max( 2*iteration, 1 ); 
  }

  int size;
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
    for( int i = 0; i < size; ++size )
    {
      test.push_back( node_t( random(), random() ) );
    }

    profiler p( i );
  }
}
