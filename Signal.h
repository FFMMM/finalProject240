#ifndef __SIGNAL_H__
#define __SIGNAL_H__

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <float.h>
#include <math.h>
#include <stdexcept>

using namespace std;

//Constructs a signal entity
class Signal
{
	private:
		//Represents the number of values for one signal in one line
		const static int NUM_DATA_VALS = 17;

		//Holds the final signal data, concatenated and normalized
		vector<double> signalData;

		//Normalizes the signal data
		void normalize(vector< vector<double> >& data);

		//Concatenates all the signal data, making the final single vector
		void concatenate(vector< vector<double> >& data);

	public:
		//Default constructor
		Signal(){};
		
		//Given a filename, constructs a signal that is normalized and concatenated
		//If file cannot be open, throws an invalid argument exception.
		Signal(string filename);

		//Copy constructor
		Signal(const Signal& copy);
		
		//Given two signals, determines if they are equal to each other.
		bool operator==(const Signal& other) const;
		
		//Given two signals, determines if they are not equal to each other.
		bool operator!=(const Signal& other) const;
		
		//Destructor
		~Signal(){};

		//Gives you the data for a given Signal
		vector<double> getSignalData();
};

#endif
