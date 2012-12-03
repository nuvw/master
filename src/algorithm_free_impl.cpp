#include <algorithm>

template <typename Algorithm>
class nodes_arranger
{
private:
  typedef typename Algorithm::node_t node_t;
  typedef typename Algorithm::nodes_t nodes_t;
public:
  template <typename Iterator>
  nodes_arranger( Iterator const & begin, Iterator const & end );
public:
  nodes_t arrange();
private:
  nodes_t nodes;
};

template <typename Algorithm>
template <typename Iterator>
nodes_arranger<Algorithm>::nodes_arranger(
  Iterator const & begin,
  Iterator const & end )
: nodes( begin, end )
{

}

template <typename Algorithm>
typename nodes_arranger<Algorithm>::nodes_t
nodes_arranger<Algorithm>::arrange()
{
  struct {
    bool operator()(
      node_t const & node_1,
      node_t const & node_2 )
    {
      return node_1.y < node_2.y ||
        (node_1.y == node_2.y && node_1.x < node_2.x);
    }
  } strict_total_order_relation;

  struct {
    bool operator()(
      node_t const & node_1,
      node_t const & node_2 )
    {
      return node_1.x == node_2.x && node_1.y == node_2.y;
    }
  } equivalence_relation;

  std::sort( nodes.begin(), nodes.end(),
    strict_total_order_relation );
  auto unique_end = std::unique( nodes.begin(), nodes.end(),
    equivalence_relation );
  nodes.erase( unique_end, nodes.end() );

  return std::move( nodes );
}

