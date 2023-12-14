#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Define a structure to represent an edge in the graph
struct Edge {
int src, dest, weight;
};

// Define a structure to represent a disjoint set
struct DisjointSet {
int *parent, *rank;
int n;

DisjointSet(int n) {
    	this->n = n;
    	parent = new int[n];
    	rank = new int[n];

    	// Initialize each set to have a single element with rank 0
    	for (int i = 0; i < n; i++) {
        	parent[i] = i;
        	rank[i] = 0;
    	}
}

// Find the set to which an element belongs (with path compression)
int find(int u) {
    	if (u != parent[u])
        	parent[u] = find(parent[u]);
    	return parent[u];
}

// Union of two sets (with union by rank)
void Union(int x, int y) {
    	int rootX = find(x);
    	int rootY = find(y);

    	if (rank[rootX] < rank[rootY])
        	parent[rootX] = rootY;
    	else if (rank[rootX] > rank[rootY])
        	parent[rootY] = rootX;
    	else {
        	parent[rootY] = rootX;
        	rank[rootX]++;
    	}
}
};

// Comparator function to sort edges based on their weights
bool compareEdges(Edge a, Edge b) {
return a.weight < b.weight;
}

// Kruskal's algorithm to find minimum spanning tree
void kruskal(vector<Edge>& edges, int V) {
// Sort the edges in ascending order of their weights
sort(edges.begin(), edges.end(), compareEdges);

// Create a disjoint set to keep track of connected components
DisjointSet ds(V);

// Initialize an empty vector to store the minimum spanning tree
vector<Edge> MST;

// Process each edge in sorted order
for (Edge edge : edges) {
    	int srcSet = ds.find(edge.src);
    	int destSet = ds.find(edge.dest);

    	// If including this edge does not create a cycle, add it to the MST
    	if (srcSet != destSet) {
        	MST.push_back(edge);
        	ds.Union(srcSet, destSet);
    	}
}

// Print the minimum spanning tree
cout << endl << "Minimum Spanning Tree:" << endl;
for (Edge edge : MST) {
    	cout << edge.src << " - " << edge.dest << ", Weight: " << edge.weight << endl;
}
}

int main() {
int V = 4;  // Number of vertices
vector<Edge> edges = {
    	{0, 1, 10},
    	{0, 2, 6},
    	{0, 3, 5},
    	{1, 3, 15},---
    	{2, 3, 4}
};

cout << "Edges in the vector:" << endl;
for (const Edge& edge : edges) {
  	cout << edge.src << " - " << edge.dest << ", Weight: " << edge.weight << endl;
}

kruskal(edges, V);

return 0;
}
