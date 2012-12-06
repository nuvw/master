#ifndef GGC_IMPL_STATE_CPP
#define GGC_IMPL_STATE_CPP

#include <algorithm>
#include <cassert>
#include <functional>
#include <iterator>
#include <type_traits>
#include <utility>

#include <ggc/decl/state.hpp>

template <typename Iterator, typename Traits>
template <bool Free>
state<Iterator, Traits>::nodes_iterator<Free>::nodes_iterator()
: state_ptr( nullptr )
{

}

template <typename Iterator, typename Traits>
template <bool Free>
state<Iterator, Traits>::nodes_iterator<Free>::nodes_iterator(
  state const * state_ptr,
  index_t index,
  external_iterator_t const & external )
: state_ptr( state_ptr ),
  index( index ),
  external( external )
{

}

template <typename Iterator, typename Traits>
template <bool Free>
typename state<Iterator, Traits>::template
nodes_iterator<Free>::reference
state<Iterator, Traits>::nodes_iterator<Free>::operator*() const
{
  assert( !null( *this ) );
  assert( dereferenceable( *this ) );

  return *external;
}

template <typename Iterator, typename Traits>
template <bool Free>
typename state<Iterator, Traits>::template
nodes_iterator<Free>::pointer
state<Iterator, Traits>::nodes_iterator<Free>::operator->() const
{
  return &operator*();
}

template <typename Iterator, typename Traits>
template <bool Free>
state<Iterator, Traits>::nodes_iterator<Free> &
state<Iterator, Traits>::nodes_iterator<Free>::operator++()
{
  assert( !null( *this ) );
  assert( incrementable( *this ) );

  while( ++external, ++index != state_ptr->free_nodes.size() &&
    state_ptr->free_nodes[index] != Free );

  return *this;
}

template <typename Iterator, typename Traits>
template <bool Free>
state<Iterator, Traits>::nodes_iterator<Free>
state<Iterator, Traits>::nodes_iterator<Free>::operator++( int )
{
  nodes_iterator temp( *this );

  operator++();

  return std::move( temp );
}

template <typename Iterator>
typename std::enable_if<is_nodes_iterator<Iterator>::value,
bool>::type operator==(
  Iterator const & iterator_1,
  Iterator const & iterator_2 )
{
  assert( !Iterator::null( iterator_1 ) );
  assert( !Iterator::null( iterator_2 ) );
  assert( Iterator::comparable( iterator_1, iterator_2 ) );

  return iterator_1.index == iterator_2.index;
}

template <typename Iterator>
typename std::enable_if<is_nodes_iterator<Iterator>::value,
bool>::type operator!=(
  Iterator const & iterator_1,
  Iterator const & iterator_2 )
{
  return !(iterator_1 == iterator_2);
}

template <typename Iterator, typename Traits>
template <bool Free>
bool
state<Iterator, Traits>::nodes_iterator<Free>::null(
  nodes_iterator const & iterator )
{
  return iterator.state_ptr == nullptr;
}

template <typename Iterator, typename Traits>
template <bool Free>
bool
state<Iterator, Traits>::nodes_iterator<Free>::dereferenceable(
  nodes_iterator const & iterator )
{
  return iterator.index != iterator.state_ptr->free_nodes.size();
}

template <typename Iterator, typename Traits>
template <bool Free>
bool
state<Iterator, Traits>::nodes_iterator<Free>::incrementable(
  nodes_iterator const & iterator )
{
  return iterator.index != iterator.state_ptr->free_nodes.size();
}

template <typename Iterator, typename Traits>
template <bool Free>
bool
state<Iterator, Traits>::nodes_iterator<Free>::comparable(
  nodes_iterator const & iterator_1,
  nodes_iterator const & iterator_2 )
{
  return iterator_1.state_ptr == iterator_2.state_ptr;
}

template <typename Iterator, typename Traits>
template <bool Free>
state<Iterator, Traits>::nodes_iterator<Free>
state<Iterator, Traits>::nodes_begin() const
{
  if( !free_nodes.empty() )
  {
    nodes_iterator<Free> it( this, 0, external_begin );

    if( free_nodes[0] != Free ) ++it;

    return std::move( it );
  }

  return nodes_end<Free>();
} 

template <typename Iterator, typename Traits>
template <bool Free>
state<Iterator, Traits>::nodes_iterator<Free>
state<Iterator, Traits>::nodes_end() const
{
  return nodes_iterator<Free>(
    this,
    free_nodes.size(),
    external_end );
}

template <typename Iterator, typename Traits>
typename state<Iterator, Traits>::free_nodes_iterator
state<Iterator, Traits>::free_nodes_begin() const
{
  return nodes_begin<true>();
}

template <typename Iterator, typename Traits>
typename state<Iterator, Traits>::free_nodes_iterator
state<Iterator, Traits>::free_nodes_end() const
{
  return nodes_end<true>();
}

template <typename Iterator, typename Traits>
typename state<Iterator, Traits>::matched_nodes_iterator
state<Iterator, Traits>::matched_nodes_begin() const
{
  return nodes_begin<false>();
}

