#include "wgraph.hpp"
#include <math.h>
#include "priorityqueue.hpp"

template<size_t N>
class shortest_path_alg {
public:
	shortest_path_alg(wgraph<N> G);
        float path_size(size_t src, size_t dst);
	std::vector<size_t> path(size_t src, size_t dst);
private:
	wgraph<N> G;
	float d[N][N];
	std::vector<size_t> P[N][N];
        void set_distance(size_t i, size_t j, float x) {
		d[i][j] = d[j][i] = x;
	}
};

// https://math.libretexts.org/Bookshelves/Combinatorics_and_Discrete_Mathematics/Applied_Combinatorics_(Keller_and_Trotter)/12%3A_Graph_Algorithms/12.03%3A_Dijkstra%27s_Algorithm_for_Shortest_Paths
template<size_t N>
float shortest_path_alg<N>::path_size(size_t src, size_t dst)
{
	priorityqueue<size_t, float> temp;

        if (P[src][dst].size() && P[src][dst][0] == src &&
            P[src][dst].back() == dst) {
		return d[src][dst];
        }

        for (size_t x = 0; x < N; ++x) {
		// permanent nodes are those where the path is complete
                if (!P[src][x].size() ||
                    (P[src][x][0] != src && P[src][x].back() != x)) {
                        set_distance(src, x, G.weight(src, x));
                        temp.insert(x, d[src][x]);
                        P[src][x].push_back(src);
                }
        }
	while(temp.size()) {
		// temp.print();
		size_t i = temp.pop();
		// mark as permanent
		P[src][i].push_back(i);
		if (i == dst)
			return d[src][dst];
                for (size_t x: temp.as_list()) {
                        if (d[src][x] > d[src][i] + G.weight(i, x)) {
				set_distance(src, x, d[src][i] + G.weight(i, x));
				temp.change_priority(x, d[src][x]);
				P[src][x] = P[src][i];
                        }
                }
        }
	return d[src][dst];
}


template<size_t N>
shortest_path_alg<N>::shortest_path_alg(wgraph<N> G):G(G) {
	for (size_t i = 0; i < N; ++i)
		for (size_t j = 0; j < N; ++j)
			if (i == j)
				d[i][j] = 0;
			else
				d[i][j] = INFINITY;
}

template <size_t N>
std::vector<size_t> shortest_path_alg<N>::path(size_t src, size_t dst) {
	path_size(src, dst);
	return P[src][dst];
}
