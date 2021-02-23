#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include <random>
#include "priorityQueue.h"
#include <typeinfo>

using namespace std;

int bincoeff(int N, int R)
{
	// Calc N/1*(N-1)/2*(N-2)/3*... for quicker computation
	// rather than using factorials
	if (R == 0)
	{
		return 1;
	}

	int out = 1;
	for (int i = 1; i <= R; i++)
	{
		out *= N - i + 1;
		out /= i;
	}

	return out;

}

struct edge {
	int index;
	int dist = 10000000;
	struct edge *next;
};

void prims(vector<vector<float>> nodes, int points) {
	vector<int> dist(points, 10000000);
	vector<bool> visited(points, false);
	PriorityQueue H(points);
	edge s;
	int tot_edge = 0;
	s.dist = 0;
	s.index = 0;
	dist[s.index] = 0;
	H.add(s);
	vector<int> path(points);

	// NOT WORKING - NEED TO CHANGE PRIORITY QUEUE
	// TO TAKE STRUCT 'EDGE'
	for (int i = 0; i < points || H.empty(); ++i) {
		edge v;
		v = H.deletemin();

		for (int k = 0; k < points; ++k) {
			if (visited[k] != true) {
				edge w;
				w.index = k;

				int vw = get_distance(nodes[v.index], nodes[k]);
				if (w.dist > vw) {
					w.dist = vw;
					dist[k] = vw;
					H.add(w);
				}
			}
		}

		visited[v.index] = true;
		tot_edge += v.dist;
	
	}

}

float get_distance(vector<float> point1, vector<float> point2, bool use_sqrt = false) {
	float sum = 0;
	for (int i = 0; i < point1.size(); ++i)
		sum += (point1[i] - point2[i])*(point1[i] - point2[i]);
	if (use_sqrt)
		return sqrt(sum);
	return sum;
}

int main() // int& test, int& numpoints, int& numtrials, int& dimension)
{
	// Init variables
	int points;
	int numtrials;
	int dimensions;

	// Init random device and seed
	random_device rd;
	mt19937 gen(rd());
	// Gen uniform dist between 0, 1
	uniform_real_distribution<> dis(0, 1);


	// For quick testing
	cout << "Enter number of points:";
	cin >> points;

	cout << "Enter number of trials:";
	cin >> numtrials;

	cout << "Enter dimension:";
	cin >> dimensions;


	std::vector<int> graph(bincoeff(points, 2));
	std::vector<int> coords(dimensions);

	// Iterate and generate coordinates
	vector<vector<float>> nodes(points);
	int dim = 0;
	if (dimensions == 0) {
		dim = 1;
	}
	for (int i = 0; i < points; i++) {
		vector<float> new_point(dimensions);
		nodes.push_back(new_point);
		for (int j = 0; j < dimensions+dim; j++) {
			nodes[i].push_back(dis(gen)); //.back().push_back(dis(gen));//dis(gen));
		}
		
	}

	// For testing - print out nodes to make sure distance is correct
	for (int i = 0; i < points; i++) {
		for (auto it = nodes[i].begin(); it != nodes[i].end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}

	// Just an example to make sure dist is correct
	cout << "Dist:" << endl;
	cout << get_distance(nodes[0], nodes[1], true);

	return 0;
}
