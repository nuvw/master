#include <map>

#include <boost/range/adaptor/map.hpp>
#include <boost/range/numeric.hpp>

#include "utility/console.hpp"

template <typename Node, typename Result>
template <typename Iterator>
algorithm<Node, Result>::algorithm(
  Iterator const & begin,
  Iterator const & end )
: nodes( nodes_arranger<algorithm>( begin, end ).arrange() )
{

}

template <typename Node, typename Result>
typename algorithm<Node, Result>::result_t
algorithm<Node, Result>::run() const
{
  typedef std::map<state_t, result_t> state_count_map_t;

  state_count_map_t state_count_map;
  state_count_map[root( nodes.begin(), nodes.end() )] = 1;

  for( std::size_t i = 0; 2*i < nodes.size(); i++ )
  {
    utility::console::write_line( "Iteration %1%", i );

    state_count_map_t new_state_count_map;

    for( auto& old_state_and_count : state_count_map )
    {
      auto new_states = successors( old_state_and_count.first );
      auto& count = old_state_and_count.second;

      for( auto& new_state : new_states )
      {
        new_state_count_map[std::move( new_state )] += count;
      }
    }

    state_count_map = std::move( new_state_count_map );
  }

  return boost::accumulate(
    state_count_map | boost::adaptors::map_values, 0 );
}

template <typename Node, typename Result>
typename algorithm<Node, Result>::successors_t
algorithm<Node, Result>::successors(
  state_t const & parent ) const
{
  successors_t result;

  auto const free_begin = parent.free_nodes_begin();
  auto const free_end = parent.free_nodes_end();
  auto const matched_begin = parent.matched_nodes_begin();
  auto const matched_end = parent.matched_nodes_end();
  auto const marked = parent.marked_node();

  for( auto lower_node = free_begin,
    previous_lower_node = free_end;
    lower_node != free_end && (marked == matched_end ||
    node_t::ascending( *lower_node, *marked ));
    previous_lower_node = lower_node++ )
  {
    if( previous_lower_node != free_end &&
      lower_node->y == previous_lower_node->y )
    {
      continue;
    }

    auto extreme_free = lower_node;
    auto extreme_matched = matched_end;
    auto matched_front = matched_begin;

    for( auto upper_node = lower_node;
      ++upper_node != free_end; )
    {
      if( extreme_free == lower_node ||
        node_t::strict_left_turn(
          *lower_node,
          *extreme_free,
          *upper_node ) )
      {
        extreme_free = upper_node;

        while( matched_front != matched_end && 
          node_t::ascending( *matched_front, *upper_node ) )
        {
          if( node_t::strict_ascending(
              *lower_node,
              *matched_front ) &&
            (extreme_matched == matched_end ||
            node_t::strict_right_turn(
              *lower_node, 
              *extreme_matched,
              *matched_front ) ) )
          {
            extreme_matched = matched_front;
          }

          ++matched_front;
        }

        if( extreme_matched == matched_end ||
          node_t::strict_right_turn(
            *lower_node,
            *extreme_matched,
            *upper_node ) )
        {
          result.push_back( parent.successor(
            lower_node,
            upper_node ) );
        }
        else
        {
          // TODO: Optimization. At this point lower_node can
          // be completely discarded because any later candidate
          // for upper_node will either have the same matched
          // nodes to the right, or the current upper_node to its
          // left.
        }
      }
    }
  }

  return std::move( result );
}

