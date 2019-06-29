#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <list>
#include <sstream>
#include <set>
using namespace std;

/*
Used this input as a test:
	 4 5
	0 2 10
	1 0 1
	0 3 5
	3 1 1
	2 3 4
 *
 */

int number_of_nodes;
int number_of_edges;

//Each pair is (destination node, weight of edge)
vector<list<pair<int, int>>> adj_list(number_of_nodes);

//Returns degree of node n
int find_degree(int n, vector<list<pair<int, int>>> adj_list);
int dijkstra(int source, int destination);

int main() {

	cin >> number_of_nodes;
	cin >> number_of_edges;


	//INPUT PART
	for (int i = 0; i < number_of_edges; i++)
	{
		int node;
		int target;
		int weight;
		cin >> node >> target >> weight;

		adj_list[node].push_back(make_pair(target, weight));
		adj_list[target].push_back(make_pair(node, weight));
	}
	//END OF INPUT PART


	//JUST AN EXAMPLE OF ACCESSING THE ADJACENCY LIST!, CAN BE OMITTED
	for (int i = 0; i < number_of_nodes; i++)
	{
		for (list<pair<int, int>>::iterator j = adj_list[i].begin(); j != adj_list[i].end(); j++)
		{
			cout << "Node:" << i << ", Target: " << j->first << ", Weight: " << j->second << endl;
		}
	}
	//END OF EXAMPLE


	//JUST AN EXAMPLE OF FINDING THE DEGREES OF NODES
	for (int i = 0; i < number_of_nodes; i++)
	{
		cout << "degree of " << i << " = " << find_degree(i, adj_list) << endl;
	}
	//END OF EXAMPLE

	return 0;
}


//Returns degree of node n
int find_degree(int n, vector<list<pair<int, int>>> adj_list)
{
	return adj_list[n].size();
}

int closeness_centrality(int n, vector<list<pair<int, int>>> adj_list) {
	long sum = 0;
	
		for (int j = 0; j < number_of_nodes; j++)
		{

			sum += dijkstra(n, j);
		}

	return (double (number_of_nodes-1) / sum);
}

int dijkstra(int source, int destination) {
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