#ifndef DummyDTW_H
#define DummyDTW_H

#include <vector>
#include "DummySignal.h"

class DummyDTW
{
	private:
		DummySignal mySignalA;
		DummySignal mySignalB;
		std::vector<double> myComparison;
	public:
		DummyDTW();
		DummyDTW(DummySignal signalA, DummySignal signalB);
		~DummyDTW();
		std::vector<double> getComparison();
		DummySignal getFirst();
		DummySignal getSecond();
};

#endif // DummyDTW_H
