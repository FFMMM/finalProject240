//David Brakman, Alexandru Pana, Nasheya Rahman

#include "Signal.h"
#include "DTW.h"
#include "PlotDTW.h"
#include <stdlib.h>

/*
Given two files, this class turns them into signals, gets the DTW part 
between those signals, and plots the DTW graph with the two signal graphs.
*/
int main(int argc, char* argv[]){
	if(argc != 3){
		cerr << "Need to enter input file names" << endl;
		exit(1);
	}
	
	//Construct the signals using the files
	Signal one(argv[1]);
	Signal two(argv[2]);
	
	DTW myDTW(one, two);
	
	PlotDTW myDTWPlot(myDTW);
	
	//Plot the DTW and the signals
	myDTWPlot.plot();
	
	return 0;
}
