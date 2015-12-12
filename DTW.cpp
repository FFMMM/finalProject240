#include "DTW.h"
#include "Signal.h"
#include <iostream>
#include <cmath> // for the absolute function
#include <algorithm> // for the max function
#include <cfloat> //for DBL_MAX
#include <limits.h>
#include <climits>

using namespace std;

DTW::DTW(Signal signalA, Signal signalB)
// Constructor takes in two Signal instances and initializes its own private Signal fields.	
{
	mySignalA = signalA;
	mySignalB = signalB;
	myCompared = false; // these Signals have not been compared

}

DTW::DTW()
//Default Constructor
{
	myCompared = false;
	/*Implicitly call default constructors for mySigA, B*/
}

DTW::DTW(const DTW& copy)
// Copy constructor
{
	this->myCompared = copy.myCompared;
	this->myComparison = copy.myComparison;
	this->setFirst(copy.getFirst());
	this->setSecond(copy.getSecond());
}

vector<DTW::Coord> DTW::getComparison()
// Method returns a vector containing the comparison between the two signals.
{
	if(myCompared == false)
		compare();
	return myComparison;
} 

Signal DTW::getFirst() const
// Accessor returns SignalA
{
	return mySignalA;
}

Signal DTW::getSecond() const
// Accessor returns SignalB
{
	return mySignalB;
}

void DTW::setFirst(Signal signalA)
// Mutator modifies the first comparison signal
{
	myCompared = false;
	mySignalA = signalA;
}

void DTW::setSecond(Signal signalB)
// Mutator modifies the second comparison signal
{
	myCompared = false;
	mySignalB = signalB;
}


double DTW::compare()
// Method compares SignalA to SignalB
{
	double res = 0;
	if(getFirst() == getSecond())
	{
		//Do nothing else but:
		for(int i=0; i< getFirst().getData().size(); i++)
		{
			myComparison.push_back(Coord());
			myComparison[i].x = i;
			myComparison[i].y = i;
			res = 0;
		}
	}
	else
	{
		res = initiateDTW();
	}
	myCompared = true;
	return res;
}

// ------------- Public Interface Ends -----------------------

double DTW::initiateDTW()
// method calls on the data forwarding algorithm
{	
	// we want to add a locality constraint
	int windowSize = abs((int)(mySignalA.getData().size() - mySignalB.getData().size()));
	return DTWDistance(mySignalA.getData(), mySignalB.getData(), windowSize);
}

double DTW::DTWDistance(vector<double> first, vector<double> second, int windowSize)
// method builds the cost matrix, finds minimizing path,
// and returns total distance between signals
{
	int first_size = first.size();
	int second_size = second.size();
	//double myDTW[first_size+1][second_size+1];
	//Allocating this array on the stack doesn't seem to work. Not enough mem.
	//Stackoverflow said to do it on the heap or do a vector, so here goes.
	vector< vector<double> > myDTW(first_size, vector<double>(second_size, DBL_MAX)); 

	windowSize = max(windowSize, abs(first_size - second_size));

	// intializing all entries to the most "expensive" path possible
	for(int i = 0; i < first_size; i++)
	{
	    for(int j = 0; j < second_size; j++)
	    {
		myDTW[i][j] = DBL_MAX;
	    }
	}
	myDTW[0][0] = 0;

	double cost = 0; 

	for(int i = 1; i < first_size; i++)
	{
	    for(int j = max(1, (i-windowSize) ); j < min(second_size, (i + windowSize)); j++)
	    {
		cost = abs(first.at(i) - second.at(i));
		myDTW[i][j] = cost + min(myDTW[i-1][j], min(myDTW[i][j-1], myDTW[i-1][j-1])); //where the minimum compares the inseration, deletion and match cases
	    }
	}

//This material added by David B. -----
	//Backtrack from upper right-hand corner
	int i = first_size - 1;
	int j = second_size - 1;
	while (i > 0 && j > 0)
	{
	    myComparison.push_back(Coord());
	    myComparison.back().x = i;
	    myComparison.back().y = j;
	    if (i==0)
	    {
		--j;
	    }
	    else if (j==0)
	    {	
		--i;
	    }
	    else
	    {
		if (myDTW[i-1][j] == min(min(myDTW[i-1][j], myDTW[i-1][j-1]), myDTW[i][j-1]))
		{
	  	    --i;
		}
		else if (myDTW[i-1][j-1] == min(min(myDTW[i-1][j], myDTW[i-1][j-1]), myDTW[i][j-1]))
		{
		    --i;
		    --j;
		}
		else
		{
		    --j;
		}
	    }
	}
	myComparison.push_back(Coord());
	myComparison.back().x = 0;
	myComparison.back().y = 0;
//End David B. addition -----
	return myDTW[first_size-1][second_size-1];
}
