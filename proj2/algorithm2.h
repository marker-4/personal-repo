#ifndef ALGORITHM2
#define ALGORITHM2

#include <iostream>
#include <utility>
#include <queue>


using namespace std;

bool validCoord(int** grid, std::pair<int, int> point, int n, int m) { //take in a coord pair and tell if it is unvisited, not a building, and in range
    int x = point.first;
    int y = point.second;

    if (x < 0 || y < 0  || x > m || y > n) {
        return false;
    }

    if (grid[y][x] == 0) {
        return false;
    }

    return true;
}

int numShortest(int** grid, std::pair<int, int> dorm, std::pair<int, int> algo, int n, int m) {
    std::queue<std::pair<int, int>> to_visit;

    bool found = false;
    int num_ways[n][m];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            num_ways[i][j] = 0;
        }
    }
    
    int dormx = dorm.first;
    int dormy = dorm.second;

    num_ways[dormy][dormx] = 1;

//TROUBLESHOOTING
    cout << endl;

    cout << "CURRRENT STATUS OF GRID" << endl;
    for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << grid[i][j] << " ";
		}
        cout << endl;
	}
    cout << "CURRENT STATUS OF NUMWAYS" << endl;

    for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << num_ways[i][j] << " ";
		}
		cout << endl;
	}
//TROUBLESHOOTING STOP


    to_visit.push(dorm);

    while (!found && !to_visit.empty()) {
        std::pair<int, int> curr = to_visit.front();
        to_visit.pop();

        int currx = curr.first;
        int curry = curr.second;

        grid[curry][currx] = 0; //mark this point as visited
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
//TROUBLESHOOT
    cout << "CURRRENT STATUS OF GRID" << endl;
    for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << grid[i][j] << " ";
		}
        cout << endl;
	}
    cout << "CURRENT STATUS OF NUMWAYS" << endl;

    for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << num_ways[i][j] << " ";
		}
		cout << endl;
	}
//TROUBLESHOOT ENDS
    }
    // deal with any remaining values in queue after algo is found
    cout << "How about here\n";
    while (!to_visit.empty()) {
        cout << "Still here?\n";
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


#endif