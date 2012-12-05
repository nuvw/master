#include <algorithm>
#include <cstdlib>
#include <vector>

#include "state.hpp"

void run_test( bool b )
{
  if( !b )
  {
    std::exit( EXIT_FAILURE );
  }
}

int main()
{
  typedef std::vector<int> vector_t;
  typedef std::vector<int> const vector_const_t;

  vector_t vector = { 1, 2, 3, 4, 5, 6 };

  // create a new state

  vector_const_t vector_const = vector;
  auto initial_state = root(
    vector_const.begin(), vector_const.end() );

  // all nodes must be free

  run_test( std::equal(
    vector.begin(),
    vector.end(),
    initial_state.free_nodes_begin() ) );

  // no node is matched and none is marked

  run_test( initial_state.matched_nodes_begin() ==
     initial_state.matched_nodes_end() );
  run_test( initial_state.marked_node() ==
    initial_state.matched_nodes_end() );

  // match two nodes

  vector.erase( vector.begin() + 4 );
  vector.erase( vector.begin() + 1 );

  auto it1 = initial_state.free_nodes_begin();
  auto it2 = initial_state.free_nodes_begin();
  ++it1;
  ++it2; ++it2; ++it2; ++it2;
  auto successor_state = initial_state.successor( it1, it2 );

  // iterate over remaining free nodes
 
  run_test( std::equal(
    vector.begin(),
    vector.end(),
    successor_state.free_nodes_begin() ) );

  // count the number of matched nodes

  run_test( 2 == std::distance(
    successor_state.matched_nodes_begin(),
    successor_state.matched_nodes_end() ) );

  // inspect the marked node

  run_test( *successor_state.marked_node() == 5 );
}

