#include <algorithm>
#include <cassert>
#include <iterator>
#include <type_traits>

template <typename Iterator>
auto detect_nodes_iterator_tag( void * )
  -> typename Iterator::nodes_iterator_tag;

template <typename Iterator>
auto detect_nodes_iterator_tag( ... )
  -> std::false_type;

template <typename Iterator>
using is_nodes_iterator = decltype(
  detect_nodes_iterator_tag<Iterator>( nullptr ) );

template <typename Iterator>
typename std::enable_if<is_nodes_iterator<Iterator>::value,
bool>::type operator==(
  Iterator const & iterator_1,
  Iterator const & iterator_2 )
{
  assert( Iterator::comparable( iterator_1, iterator_2 ) );

  return iterator_1.internal == iterator_2.internal;
}

template <typename Iterator>
typename std::enable_if<is_nodes_iterator<Iterator>::value,
bool>::type operator!=(
  Iterator const & iterator_1,
  Iterator const & iterator_2 )
{
  return !(iterator_1 == iterator_2);
}

template <typename, typename>
class state;

template <
  typename Iterator,
  typename Traits = std::iterator_traits<Iterator>>
state<Iterator, Traits> root(
  Iterator const & external_begin,
  Iterator const & external_end )
{
  return state<Iterator, Traits>( external_begin, external_end );
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

  auto marked_1_index = std::distance(
    state_1.marked.internal,
    state_1.marked.internal_end );
  auto marked_2_index = std::distance(
    state_2.marked.internal,
    state_2.marked.internal_end );

  return (equal && marked_1_index == marked_2_index);
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

  auto marked_1_index = std::distance(
    state_1.marked.internal,
    state_1.marked.internal_end );
  auto marked_2_index = std::distance(
    state_2.marked.internal,
    state_2.marked.internal_end );

  return lexico || (equal &&
    marked_1_index < marked_2_index);
}

namespace std
{
  template <typename Iterator, typename Traits>
  class hash<state<Iterator, Traits>>
  {
  public:
    std::size_t operator()(
      const state<Iterator, Traits> & state ) const
    {
      typedef typename
        ::state<Iterator, Traits>::free_nodes_t free_nodes_t;

      return std::hash<free_nodes_t>()( state.free_nodes );
    }
  };
}

