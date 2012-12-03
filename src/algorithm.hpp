#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <vector>

#include "state.hpp"

/**
 * A class that runs the perfect matching counting algorithm on
 * a range of nodes. The template parameter Node stands for the
 * underlying node type. It is recommended to use a specialization
 * of node<T> which is provided in the file 'node.hpp'.
 * For representing the result of the algorithm the type Result is
 * used. It can be a primitive type such as 'int'. For not so
 * small inputs however one should consider using an integral
 * type that provides arbitrary precision because the number of
 * perfect matchings grows very quickly in the number of nodes.
 * The type requirements for Result are the addition assignment
 * operator+=, a copy constructor and a default constructor that
 * initializes the object to zero.
 */

#include "algorithm_free_impl.cpp"

template <typename Node, typename Result>
class algorithm
{
private:
  friend class nodes_arranger<algorithm>;
  typedef Node node_t;
  typedef Result result_t;
  typedef std::vector<node_t> nodes_t;
  typedef state<typename nodes_t::const_iterator> state_t;
  typedef std::vector<state_t> successors_t;

public:
  algorithm() = delete;
  template <typename Iterator>
  algorithm( Iterator const & begin, Iterator const & end );

public:
  result_t run() const;

private:
  successors_t successors( state_t const & parent ) const;

private:
  nodes_t const nodes;
};

#include "algorithm_member_impl.cpp"

#endif

