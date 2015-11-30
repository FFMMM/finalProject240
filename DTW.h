#ifndef __DTW_H__
#define __DTW_H__
#include <vector>


class DTW
{
	private:
		Signal mySignalA;
		Signal mySignalB;
		bool myCompared;
		vector<double> myComparison;
	public:
		DTW(Signal signalA, Signal signalB);
		vector<double> getComparison();
		Signal getFirst();
		Signal getSecond();
		void setFirst(Signal signalA);
		void setSecond(Signal signalB);
};

#endif 
