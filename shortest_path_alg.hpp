#include "wgraph.hpp"
#include <math.h>
#include "priorityqueue.hpp"

// Implements the shortest path algorithm for graphs as described in
// https://math.libretexts.org/Bookshelves/Combinatorics_and_Discrete_Mathematics/Applied_Combinatorics_(Keller_and_Trotter)/12%3A_Graph_Algorithms/12.03%3A_Dijkstra%27s_Algorithm_for_Shortest_Paths
class shortest_path_alg {
public:
	explicit shortest_path_alg(wgraph G, size_t N);

        float path_size(size_t src, size_t dst);

	std::vector<size_t> path(size_t src, size_t dst);
private:
	int N;
	wgraph G;
	std::vector<std::vector<float>> d;
	std::vector<std::vector<std::vector<size_t>>> P;
        void set_distance(size_t i, size_t j, float x) {
		d[i][j] = d[j][i] = x;
	}
};
