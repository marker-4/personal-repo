#include <iostream>

#include "algorithm2.h"

using namespace std;


int main(){
	



	cout << "**TESTING NUM SHORTEST PATHS MATRIX**\n\n";	
	
	int** test = new int*[3];
	for (int i = 0; i < 3; i++) {
		test[i] = new int[3];
	}


	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			test[i][j] = 1;
		}
	}

	test[1][1] = 0;

	cout << "Testing on this array" << endl;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << test[i][j] << " ";
		}
		cout << endl;
	}
	std::pair<int, int> dorm{0,0};
	std::pair<int, int> algo{2,2};

	cout << "This array has " << numShortest(test, dorm, algo, 3, 3) << " possible shortest paths..." << endl;

	for (int i = 0; i < 3; i++) {
            delete[] test[i];
    }

	delete[] test;
	
	return 0;
}