#include "headers/move.h"
#include "headers/zeros.h"

using namespace std;

// OPTIMIZATION: Pass large variable by reference
vector< vector <float> > move(int dy, int dx, 
	vector < vector <float> > &beliefs) 
{
	int height, width;
	height = beliefs.size();
	width = beliefs[0].size();

	vector < vector <float> > newGrid = zeros(height, width);

// OPTIMIZATION: Eliminate any variables that aren't needed
	int new_i;
	
  	for (int i=0; i<height; i++) 
    {
      new_i = (i + dy + height) % height;		
      for (int j=0; j<width; j++) 
      {
		newGrid[new_i][((j + dx + width)  % width)] = beliefs[i][j];
	  }
	}
	return newGrid;
}
