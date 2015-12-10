#include "DTW.h"
#include "Signal.h"
#include <iostream>
#include <cmath> // for the absolute function
#include <algorithm> // for the max function
#include <float.h>
#include <limits.h>
#include <climits>

DTW::DTW(Signal signalA, Signal signalB)
// Constructor takes in two Signal instances and initializes its own private Signal fields.	
{
	mySignalA = signalA;
	mySignalB = signalB;
	myCompared = false; // these Signals have not been compared

}

DTW::DTW(const DTW& copy)
// Copy constructor
{
	this->myCompared = copy.myCompared;
	this->myComparison = copy.myComparison;
	this->setFirst(copy.getFirst());
	this->setSecond(copy.getSecond());
}

vector<double> DTW::getComparison()
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

// ------------- Public Interface Ends -----------------------

void DTW::compare()
// Method compares SignalA to SignalB
{
	if(getFirst() == getSecond())
	{
		//Do nothing else but:
		myCompared = true;
		myComparison = mySignalA.getSignalData();
	}
	else
	{ 
		initiateDTW();
	}

}

void DTW::initiateDTW()
// method calls on the data forwarding algorithm
{	
	// we want to add a locality constraint
	int windowSize = abs((int)(mySignalA.getSignalData().size() - mySignalB.getSignalData().size()));

	DTWDistance(mySignalA.getSignalData(), mySignalB.getSignalData(), windowSize);
}

double DTW::DTWDistance(vector<double> first, vector<double> second, int windowSize)
// method performs the DTW and updates the myComparison vector
{
	double myDTW[first.size()+1][second.size()+1];

	int first_size = first.size();
	int second_size = second.size();

	windowSize = max(windowSize, abs(first_size - second_size));

	// intializing all entries to the most "expensive" path possible
	for(int i = 0; i < first_size; i++)
		for(int j = 0; j < second_size; j++)
			myDTW[i][j] = DBL_MAX;

	myDTW[0][0] = 0;
	myComparison.push_back(myDTW[0][0]);

	double cost = 0; 

	for(int i = 1; i < first_size; i++)
		for(int j = max(1, (i-windowSize) ); j < min(second_size, (i + windowSize)); j++)
		{
			cost = abs(first.at(i) - second.at(i));

			myDTW[i][j] = cost + min(myDTW[i-1][j], min(myDTW[i][j-1], myDTW[i-1][j-1])); //where the minimum compares the inseration, deletion and match cases
			myComparison.push_back(myDTW[i][j]);
		}

	return myDTW[first.size()][second.size()];
}
