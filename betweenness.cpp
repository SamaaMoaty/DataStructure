#include <iostream>
#include <vector>
#include <iterator>
#include <list>
#include <sstream>
#include <set>
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <iomanip>
#include <stack>

using namespace std;
typedef std::numeric_limits< double > dbl;
int number_of_nodes;
int number_of_edges;

volatile unsigned int repeated ;

int dijkstra(int source, int destination, vector<list<pair<int, int>>> &adj_list);


int main() {
	cout.precision(dbl::max_digits10);

	cin >> number_of_nodes;
	cin >> number_of_edges;

	stack <int> s;

	vector<list<pair<int, int>>> adj_list(number_of_nodes);
	/*NUMBER OF SHORTEST PATHS MATRIX*/
	vector<vector<int>> num_short_paths (number_of_nodes,vector<int>(number_of_nodes));
	/*MATRIX CONTAINING LIST OF ALL INTERMEDIATE NODES*/
	vector<vector<list<int>>> intermediate(number_of_nodes,vector<list<int>>(number_of_nodes));
	/*USER INPUT*/
	for (int i = 0; i < number_of_edges; i++)
	{
		int node;
		int target;
		int weight;
		cin >> node >> target >> weight;

		adj_list[node].push_back(make_pair(target, weight));
		adj_list[target].push_back(make_pair(node, weight));
	}
	/*END OF INPUT*/
	/*INIT SHORTEST PATH MATRIX*/
	for (int i = 0; i < number_of_nodes; i++) {
		for (int j = i + 1; j < number_of_nodes; j++)      num_short_paths[i][j] = 0;
	}

	int flag1 = 0, flag2 = 0;


		for (int i = 0; i < number_of_nodes-1; i++) {
			for (int j = i + 1; j < number_of_nodes; j++) {
				for (list<pair<int, int>> ::iterator it = adj_list[i].begin(); it != adj_list[i].end(); it++) 
					if (it->first == j && it->second == dijkstra(i, j, adj_list)) {
						num_short_paths[i][j]++;
						break;
					}
			}
		}
	/*FIND INTERMEDIATE NODES AND PUT THEM IN INTERMEDIATE MATRIX AND GET NUMBER OF SHORTEST PATHS BETWEEN EACH TWO NODES*/
	for (int node = 0; node < number_of_nodes; node++){
		for (int i = 0; i < number_of_nodes-1; i++) {
			if (node != i){
				for (int j = i + 1; j < number_of_nodes; j++){
					if (j != node){
						if ((dijkstra(i, node, adj_list) + dijkstra(node, j, adj_list)) == dijkstra(i, j, adj_list)) {
							for (list<pair<int, int>> ::iterator it = adj_list[i].begin(); it != adj_list[i].end(); it++) {
								if (node == it->first && it->second == dijkstra(i,it->first,adj_list)) {
									flag1 = 1;
									break;
								}
							}
							for (list<pair<int, int>> ::iterator it = adj_list[j].begin(); it != adj_list[j].end(); it++) {
								if (node == it->first && it->second == dijkstra(j,it->first,adj_list)) {
									flag2 = 1;
									break;
								}

							}
							if (flag1 &&flag2) {/*3 NODES ONE ONLY INTERMEDIATE*/
								intermediate[i][j].push_back(node);
								num_short_paths[i][j]++;
								flag1 = 0;
								flag2 = 0;
							}
							else if (flag1) {/*4 OR MORE NODES*/
								for (list<pair<int, int>> ::iterator it = adj_list[node].begin(); it != adj_list[node].end(); it++) {
									{
										int fff = 0;
										if ((dijkstra(i, it->first, adj_list) + dijkstra(it->first, j, adj_list) == dijkstra(i, j, adj_list)) && it->first != j && it->first != i) {
											list<pair<int, int>> ::iterator itr = adj_list[it->first].begin();
											while (itr != adj_list[it->first].end() )
											{
												if (itr->first == j)
												{
													fff = 1;
													break;
												}
												itr++;
											}
											if (fff == 1) {/*four nodes*/
												fff = 0;
												intermediate[i][j].push_back(node);
												num_short_paths[i][j]++;
											}
											else { /*more than 4 so check repetition of node*/
												for (list<pair<int, int>> ::iterator itt = adj_list[it->first].begin(); itt != adj_list[it->first].end(); itt++) {

													if (itt->second + dijkstra(itt->first, j, adj_list) == dijkstra(it->first, j, adj_list))
													{

														intermediate[i][j].push_back(node);
														intermediate[i][j].push_back(it->first);
														num_short_paths[i][j]++;

													}
												}
											}
										}
										flag1 = 0;
									}
								}
							}
							else if (flag2) {
								for (list<pair<int, int>> ::iterator it = adj_list[node].begin(); it != adj_list[node].end(); it++) {
									{
										int fff = 0;
										if ((dijkstra(i, it->first, adj_list) + dijkstra(it->first, j, adj_list) == dijkstra(i, j, adj_list)) && it->first != j && it->first != i) {
											list<pair<int, int>> ::iterator itr = adj_list[it->first].begin();
											while (itr != adj_list[it->first].end())
											{
												if (itr->first == i)
												{
													fff = 1;
													break;
												}
												itr++;
											}
											if (fff == 1) {/*four nodes*/
												fff = 0;
												intermediate[i][j].push_back(node);
												
											}
											else { /*more than 4 so check repetition of node*/
												for (list<pair<int, int>> ::iterator itt = adj_list[it->first].begin(); itt != adj_list[it->first].end(); itt++) {
													
													if (itt->second + dijkstra(itt->first, i, adj_list) == dijkstra(it->first, i, adj_list))
													{
														intermediate[i][j].push_back(node);
													}
												}
											}
										}
										flag2 = 0;
									}
									}
							}

						}

					}
				}

			}
		}
	}
	
	
	double *between;
	between = new double[number_of_nodes];
	repeated = 0;
	/*INIT OF BETWEENEES ARRAY*/
	for (int i = 0; i < number_of_nodes; i++) {
		between[i] = 0;
	}
	
	for (int node = 0; node < number_of_nodes; node++) {
		for (int i = 0; i < number_of_nodes-1; i++) {
			if (node != i) {
				for (int j = i + 1; j < number_of_nodes; j++) {
					if (node != j) {
							for (list<int> ::iterator it = intermediate[i][j].begin(); it != intermediate[i][j].end(); it++) {
							if (node == *it)				repeated++;
							}
							if (num_short_paths[i][j] > 0) 	between[node] += (double)(repeated) / (double)(num_short_paths[i][j]);
							repeated = 0;
					}
				}
			}
		}
	}
	/*PRINTING THE ARRAY*/
	for (int i = 0; i < number_of_nodes; i++) {
		cout  << fixed << setprecision(12) <<  between[i] << "\n";
	}
	
}

int dijkstra(int source, int destination, vector<list<pair<int, int>>> &adj_list) {
	vector <int> cost(number_of_edges + 9, -1);
	set<pair<int, int>> s;
	s.insert({ 0,source }); // <cost of reaching the node , node>

	while (!s.empty()) {
		pair<int, int> p = *(s.begin()); // top of priority queue but with least cost
		s.erase(p); // pop
		int node = p.second, nodecost = p.first;
		if (cost[node] != -1) continue; //node was out from the queue before with lower cost 
		cost[node] = nodecost;
		for (pair<int, int> edge : adj_list[node]) if (cost[edge.first] == -1)
		{
			s.insert({ nodecost + edge.second, edge.first }); // cost of reaching current node + edge to neighbor , neighbor
		}
	}
	if (cost[destination] == -1) return -1;
	else return cost[destination];
}

