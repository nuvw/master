#ifndef GGC_DECL_STATE_FWD_HPP
#define GGC_DECL_STATE_FWD_HPP

#include <iterator>
#include <ostream>
#include <type_traits>

template <
  typename Iterator,
  typename Traits = std::iterator_traits<Iterator>>
class state;

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
  Iterator const & iterator_2 );

template <typename Iterator>
typename std::enable_if<is_nodes_iterator<Iterator>::value,
bool>::type operator!=(
  Iterator const & iterator_1,
  Iterator const & iterator_2 );

template <
  typename Iterator,
  typename Traits = std::iterator_traits<Iterator>>
state<Iterator, Traits> root(
  Iterator const & external_begin,
  Iterator const & external_end );

template <typename Iterator, typename Traits>
std::ostream & operator<<(
  std::ostream & ostream,
  state<Iterator, Traits> const & state );

template <typename Iterator, typename Traits>
bool operator==(
  state<Iterator, Traits> const & state_1,
  state<Iterator, Traits> const & state_2 );

template <typename Iterator, typename Traits>
bool operator<(
  state<Iterator, Traits> const & state_1,
  state<Iterator, Traits> const & state_2 );

namespace std
{
  template <typename Iterator, typename Traits>
  struct hash<state<Iterator, Traits>>;
}

#endif

