#include "wgraph.hpp"

// Initialises a graph of size N. If rand is true, then the adjacency matrix is
// random generated where each non-loop edge has a chance 0.0 < prob < 1.0 of
// occuring and the weight is randomly assigned a value between low and high
// based on a uniform distribution of reals. If rand is false, a discrete graph
// is initialised
wgraph::wgraph(size_t N, bool rand, float prob, float low, float high): N(N), matrix(N, std::vector<float>(N))
{
	if (rand)
		randomly_populate(prob, low, high);
	else
		zero();
}

// returns the number of vertices in the wgraph
size_t wgraph::size()
{
	return N;
}

// returns the list of edges in the wgraph
std::vector<std::pair<size_t, size_t>> wgraph::edges()
{
	if (edge_list.size())
		return edge_list;

	else
		for (size_t i = 0; i < N; ++i)
			for(size_t j = i; j < N; ++j)
				if (matrix[i][j] != 0.0 && matrix[i][j] != INFINITY)
					edge_list.push_back(std::pair<size_t, size_t>(i, j));
	return edge_list;
}

// randomly populates the graph as described in the comment above the
// constructor
void wgraph::randomly_populate(float prob, float low, float high)
{
	std::random_device rd;
	std::default_random_engine gen(rd());
	std::uniform_real_distribution<> wdist(low, high);
	std::bernoulli_distribution dist(prob);

	for (size_t i = 0; i < N; ++i) 
		for (size_t j = 0; j <= i; ++j) 
			if (j == i || !dist(gen))
				set_edge(i, j, INFINITY);
			else 
				set_edge(i, j, wdist(gen));
}

// deletes all edges (graph is discrete)
void wgraph::zero()
{
	for (size_t i = 0; i < N; ++i)
		for (size_t j = 0; j < N; ++j)
			if (i == j)
				matrix[i][j] = 0;
			else
				matrix[i][j] = INFINITY;
	E = 0;
}

// assigns edge (i, j) the weight x
void wgraph::set_edge(size_t i, size_t j, float x)
{
	if (i >= N || j >= N || i < 0 || j < 0) {
		std::cout<<"Indices out of bounds. This is a graph of N vertices.\n";
		std::abort();
	}

	if (x == INFINITY && matrix[i][j] != INFINITY)
		E++;
	else if (x == INFINITY && matrix[i][j] != INFINITY)
		E--;

	matrix[i][j] = x;
	matrix[j][i] = x;
}

// getter
float wgraph::weight(size_t i, size_t j)
{
	if (i >= N || j >= N || i < 0 || j < 0) {
		std::cout<<"Indices out of bounds. This is a graph of N vertices.\n";
		std::abort();
	}
	return matrix[i][j];
}

// returns the list of vertices which share an edge with x
std::vector<size_t> wgraph::neighbours(size_t x)
{
	if (x >= N || x < 0) {
		std::cout<<"Index out of bounds. This is a graph of N vertices.\n";
		std::abort();
	}
	std::vector<size_t> ne;
	for (size_t i = 0; i < N; ++i)
		if (weight(x, i))
			ne.push_back(i);
	return ne;
}

// prints the graph (awfully)
void wgraph::print()
{
	for (size_t i = 0; i < N; ++i) {
		for (size_t j = 0; j < N; ++j)
			std::cout<<std::fixed
				 <<std::setprecision(1)
				 <<matrix[i][j]<<" ";
		std::cout<<std::endl;
	}
}

// Initialises the graph using a file of the following format:
// Line 1: number of vertices in graph
// Line 2: node1 node2 weight
// Line 3: node1 node2 weight
wgraph::wgraph(std::string filename)
{
	std::ifstream file(filename);
	file >> this->N;
	matrix.resize(N);
	for (auto &row: matrix)
		row.resize(N);
	zero();
	int i, j, weight;
	while(file >> i) {
		file >> j;
		file >> weight;
		set_edge(i, j, weight);
	}
}
