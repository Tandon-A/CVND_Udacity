#include "headers/zeros.h"

using namespace std;

vector < vector <float> > zeros(int height, int width) {
	
	// OPTIMIZATION: Reserved space in memory for vectors
	vector < vector <float> > newGrid;
  	newGrid.reserve(height);
	vector <float> newRow; 
  	newRow.reserve(width);
  
  	for(vector < vector<float> >::iterator it=newGrid.begin(); it!=newGrid.end(); ++it)
    {
        it->reserve(width);
    }

  	// OPTIMIZATION: Not using nested for loops 
	for (int j=0; j<width; j++) 
    {
      newRow.push_back(0.0);
    }
  	for (int i=0;i<height;i++)
    {
		newGrid.push_back(newRow);
	}
	return newGrid;
}
