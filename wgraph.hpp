#include <vector> 
#include <iostream>
#include <random>
#include <iomanip>
#include <fstream>

class wgraph {
public:
	wgraph(int N = 50, bool rand = false, float prob = 0.5, float low = 1.0, float high = 10);
	wgraph(std::string filename);

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
	int N;
	std::vector<std::vector<float>> matrix;
	bool connected_run = false;
	bool connected = false;
	bool rand = true;
};
