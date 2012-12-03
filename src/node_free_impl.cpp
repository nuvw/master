#include <ostream>

template <typename Numeric>
class node;

template <typename Numeric>
std::ostream & operator<<(
  std::ostream & ostream,
  node<Numeric> const & node )
{
  return ostream << '(' << node.x << ',' << node.y << ')';
}

