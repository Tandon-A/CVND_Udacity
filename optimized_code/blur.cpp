#include "headers/blur.h"
#include "headers/zeros.h"

using namespace std;

// OPTIMIZATION: Pass large variable by reference
vector < vector <float> > blur(vector < vector < float> > &grid, float blurring) {

	// OPTIMIZATION: window, DX and  DY variables have the 
    // same value each time the function is run.
  	// It's very inefficient to recalculate the vectors
    // every time the function runs. 
    // 
    // The const and/or static operator could be useful.
  	// Define and declare window, DX, and DY using the
    // bracket syntax: vector<int> foo = {1, 2, 3, 4} 
    // instead of calculating these vectors with for loops 
    // and push back
  	vector < vector <float> > newGrid;

	int height;
	int width;
	float center, corner, adjacent;

	height = grid.size();
	width = grid[0].size();

	center = 1.0 - blurring;
	corner = blurring / 12.0;
	adjacent = blurring / 6.0;

  	
	vector < vector <float> > window = { {corner, adjacent, corner}, {adjacent, center, adjacent}, {corner, adjacent, corner} };


	vector <int> DX = {-1, 0, 1};
	vector <int> DY = {-1, 0, 1};  	


	// OPTIMIZATION: Use your improved zeros function
	newGrid = zeros(height,width);
  	int val, gval;
	for (int i=0; i< height; i++ ) {
		for (int j=0; j<width; j++ ) {
          	gval = grid[i][j];
			for (int ii=0; ii<3; ii++) {
              	val = (i +  DY[ii] + height) % height;
				for (int jj=0; jj<3; jj++) {
					newGrid[val][((j + DX[jj] + width) % width)] += gval * window[ii][jj];
				}
			}
		}
	}

	return newGrid;
}
