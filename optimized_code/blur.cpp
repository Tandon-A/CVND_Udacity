#include "headers/blur.h"
#include "headers/zeros.h"

using namespace std;

// OPTIMIZATION: Large variables passed by reference
vector < vector <float> > blur(vector < vector < float> > &grid, float blurring) {

  	vector < vector <float> > newGrid;

	int height;
	int width;
	float center, corner, adjacent;

	height = grid.size();
	width = grid[0].size();

	center = 1.0 - blurring;
	corner = blurring / 12.0;
	adjacent = blurring / 6.0;

	// OPTIMIZATION: Loop to initialize arrays removed.   	
	vector < vector <float> > window = { {corner, adjacent, corner}, {adjacent, center, adjacent}, {corner, adjacent, corner} };
	vector <int> DX = {-1, 0, 1};
	vector <int> DY = {-1, 0, 1};  	


	// OPTIMIZATION: Using improved zeros function
	newGrid = zeros(height,width);
  	int val, gval;
	for (int i=0; i< height; i++ ) {
		for (int j=0; j<width; j++ ) {
		// OPTIMIZATION: Defining gval variable which will remain constant for below two for loops	
          	gval = grid[i][j];
			for (int ii=0; ii<3; ii++) {
              	val = (i +  DY[ii] + height) % height;
				for (int jj=0; jj<3; jj++) {
					// OPTIMIZATION: Not storing values in different variables 
					newGrid[val][((j + DX[jj] + width) % width)] += gval * window[ii][jj];
				}
			}
		}
	}

	return newGrid;
}
