#ifndef __DTW_H__
#define __DTW_H__
#include <vector>
#include "Signal.h"

using namespace std;

class DTW
{
	private:
		Signal mySignalA; //instances of the Signal class initialized in the constructor or modified through provided mutators
		Signal mySignalB;
		bool myCompared; // boolean variable that establishes if comparison has to be made between the signals before returning the myComparison vector
		vector<double> myComparison; // vector that holds the result of the comparison between  the two Signals.
		void compare(); // method compares SignalA to SignalB
		void initiateDTW(); // method calls on the data forwarding algorithm
		double DTWDistance(); // method performs the DTW and updates the myComparison vector.
	public:
		// Constructor takes in two Singnal instances and initializes its own private Signal fields.
		DTW(Signal signalA, Signal signalB); 

		~DTW(){}; //Default destructor
		// Method returns a vector containing the comparison between the two signals.
		vector<double> getComparison();

		// Accessors to query the Signal fields of the existing DTW class instance
		Signal getFirst();
		Signal getSecond();
		
		// Mutators to easily modify signals that need to be compared. Obviously, a call to any one of these methods requires the comparsion to be performed again.
		void setFirst(Signal signalA);
		void setSecond(Signal signalB);
		//overload the equals operators in Signal class?
};

#endif 
