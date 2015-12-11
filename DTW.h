#ifndef __DTW_H__
#define __DTW_H__
#include <vector>
#include "Signal.h"

using namespace std;

class DTW
{
	public:
		// Constructor takes in two Singnal instances and initializes its own private Signal fields.
		DTW(Signal signalA, Signal signalB); 

		// Default Constructor
		DTW();

		// Copy constructor.
		DTW(const DTW& copy);

		~DTW(){}; //Default destructor
		// Method returns a vector containing the comparison between the two signals.
		struct Coord
		{
			int x;
			int y;
		};

		vector<Coord> getComparison();

		// Accessors to query the Signal fields of the existing DTW class instance
		Signal getFirst() const;
		Signal getSecond() const;
		
		// Mutators to easily modify signals that need to be compared. Obviously, a call to any one of these methods requires the comparsion to be performed again.
		void setFirst(Signal signalA);
		void setSecond(Signal signalB);
		//overload the equals operators in Signal class?

		void compare(); // method compares SignalA to SignalB

	private:
		Signal mySignalA; //instances of the Signal class initialized in the constructor or modified through provided mutators
		Signal mySignalB;
		bool myCompared; // boolean variable that establishes if comparison has to be made between the signals before returning the myComparison vector
		vector<Coord> myComparison; // vector that holds the result of the comparison between  the two Signals.
		void initiateDTW(); // method calls on the data forwarding algorithm
		double DTWDistance(vector<double> first, vector<double> second, int windowSize); // method performs the DTW and updates the myComparison vector.

};

#endif 
