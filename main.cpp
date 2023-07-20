#include "shortest_path_algo.hpp"

int main() {
	wgraph<9> G;
        G.set_edge(0, 1, 4);
        G.set_edge(0, 7, 8);
        G.set_edge(1, 7, 11);
        G.set_edge(1, 2, 8);
        G.set_edge(7, 8, 7);
        G.set_edge(2, 8, 2);
        G.set_edge(6, 8, 6);
        G.set_edge(7, 6, 1);
        G.set_edge(2, 5, 4);
        G.set_edge(6, 5, 2);
        G.set_edge(2, 3, 7);
        G.set_edge(3, 5, 14);
        G.set_edge(3, 4, 9);
        G.set_edge(5, 4, 10);
        shortest_path_alg<9> d(G);
	std::vector<size_t> u = d.path(0, 2);
	for (size_t i: u)
		std::cout<<i<<" ";
	std::cout<<std::endl;
}
