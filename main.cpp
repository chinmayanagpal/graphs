#include "shortest_path_alg.hpp"
#include <string>

int main(int argc, char* argv[]) {

	// float prob;
	// try {
	// 	prob = std::stof(argv[1]);
	// } catch (...) {
	// 	prob = 0.2;
	// }

	// float avgavg = 0;
	// for (int j = 0; j < 100; ++j) {
	// 	wgraph G(50, true, prob, 1.0, 10.0);
	// 	shortest_path_alg<50> sp(G);
	// 	double avg = 0;
	// 	int edges = 0;
	// 	for (int i = 1; i < 50; ++i)
	// 	{
	// 		float size = sp.path_size(0, i); 
	// 		if (sp.path_size(0, i) != INFINITY) {
	// 			avg += size;
	// 			edges++;
	// 		}
	// 	}
	// 	avg /= edges;
	// 	avgavg += avg;
	// }
	// avgavg /= 100;
	// std::cout<<avgavg<<std::endl;
	wgraph G("testdata.txt");
	G.print();
}
