#include <vector> 
#include <iostream>
#include <random>
#include <iomanip>

template<size_t N>
class wgraph {
public:
	wgraph(bool rand = false, float prob = 0.5, float low = 1.0, float high = 10);

	void randomly_populate(float prob, float low = 1.0, float high = 10.0);

	void zero(); 

	// setters
	void set_edge(size_t i, size_t j, float x);

	// getter
	float weight(size_t i, size_t j);

	std::vector<size_t> neighbours(size_t x);

	void print();

	bool is_connected();
private:
	float matrix[N][N];
	bool connected_run = false;
	bool connected = false;
};

template<size_t N>
wgraph<N>::wgraph(bool rand, float prob, float low, float high) {
	if (rand)
		randomly_populate(prob, low, high);
	else
		zero();
}

template<size_t N> 
bool wgraph<N>::is_connected() {
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

template <size_t N>
void wgraph<N>::randomly_populate(float prob, float low, float high)
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



template<size_t N>
void wgraph<N>::zero() {
	for (size_t i = 0; i < N; ++i)
		for (size_t j = 0; j < N; ++j)
			if (i == j)
				matrix[i][j] = 0;
			else
				matrix[i][j] = INFINITY;
}

// setters
template<size_t N>
void wgraph<N>::set_edge(size_t i, size_t j, float x) {
	if (i >= N || j >= N || i < 0 || j < 0) {
		std::cout<<"Indices out of bounds. This is a graph of N vertices.\n";
		std::exit(1);
	}
	matrix[i][j] = x;
	matrix[j][i] = x;
	connected_run = false;
}

// getter
template<size_t N>
float wgraph<N>::weight(size_t i, size_t j) {
	if (i >= N || j >= N || i < 0 || j < 0) {
		std::cout<<"Indices out of bounds. This is a graph of N vertices.\n";
		std::exit(1);
	}
	return matrix[i][j];
}

template<size_t N>
std::vector<size_t> wgraph<N>::neighbours(size_t x) {
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

template<size_t N>
void wgraph<N>::print() {
	for (size_t i = 0; i < N; ++i) {
		for (size_t j = 0; j < N; ++j)
			std::cout<<std::fixed
				 <<std::setprecision(1)
				 <<matrix[i][j]<<" ";
		std::cout<<std::endl;
	}
}
