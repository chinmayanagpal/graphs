#include "wgraph.hpp"

class Kruskal {
private:
	wgraph G;
	float weight = 0;
public:
	Kruskal(wgraph G);
	wgraph MST();
	float get_weight();
};
