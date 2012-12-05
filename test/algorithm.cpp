#include <cstdlib>
#include <vector>

#include "node.hpp"
#include "algorithm.hpp"

template <typename Test, typename Result>
void run_test( Test const & test, Result const & result )
{
  typedef algorithm<typename Test::value_type, Result> algo_t;

  if( algo_t( test.begin(), test.end() ).run() != result )
  {
    std::exit( EXIT_FAILURE );
  }
}

int main()
{
  typedef node<int> node_t;
  typedef std::vector<node_t> test_t;

  // 0 points, general position

  run_test( test_t( {
  } ), 1 );

  // 1 point, general position

  run_test( test_t( {
    node_t(1,1)
  } ), 0 );

  // 2 points, general position

  run_test( test_t( {
    node_t(1,1), node_t(2,2)
  } ), 1 );

  // 2 points, aligned horizontally

  run_test( test_t( {
    node_t(1,1), node_t(2,1)
  } ), 1 );

  // 2 points, aligned vertically

  run_test( test_t( {
    node_t(1,1), node_t(1,2)
  } ), 1 );

  // 2 points, identical (i.e., 1 actual point)

  run_test( test_t( {
    node_t(1,1), node_t(1,1)
  } ), 0 );

  // 3 points, general position

  run_test( test_t( {
    node_t(1,1), node_t(3,2), node_t(2,3)
  } ), 0 );

  // 3 points, 2 identical (i.e., 2 actual points)

  run_test( test_t( {
    node_t(1,1), node_t(2,2), node_t(1,1)
  } ), 1 );

  // 4 points, general convex position

  run_test( test_t( {
    node_t(1,1), node_t(9,9),
    node_t(2,8), node_t(8,2)
  } ), 2 );

  // 4 points, 2x2 grid

  run_test( test_t( {
    node_t(1,1), node_t(2,1),
    node_t(1,2), node_t(2,2)
  } ), 2 );

  // 4 points, non-convex position

  run_test( test_t( {
    node_t(1,1), node_t(5,2),
    node_t(2,5), node_t(3,3)
  } ), 3 );

  // 6 points, convex position

  run_test( test_t( {
    node_t(2,2), node_t(4,1), node_t(6,3),
    node_t(5,5), node_t(3,6), node_t(1,4) 
  } ), 5 );

  // 6 points, 2x3 grid

  run_test( test_t( {
    node_t(1,1), node_t(2,1), node_t(1,2),
    node_t(2,2), node_t(1,3), node_t(2,3)
  } ), 5 );

  // 6 points, 3x2 grid

  run_test( test_t( {
    node_t(1,1), node_t(2,1), node_t(3,1),
    node_t(1,2), node_t(2,2), node_t(3,2)
  } ), 5 );

  // 6 points, big triangle containing small triangle

  run_test( test_t( {
    node_t(1,1), node_t(5,1), node_t(3,6),
    node_t(2,2), node_t(4,2), node_t(3,4)
  } ), 12 );

  // 6 points, big triangle containing small rotated triangle

  run_test( test_t( {
    node_t(1,1), node_t(5,1), node_t(3,6),
    node_t(3,2), node_t(2,3), node_t(4,3)
  } ), 11 );

  // 6 points, straight line

  run_test( test_t( {
    node_t(1,1), node_t(2,2), node_t(3,3),
    node_t(4,4), node_t(5,5), node_t(6,6)
  } ), 1 );

  // 8 points, convex position

  run_test( test_t( {
    node_t(1,4), node_t(2,6), node_t(3,2), node_t(4,8),
    node_t(5,1), node_t(6,7), node_t(7,3), node_t(8,5)
  } ), 14 );

  // 8 points, big square containing small square

  run_test( test_t( {
    node_t(1,1), node_t(5,1), node_t(1,5), node_t(5,5),
    node_t(2,2), node_t(4,2), node_t(2,4), node_t(4,4)
  } ), 31 );

  // 8 points, big square containing small rotated square

  run_test( test_t( {
    node_t(1,1), node_t(5,1), node_t(1,5), node_t(5,5),
    node_t(3,2), node_t(2,3), node_t(4,3), node_t(3,4)
  } ), 38 );

  // 10 points, convex position

  run_test( test_t( {
    node_t(1,1), node_t(1,2), node_t(2,1),
    node_t(2,4), node_t(3,5), node_t(4,2), node_t(5,3),
    node_t(5,6), node_t(6,5), node_t(6,6)
  } ), 42 );
}

