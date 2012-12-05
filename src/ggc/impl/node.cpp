#ifndef GGC_IMPL_NODE_CPP
#define GGC_IMPL_NODE_CPP

#include <ostream>
#include <utility>

#include <ggc/decl/node.hpp>

template <typename Numeric>
node<Numeric>::node( numeric_t const & x, numeric_t const & y )
: x( x ), y( y )
{

}

template <typename Numeric>
node<Numeric>::node( numeric_t && x, numeric_t && y )
: x( std::move( x ) ), y( std::move( y ) )
{

}

template <typename Numeric>
std::ostream & operator<<(
  std::ostream & ostream,
  node<Numeric> const & node )
{
  return ostream << '(' << node.x << ',' << node.y << ')';
}

template <typename Numeric>
bool node<Numeric>::descending(
  node const & node_1,
  node const & node_2 )
{
  return !(node_1.y < node_2.y);
}

template <typename Numeric>
bool node<Numeric>::ascending(
  node const & node_1,
  node const & node_2 )
{
  return !(node_2.y < node_1.y);
}

template <typename Numeric>
bool node<Numeric>::strict_descending(
  node const & node_1,
  node const & node_2 )
{
  return node_2.y < node_1.y;
}

template <typename Numeric>
bool node<Numeric>::strict_ascending(
  node const & node_1,
  node const & node_2 )
{
  return node_1.y < node_2.y;
}

template <typename Numeric>
bool node<Numeric>::right_turn(
  node const & node_1,
  node const & node_2,
  node const & node_3 )
{
  return cross_product( node_1, node_2, node_3 ) != plus;
}

template <typename Numeric>
bool node<Numeric>::left_turn(
  node const & node_1,
  node const & node_2,
  node const & node_3 )
{
  return cross_product( node_1, node_2, node_3 ) != minus;
}

template <typename Numeric>
bool node<Numeric>::strict_right_turn(
  node const & node_1,
  node const & node_2,
  node const & node_3 )
{
  return cross_product( node_1, node_2, node_3 ) == minus;
}

template <typename Numeric>
bool node<Numeric>::strict_left_turn(
  node const & node_1,
  node const & node_2,
  node const & node_3 )
{
  return cross_product( node_1, node_2, node_3 ) == plus;
}

template <typename Numeric>
typename node<Numeric>::cross_product_result
node<Numeric>::cross_product(
  node const & node_1,
  node const & node_2,
  node const & node_3 )
{
  numeric_t d1x = node_2.x - node_1.x;
  numeric_t d1y = node_2.y - node_1.y;
  numeric_t d2x = node_3.x - node_2.x;
  numeric_t d2y = node_3.y - node_2.y;

  numeric_t pl = d1x * d2y;
  numeric_t pr = d2x * d1y;

  if( pr < pl ) return plus;
  if( pl < pr ) return minus;
  return zero;
}

#endif

