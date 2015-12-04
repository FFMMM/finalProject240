#include "DummySignal.h"

DummySignal::DummySignal(char* filename)
{
	value = genSignal();
}

DummySignal::DummySignal()
{
	value = genSignal();
}

DummySignal::~DummySignal()
{
}

std::vector<double> DummySignal::getData()
{
	return value;
}

std::vector<double> DummySignal::genSignal()
{
	std::vector<double> res;
	for(int i=0; i<1200; i++)
	{
		res.push_back(.2 + .8*i*i/(1200*1200));
	}
	for(int i=0; i<1200; i++)
	{
		res.push_back(.8 - .8*i*i/(1200*1200));
	}
	return res;
}
