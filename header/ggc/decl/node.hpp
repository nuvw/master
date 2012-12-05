#ifndef GGC_DECL_NODE_HPP
#define GGC_DECL_NODE_HPP

#include <ostream>

#include <ggc/decl/node_fwd.hpp>

/**
 * A class that represents a node in the plane with x and y
 * coordinates. The origin of the coordinate system is assumed to
 * be in the bottom left corner with the x-axis pointing to the
 * right and the y-axis pointing upwards.
 * The template parameter Numeric stands for the underlying
 * numeric type. In order for all features of this class to be
 * available, the type Numeric must support the following:
 * @         Numeric( Numeric const & ),     copy constructible;
 * @         Numeric( Numeric && ),          move constructible;
 * @ ostream operator<<( ostream, Numeric ), stream insertable;
 * @ bool    operator<( Numeric, Numeric ),  strict total order;
 * @ Numeric operator-( Numeric, Numeric ),  subtraction;
 * @ Numeric operator*( Numeric, Numeric ),  multiplication.
 */

template <typename Numeric>
class node
{
private:
  typedef Numeric numeric_t;

public:
  node( numeric_t const & x, numeric_t const & y );
  node( numeric_t && x, numeric_t && y );

public:
  friend std::ostream & operator<< <Numeric>(
    std::ostream & ostream,
    node const & node );

public:
  static bool descending(
    node const & node_1,
    node const & node_2 );
  static bool ascending(
    node const & node_1,
    node const & node_2 );
  static bool strict_descending(
    node const & node_1,
    node const & node_2 );
  static bool strict_ascending(
    node const & node_1,
    node const & node_2 );
  static bool right_turn(
    node const & node_1,
    node const & node_2,
    node const & node_3 );
  static bool left_turn(
    node const & node_1,
    node const & node_2,
    node const & node_3 );
  static bool strict_right_turn(
    node const & node_1,
    node const & node_2,
    node const & node_3 );
  static bool strict_left_turn(
    node const & node_1,
    node const & node_2,
    node const & node_3 );

private:
  enum cross_product_result {
    minus,
    zero,
    plus
  };
  static cross_product_result cross_product(
    node const & node_1,
    node const & node_2,
    node const & node_3 );

public:
  numeric_t x;
  numeric_t y;
};

#endif

