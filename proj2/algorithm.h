#ifndef ALGORITHM
#define ALGORITHM

#include <iostream>
#include <utility>
#include <queue>

class AdjacencyMatrix{
	// class to represent the adjacency matrix of a weighted, directed graph

public:
    int V;					//number of nodes in the graph
    int** adjMatrix;		//adjacency matrix of a graph


	AdjacencyMatrix(int numVertices){
		// Constructor: takes a number of vertices in the graph, and constructs the adjacency matrix of the graph with no edges (all entries are 0)
		// Nodes are numbered 0, 1, 2, ..., numVertices-1
		V = numVertices;

		// set up adjacency matrix, as an array of arrays. 
		// Dimensions of the matrix are numVertices by numVertices.
		// adjMatrix[i][j] will be 0 if there is no edge from j to i, and will be the weight if there is such an edge.
		// all values in matrix are initialized to 0. Edges will be filled in later.
		adjMatrix = new int*[V];	
		for (int i = 0; i < V; i++){
			adjMatrix[i] = new int[V]();
		}
	}

	AdjacencyMatrix(const AdjacencyMatrix* other){
		// Constructor: takes another adjacency matrix, and makes a clone (deep copy) of it
		// Nodes are numbered 0, 1, 2, ..., numVertices-1
		V = other->V;

		// set up adjacency matrix, as an array of arrays. 
		// Dimensions of the matrix are numVertices by numVertices.
		// adjMatrix[i][j] will be 0 if there is no edge from j to i, and will be the weight if there is such an edge.
		// all values in matrix are initialized to 0. Edges will be filled in later.
		adjMatrix = new int*[V];	
		for (int i = 0; i < V; i++){
			adjMatrix[i] = new int[V]();
		}

		// copy all entries from other.AdjMatrix into the new adjacency matrix for this graph
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++){
				adjMatrix[i][j] = other->adjMatrix[i][j];
			}
		}
	}

    bool validCoord(AdjacencyMatrix& grid, std::pair<int, int> point, int n, int m) { //take in a coord pair and tell if it is unvisited, not a building, and in range
        int x = point.first;
        int y = point.second;

        if (x < 0 || y < 0  || x > m || y > n) {
            return false;
        }

        if (grid.adjMatrix[y][x] == 0) {
            return false;
        }

        return true;
    }

    int numShortest(AdjacencyMatrix& grid, std::pair<int, int> dorm, std::pair<int, int> algo, int n, int m) {
        std::queue<std::pair<int, int>> to_visit;

        bool found = false;
        int** num_ways;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                num_ways[i][j] = 0;
            }
        }
        int dormx = dorm.first;
        int dormy = dorm.second;
        num_ways[dormy][dormx] = 1;

        to_visit.push(dorm);
        while (!found && !to_visit.empty()) {
            std::pair<int, int> curr = to_visit.front();
            to_visit.pop();

            int currx = curr.first;
            int curry = curr.second;
            std::cout << "Current is: " << currx << ", " << curry << std::endl;

            grid.adjMatrix[curry][currx] = 0; //mark this point as visited
            std::pair<int, int> neighbor;
            
            // TEST ALL NEIGHBOR CASES
            neighbor.first = currx + 1;
            neighbor.second = curry;
            if (validCoord(grid, neighbor, n, m)) { // if neighbor is in range, and unvisited, and does not represent a blocked pathway
                int nx = neighbor.first;
                int ny = neighbor.second;
                num_ways[ny][nx] += num_ways[curry][currx];
                if (neighbor == algo) {
                    found = true;
                } else {
                    to_visit.push(neighbor);
                }
            }

            neighbor.first = currx;
            neighbor.second = curry + 1;
            if (validCoord(grid, neighbor, n, m)) { // if neighbor is in range, and unvisited, and does not represent a blocked pathway
                int nx = neighbor.first;
                int ny = neighbor.second;
                num_ways[ny][nx] += num_ways[curry][currx];
                if (neighbor == algo) {
                    found = true;
                } else {
                    to_visit.push(neighbor);
                }
            }

            neighbor.first = currx - 1;
            neighbor.second = curry;
            if (validCoord(grid, neighbor, n, m)) { // if neighbor is in range, and unvisited, and does not represent a blocked pathway
                int nx = neighbor.first;
                int ny = neighbor.second;
                num_ways[ny][nx] += num_ways[curry][currx];
                if (neighbor == algo) {
                    found = true;
                } else {
                    to_visit.push(neighbor);
                }
            }

            neighbor.first = currx;
            neighbor.second = curry - 1;
            if (validCoord(grid, neighbor, n, m)) { // if neighbor is in range, and unvisited, and does not represent a blocked pathway
                int nx = neighbor.first;
                int ny = neighbor.second;
                num_ways[ny][nx] += num_ways[curry][currx];
                if (neighbor == algo) {
                    found = true;
                } else {
                    to_visit.push(neighbor);
                }
            }
            // END NEIGHBOR CASES

        }
        // deal with any remaining values in queue after algo is found

        while (!to_visit.empty()) {
            std::pair<int, int> curr = to_visit.front();
            to_visit.pop();

            int currx = curr.first;
            int curry = curr.second;

            // TEST ALL NEIGHBOR CASES
            std::pair<int, int> neighbor;
            neighbor.first = currx + 1;
            neighbor.second = curry;
            if (neighbor == algo) {
                int nx = neighbor.first;
                int ny = neighbor.second;
                num_ways[ny][nx] += num_ways[curry][currx];
            }

            neighbor.first = currx;
            neighbor.second = curry + 1;
            
            if (neighbor == algo) {
                int nx = neighbor.first;
                int ny = neighbor.second;
                num_ways[ny][nx] += num_ways[curry][currx];
            }

            neighbor.first = currx - 1;
            neighbor.second = curry;
            
            if (neighbor == algo) {
                int nx = neighbor.first;
                int ny = neighbor.second;
                num_ways[ny][nx] += num_ways[curry][currx];
            }

            neighbor.first = currx;
            neighbor.second = curry - 1;
            
            if (neighbor == algo) {
                int nx = neighbor.first;
                int ny = neighbor.second;
                num_ways[ny][nx] += num_ways[curry][currx];
            }
            // END NEIGHBOR CASES
        }

        int algox = algo.first;
        int algoy = algo.second;

        return num_ways[algoy][algox];
    }

	~AdjacencyMatrix(){
		// This is the destructor. It deletes the dynamically allocated arrays, so that we don't have memory leaks.
		for (int i = 0; i < V; i++){
			delete[] adjMatrix[i];		//delete every row
		}
		delete[] adjMatrix;				//delete the array of rows
	}
};

#endif