template <typename Iterator, typename Traits>
typename state<Iterator, Traits>::matched_nodes_iterator
state<Iterator, Traits>::matched_nodes_end() const
{
  return nodes_end<false>();
}

template <typename Iterator, typename Traits>
typename state<Iterator, Traits>::matched_nodes_iterator
state<Iterator, Traits>::marked_node() const
{
  return marked;
}

template <typename Iterator, typename Traits>
state<Iterator, Traits> root(
  Iterator const & external_begin,
  Iterator const & external_end )
{
  return state<Iterator, Traits>( external_begin, external_end );
}

template <typename Iterator, typename Traits>
state<Iterator, Traits> state<Iterator, Traits>::successor(
  free_nodes_iterator const & lower_node,
  free_nodes_iterator const & upper_node ) const
{
  return state( *this, lower_node, upper_node );
}

template <typename Iterator, typename Traits>
state<Iterator, Traits>::state( state const & state )
: external_begin( state.external_begin ),
  external_end( state.external_end ),
  free_nodes( state.free_nodes ),
  marked(
    this,
    state.marked.index,
    state.marked.external )
{

}

template <typename Iterator, typename Traits>
state<Iterator, Traits>::state( state && state )
: external_begin( std::move( state.external_begin ) ),
  external_end( std::move( state.external_end ) ),
  free_nodes( std::move( state.free_nodes ) ),
  marked(
    this,
    state.marked.index,
    std::move( state.marked.external ) )
{

}

template <typename Iterator, typename Traits>
state<Iterator, Traits> & state<Iterator, Traits>::operator=(
  state const & state )
{
  external_begin = state.external_begin;
  external_end = state.external_end;
  free_nodes = state.free_nodes;
  marked = matched_nodes_iterator(
    this,
    state.marked.index,
    state.marked.external );

  return *this;
}

template <typename Iterator, typename Traits>
state<Iterator, Traits> & state<Iterator, Traits>::operator=(
  state && state )
{
  external_begin = std::move( state.external_begin );
  external_end = std::move( state.external_end );
  free_nodes = std::move( state.free_nodes );
  marked = matched_nodes_iterator(
    this,
    state.marked.index,
    std::move( state.marked.external ) );

  return *this;
}

template <typename Iterator, typename Traits>
state<Iterator, Traits>::state(
  external_iterator_t const & external_begin,
  external_iterator_t const & external_end )
: external_begin( external_begin ),
  external_end( external_end ),
  free_nodes(
    std::distance( external_begin, external_end ),
    true ),
  marked( matched_nodes_end() )
{

}

template <typename Iterator, typename Traits>
state<Iterator, Traits>::state(
  state const & parent,
  free_nodes_iterator const & lower_node,
  free_nodes_iterator const & upper_node )
: external_begin( parent.external_begin ),
  external_end( parent.external_end ),
  free_nodes( parent.free_nodes ),
  marked( this, upper_node.index, upper_node.external )
{
  free_nodes[lower_node.index] = false;
  free_nodes[upper_node.index] = false;
}

template <typename Iterator, typename Traits>
std::ostream & operator<<(
  std::ostream & ostream,
  state<Iterator, Traits> const & state )
{
  std::copy(
    state.free_nodes.begin(),
    state.free_nodes.end(),
    std::ostream_iterator<bool>( ostream ) );

  return ostream;
}

template <typename Iterator, typename Traits>
bool operator==(
  state<Iterator, Traits> const & state_1,
  state<Iterator, Traits> const & state_2 )
{
  assert(( state<Iterator, Traits>::comparable(
    state_1,
    state_2 ) ));

  bool equal = std::equal(
    state_1.free_nodes.begin(),
    state_1.free_nodes.end(),
    state_2.free_nodes.begin() );

  return equal && state_1.marked.index == state_2.marked.index;
}

template <typename Iterator, typename Traits>
bool operator<(
  state<Iterator, Traits> const & state_1,
  state<Iterator, Traits> const & state_2 )
{
  assert(( state<Iterator, Traits>::comparable(
    state_1,
    state_2 ) ));

  bool lexico = std::lexicographical_compare(
    state_1.free_nodes.begin(),
    state_1.free_nodes.end(),
    state_2.free_nodes.begin(),
    state_2.free_nodes.end() );
  bool equal = std::equal(
    state_1.free_nodes.begin(),
    state_1.free_nodes.end(),
    state_2.free_nodes.begin() );

  return lexico || (equal &&
    state_1.marked.index < state_2.marked.index);
}

template <typename Iterator, typename Traits>
bool state<Iterator, Traits>::comparable(
  state const & state_1,
  state const & state_2 )
{
  return state_1.external_begin == state_2.external_begin &&
    state_1.external_end == state_2.external_end;
}

namespace std
{
  template <typename Iterator, typename Traits>
  struct hash<state<Iterator, Traits>>
  {
  public:
    std::size_t operator()(
      state<Iterator, Traits> const & state ) const
    {
      typedef typename
        ::state<Iterator, Traits>::free_nodes_t free_nodes_t;

      return std::hash<free_nodes_t>()( state.free_nodes );
    }
  };
}

#endif

