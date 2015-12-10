#include "DummyDTW.h"

DummyDTW::DummyDTW(DummySignal signalA, DummySignal signalB)
{
	mySignalA = signalA;
	mySignalB = signalB;
	myComparison = DummySignal::genSignal();
}

DummyDTW::DummyDTW()
{
	myComparison = DummySignal::genSignal();
}

DummyDTW::~DummyDTW()
{
}

std::vector<double> DummyDTW::getComparison()
{
	return myComparison;
}

DummySignal DummyDTW::getFirst()
{
	return mySignalA;
}

DummySignal DummyDTW::getSecond()
{
	return mySignalB;
}
