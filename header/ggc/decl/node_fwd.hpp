#ifndef GGC_DECL_NODE_FWD_HPP
#define GGC_DECL_NODE_FWD_HPP

#include <ostream>

template <typename Numeric>
class node;

template <typename Numeric>
std::ostream & operator<<(
  std::ostream & ostream,
  node<Numeric> const & node );

template <typename Numeric>
bool operator<(
  node<Numeric> const & node_1,
  node<Numeric> const & node_2 );

#endif

