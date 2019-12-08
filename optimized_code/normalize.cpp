#include "headers/normalize.h"
using namespace std;

// OPTIMIZATION: Pass variable by reference
vector< vector<float> > normalize(vector< vector <float> > &grid) {

  	// OPTIMIZATION: Avoid declaring and defining 				// intermediate variables that are not needed.
	float total = 0.0;
  	int width = grid[0].size();
  	int height = grid.size();
	for (int i = 0; i < height; i++)
	{
		for (int j=0; j< width; j++)
		{
			total += grid[i][j];
		}
	}

	for (int i = 0; i < height; i++) 
    {
		for (int j=0; j< width; j++) 
        {
			grid[i][j] = grid[i][j] / total;
		}
	}

	return grid;
}
