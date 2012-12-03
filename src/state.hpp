#ifndef STATE_HPP
#define STATE_HPP

#include <functional>
#include <iterator>
#include <ostream>
#include <vector>

/**
 * A class that represents one of the intermediate states during
 * the run of the perfect matching counting algorithm. It
 * basically keeps track of which nodes have already been matched
 * with some other node and which nodes are still free.
 * The class provides a convenient interface for the creation of
 * an initial state as well as of successor states which arise
 * when an additional matching edge is added to some parent state.
 * The class also allows forward iteration over all free or
 * matched nodes independently.
 * The template parameter Iterator stands for the type of the
 * forward iterator pair which points to the range of all
 * underlying nodes. This class is lightweight in the sense that
 * it does not make a copy of that range, which means that the
 * caller must guarantee its validity as long as the initial state
 * or any descendant from it exists.
 */

#include "state_free_impl.cpp"

template <
  typename Iterator,
  typename Traits = std::iterator_traits<Iterator>>
class state
{
  // TYPES /////////////////////////////////////////////////

private:
  typedef Iterator external_iterator_t;
  typedef Traits external_iterator_traits;
  typedef std::vector<bool> free_nodes_t;

  // ITERATION /////////////////////////////////////////////

public:
  template <bool Free>
  class nodes_iterator
  {
  private:
    typedef free_nodes_t::const_iterator internal_iterator_t;
    typedef state<Iterator, Traits> state_t;

  public:
    typedef typename
      internal_iterator_t::difference_type difference_type;
    typedef typename
      external_iterator_traits::value_type value_type;
    typedef typename
      external_iterator_traits::pointer pointer;
    typedef typename
      external_iterator_traits::reference reference;
    typedef typename
      std::forward_iterator_tag iterator_category;
    typedef typename
      std::true_type nodes_iterator_tag;

  public:
    nodes_iterator();

  private:
    friend class state<Iterator, Traits>;
    nodes_iterator(
      internal_iterator_t const & internal,
      internal_iterator_t const & internal_end,
      external_iterator_t const & external );

  public:
    reference operator*() const;
    pointer operator->() const;
    nodes_iterator & operator++();
    nodes_iterator operator++( int );
    friend bool operator== <nodes_iterator>(
      nodes_iterator const & iterator_1,
      nodes_iterator const & iterator_2 );
    friend bool operator!= <nodes_iterator>(
      nodes_iterator const & iterator_1,
      nodes_iterator const & iterator_2 );

  public:
    friend bool operator== <Iterator, Traits>(
      state const & state_1,
      state const & state_2 );
    friend bool operator< <Iterator, Traits>(
      state const & state_1,
      state const & state_2 );

  private:
    static bool dereferenceable(
      nodes_iterator const & iterator );
    static bool incrementable(
      nodes_iterator const & iterator );
    static bool comparable(
      nodes_iterator const & iterator_1,
      nodes_iterator const & iterator_2 );

  private:
    internal_iterator_t internal;
    internal_iterator_t internal_end;
    external_iterator_t external;
  };

public:
  typedef nodes_iterator<true> free_nodes_iterator;
  typedef nodes_iterator<false> matched_nodes_iterator;

private:
  template <bool Free>
  nodes_iterator<Free> nodes_begin() const;
  template <bool Free>
  nodes_iterator<Free> nodes_end() const; 

public:
  free_nodes_iterator free_nodes_begin() const;
  free_nodes_iterator free_nodes_end() const;
  matched_nodes_iterator matched_nodes_begin() const;
  matched_nodes_iterator matched_nodes_end() const;
  matched_nodes_iterator marked_node() const;

  // CONSTRUCTION //////////////////////////////////////////

public:
  friend state root<Iterator, Traits>(
    external_iterator_t const & external_begin,
    external_iterator_t const & external_end );
  state successor(
    free_nodes_iterator const & lower_node,
    free_nodes_iterator const & upper_node ) const;

private:
  state() = delete;
  state(
    external_iterator_t const & external_begin,
    external_iterator_t const & external_end );
  state(
    state const & parent,
    free_nodes_iterator const & lower_node,
    free_nodes_iterator const & upper_node );

  // STREAM INSERTION //////////////////////////////////////

public:
  friend std::ostream & operator<< <Iterator, Traits>(
    std::ostream & ostream,
    state const & state );

  // COMPARING /////////////////////////////////////////////

public:
  friend bool operator== <Iterator, Traits>(
    state const & state_1,
    state const & state_2 );
  friend bool operator< <Iterator, Traits>(
    state const & state_1,
    state const & state_2 );

private:
  static bool comparable(
    state const & state_1,
    state const & state_2 );

  // HASHING ///////////////////////////////////////////////

public:
  friend class std::hash<state>;

  // ATTRIBUTES (ALL CONST UNLESS MOVED FROM THIS) /////////

private:
  external_iterator_t external_begin;
  external_iterator_t external_end;
  free_nodes_t free_nodes;
  matched_nodes_iterator marked;
};

#include "state_member_impl.cpp"

#endif

