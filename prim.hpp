#include "wgraph.hpp"

class Prim {
private:
	wgraph G;
	float weight = 0;
public:
	Prim(wgraph G);
	wgraph MST(size_t src = 0);
	float get_weight();
};
