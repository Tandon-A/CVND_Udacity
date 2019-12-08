#include "headers/initialize_beliefs.h"

using namespace std;

// OPTIMIZATION: Large variables passed by reference
vector< vector <float> > initialize_beliefs(vector< vector <char> > &grid) {

  	vector< vector <float> > newGrid;
	vector<float> newRow;
	int height, width;
	float prob_per_cell;

	height = grid.size();
	width = grid[0].size();
 	// OPTIMIZATION: Reserving space for vectors 
  	newGrid.reserve(height);
  	newRow.reserve(width);
  
  	for(vector < vector<float> >::iterator it=newGrid.begin(); it!=newGrid.end(); ++it)
    {
        it->reserve(width);
    }
  	prob_per_cell = 1.0 / ( (float) height*width) ;

  	// OPTIMIZATION: Making the newGrid matrix without nested for loops
	for (int i=0; i<width; i++) 
    {
		newRow.push_back(prob_per_cell);
	}
  	for (int i=0; i<height;i++)
    {
      	newGrid.push_back(newRow);
    }
	return newGrid;
}
