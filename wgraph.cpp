#include "wgraph.hpp"

wgraph::wgraph(int N, bool rand, float prob, float low, float high): N(N), matrix(N, std::vector<float>(N)) {
	if (rand)
		randomly_populate(prob, low, high);
	else
		zero();
}

bool wgraph::is_connected() {
	if (connected_run)
		return connected;

	size_t queue[N];

	// initially place the node 0 in the queue
	// and set the size to 1
	queue[0] = 0; 
	size_t  queue_size = 1;
	size_t queue_pos = 0;

	// visited[n] is true if the node n has been visited
	bool visited[N];
	visited[0] = true;

	while (queue_pos < queue_size) {
		//current node
		size_t curr = queue[queue_pos];
		for (size_t i = 0; i < N; ++i)
			// Add i to the queue and mark it as visited: there is
			// an edge between the current node and i has not
			// already been visited.
			if (matrix[curr][i] > 0 && !visited[i]) {
				visited[i] = true;
				queue[queue_size++] = i;
				if (queue_size == N) {
					connected_run = true;
					connected = true;
					return true;
				}
			}
		queue_pos++;
	}
	connected_run = true;
	connected = false;
	return false;
}

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



void wgraph::zero() {
	for (size_t i = 0; i < N; ++i)
		for (size_t j = 0; j < N; ++j)
			if (i == j)
				matrix[i][j] = 0;
			else
				matrix[i][j] = INFINITY;
}

// setters
void wgraph::set_edge(size_t i, size_t j, float x) {
	if (i >= N || j >= N || i < 0 || j < 0) {
		std::cout<<"Indices out of bounds. This is a graph of N vertices.\n";
		std::exit(1);
	}
	matrix[i][j] = x;
	matrix[j][i] = x;
	connected_run = false;
}

// getter
float wgraph::weight(size_t i, size_t j) {
	if (i >= N || j >= N || i < 0 || j < 0) {
		std::cout<<"Indices out of bounds. This is a graph of N vertices.\n";
		std::exit(1);
	}
	return matrix[i][j];
}

std::vector<size_t> wgraph::neighbours(size_t x) {
	if (x >= N || x < 0) {
		std::cout<<"Index out of bounds. This is a graph of N vertices.\n";
		std::exit(1);
	}
	std::vector<size_t> ne;
	for (size_t i = 0; i < N; ++i)
		if (weight(x, i))
			ne.push_back(i);
	return ne;
}

void wgraph::print() {
	for (size_t i = 0; i < N; ++i) {
		for (size_t j = 0; j < N; ++j)
			std::cout<<std::fixed
				 <<std::setprecision(1)
				 <<matrix[i][j]<<" ";
		std::cout<<std::endl;
	}
}

wgraph::wgraph(std::string filename) {
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
