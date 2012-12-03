#include <cstdlib>
#include <functional>
#include <random>
#include <vector>

#include "node.hpp"
#include "algorithm.hpp"

void run_test( bool b )
{
  if( !b )
  {
    std::exit( EXIT_FAILURE );
  }
}

int main()
{
  typedef node<int> node_t;
  typedef std::vector<node_t> test_t;
  typedef algorithm<node_t, int> algorithm_t;

  std::mt19937 engine;
  std::uniform_int_distribution<int> dist( 0, 1000 );
  auto random = std::bind( dist, engine );

  test_t test;
  for( int i = 0; i < 26; i++ )
  {
    test.push_back( node_t( random(), random() ) );
  }

  auto result = algorithm_t( test.begin(), test.end() ).run();

  run_test( result == 91779787 );
}

