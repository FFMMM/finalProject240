#include <iostream>
#include "DummySignal.h"
#include "DummyDTW.h"
#include "PlotDTW.h"

int main(int argc, char* argv[])
{

//	Testing Dummy Classes
/*
	DummySignal sigA;
	std::vector<double> vecA = sigA.getData();
	std::cout<<"Printing signalA data: "<<std::endl;
	for(int i=0; i < vecA.size(); i++)
	{
		std::cout<<"vecA["<<i<<"] = "<<vecA[i]<<std::endl;
	}
	DummySignal sigB;

	DummyDTW aDTW(sigA, sigB);
	std::vector<double> vecC = aDTW.getComparison();
	std::cout<<"Printing signalC data: "<<std::endl;
	for(int i=0; i < vecC.size(); i++)
	{
		std::cout<<"vecC["<<i<<"] = "<<vecC[i]<<std::endl;
	}

	PlotDTW aPlot;
	std::cout<<"Finished the stubTester successfully"<<std::endl;	
*/


//	Testing the PlotDTW class

	QApplication a(argc, argv);
//	Default Constructor
	std::cout<<"Test 3: Testing  Default Constructor of plotDTW"<<std::endl;
	
	PlotDTW w;
	w.show();

	return a.exec();
}
