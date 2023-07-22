#include <vector> 
#include <iostream>
#include <random>
#include <iomanip>
#include <fstream>
#include <utility>


class wgraph {
public:
	wgraph(size_t N = 50, bool rand = false, float prob = 0.5, float low = 1.0, float high = 10);
	wgraph(std::string filename);

	void randomly_populate(float prob, float low = 1.0, float high = 10.0);

	void zero(); 

	// setters
	void set_edge(size_t i, size_t j, float x);

	// getter
	float weight(size_t i, size_t j);

	std::vector<size_t> neighbours(size_t x);

	void print();

	size_t size();

	std::vector<std::pair<size_t, size_t>> edges();
private:
	std::vector<std::pair<size_t, size_t>> edge_list;
	size_t N;
	size_t E;
	std::vector<std::vector<float>> matrix;
	bool rand = true;
};
