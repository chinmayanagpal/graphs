#include "kruskal.hpp"
#include "priorityqueue.hpp"
#include <utility>
#include <algorithm>
#include <functional>

typedef std::pair<size_t, size_t> edge;

Kruskal::Kruskal(wgraph G): G(G) {}

wgraph Kruskal::MST()
{
	size_t N = G.size();
	wgraph T(N);
	weight = 0;

	// priorityqueue of all edges
	priorityqueue<edge, float> edges;
	for (size_t i = 0; i < N; ++i)
		for (size_t j = i + 1; j < N; ++j) 
			if (G.weight(i, j) != INFINITY)
				edges.insert({i, j}, G.weight(i, j));

	std::vector<size_t> comp(N);
	size_t i = 0;
	for (size_t i = 0; i < N; ++i)
		comp[i] = i;

	size_t nedges = 0;
	while(nedges < N - 2) {
		// edges.print();
		edge e = edges.pop();
		if (comp[e.first] != comp[e.second]) {
			size_t s = comp[e.second];
			for (size_t& i: comp)
				if (i == s)
					i = comp[e.first];
			T.set_edge(e.first, e.second, G.weight(e.first, e.second));
			weight += G.weight(e.first, e.second);
			nedges++;
		}
	}
	return T;
}

float Kruskal::get_weight()
{
	float w;
	wgraph T = MST();
	for(size_t i = 0; i < T.size(); ++i)
		for(size_t j = i + 1 ; j < T.size(); ++j)
			if (T.weight(i, j) != INFINITY) {
				w += T.weight(i, j);
				if (G.weight(i, j) != T.weight(i, j))
					std::abort();
			}
	return w;
}
