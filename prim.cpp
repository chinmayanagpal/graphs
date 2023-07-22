#include "prim.hpp" 
#include "priorityqueue.hpp"
#include <algorithm>
#include <iostream>

typedef std::pair<size_t, size_t> edge;

Prim::Prim(wgraph G) : G(G) {}

// returns a minimum spanning tree using Prim's algorithm: initialise the tree
// with a single (supplied) vertex at each step, consider the vertices already
// in the tree. all vertices immediately adjacent to these vertices are called
// the temporary vertices, and these are stored in a priorityqueue. the priority
// of a temporary vertex is given by the smallest edge weight of an edge that
// connects the current tree to the vertex. the other node of this edge is
// stored in an array. at each step, the highest priority vertex is removed from
// the priorityqueue, and the edge with min weight connecting it to the tree is
// added to the tree. the new temporary nodes are inserted into the
// priorityqueue, and the priorities of the others are updated if necessary.
// this is performed until there are N-1 edges.
wgraph Prim::MST(size_t root)
{
	weight = 0;
	int N = G.size();
	wgraph T(N);

	// priority queue of nodes to add, along with weight
	// which is decreased every time an edge to the node
	// is discovered with lower weight
	priorityqueue<size_t, float> tempq;
	// stores the other node in the edge associated with each node in tempq
	std::vector<size_t> first(N);

	// stores which nodes are already in the tree
	std::vector<bool> perm(N);
	std::fill(perm.begin(), perm.end(), false);

	// store whether tempq contains a certain node faster than the
	// tempq.contains() method, which has complexity O(tempq.size)
	std::vector<bool> temp(N);
	std::fill(temp.begin(), temp.end(), false);

	size_t p = root;
	do {
		// mark the most recently popped off vertex as permanent as well
		// as non-temporary
		perm[p] = true;
		temp[p] = false;
		for(size_t x: G.neighbours(p)) {
			// don't add vertices already in T to the temporary
			// vertices
			if (!perm[x]) {
				// if x is not temporary, then set it as
				// temporary
				// and if it is temporary but there is a shorter
				// edge available to connect it to T, then
				// update its priority and the vertex in T that
				// is closest to it
				if (!temp[x]) {
					tempq.insert(x, G.weight(x, p));
					temp[x] = true;
					first[x] = p;
				} else if (tempq.priority(x) > G.weight(x, p)) {
					tempq.change_priority(x, G.weight(x, p));
					first[x] = p;
				}
			}
		}
		// pop off the closest node
		p = tempq.pop();
		// and add to T the shortest edge from T to p 
		T.set_edge(first[p], p, G.weight(first[p], p));
		// increase the total weight of T by the weight of the edge just
		// added
		weight += G.weight(first[p], p);
	} while (tempq.size());

	return T;
}

float Prim::get_weight()
{
	float w;
	wgraph T = MST();
	for(size_t i = 0; i < T.size(); ++i)
		for(size_t j = i + 1 ; j < T.size(); ++j)
			if (T.weight(i, j) != INFINITY)
				w += T.weight(i, j);
	return w;
}
