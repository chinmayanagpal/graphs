#include "shortest_path_alg.hpp"

shortest_path_alg::shortest_path_alg(wgraph G, size_t N) :
	N(N), G(G), d(N, std::vector<float>(N)),
	P(N, std::vector<std::vector<size_t>>(N))
{
	for (size_t i = 0; i < N; ++i)
		for (size_t j = 0; j < N; ++j)
			if (i == j)
				d[i][j] = 0;
			else
				d[i][j] = INFINITY;
}

float shortest_path_alg::path_size(size_t src, size_t dst)
{
	// permanent nodes are those where the path is complete
	priorityqueue<size_t, float> temp;

        if (P[src][dst].size() && P[src][dst][0] == src &&
            P[src][dst].back() == dst) {
		return d[src][dst];
        }

        for (size_t x = 0; x < N; ++x) {
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

std::vector<size_t> shortest_path_alg::path(size_t src, size_t dst) {
	path_size(src, dst);
	return P[src][dst];
}
