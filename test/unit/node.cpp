#include <cstdlib>
#include <sstream>

#include <ggc/impl/node.cpp>

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

  // Construction

  node_t n1( 1, 1 );
  node_t n2( 2, 1 );
  node_t n3( 2, 2 );
  node_t n4( 3, 3 );

  // Stream insertion

  std::ostringstream oss;
  oss << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4;
  run_test( oss.str() == "(1,1) (2,1) (2,2) (3,3)" );

  // Predicates

  run_test(          node_t::ascending( n1, n1 ) );
  run_test(         node_t::descending( n1, n1 ) );
  run_test(  !node_t::strict_ascending( n1, n1 ) );
  run_test( !node_t::strict_descending( n1, n1 ) );

  run_test(          node_t::ascending( n1, n3 ) );
  run_test(        !node_t::descending( n1, n3 ) );
  run_test(   node_t::strict_ascending( n1, n3 ) );
  run_test( !node_t::strict_descending( n1, n3 ) );

  run_test(          node_t::ascending( n2, n3 ) );
  run_test(        !node_t::descending( n2, n3 ) );
  run_test(   node_t::strict_ascending( n2, n3 ) );
  run_test( !node_t::strict_descending( n2, n3 ) );

  run_test(          node_t::ascending( n1, n2 ) );
  run_test(         node_t::descending( n1, n2 ) );
  run_test(  !node_t::strict_ascending( n1, n2 ) );
  run_test( !node_t::strict_descending( n1, n2 ) );

  run_test(         !node_t::ascending( n4, n2 ) );
  run_test(         node_t::descending( n4, n2 ) );
  run_test(  !node_t::strict_ascending( n4, n2 ) );
  run_test(  node_t::strict_descending( n4, n2 ) );

  run_test(          node_t::left_turn( n1, n2, n3 ) );  
  run_test(        !node_t::right_turn( n1, n2, n3 ) );  
  run_test(   node_t::strict_left_turn( n1, n2, n3 ) );  
  run_test( !node_t::strict_right_turn( n1, n2, n3 ) );  
  
  run_test(         !node_t::left_turn( n1, n3, n2 ) );  
  run_test(         node_t::right_turn( n1, n3, n2 ) );  
  run_test(  !node_t::strict_left_turn( n1, n3, n2 ) );  
  run_test(  node_t::strict_right_turn( n1, n3, n2 ) );  
 
  run_test(          node_t::left_turn( n1, n3, n4 ) );  
  run_test(         node_t::right_turn( n1, n3, n4 ) );  
  run_test(  !node_t::strict_left_turn( n1, n3, n4 ) );  
  run_test( !node_t::strict_right_turn( n1, n3, n4 ) );  
}

