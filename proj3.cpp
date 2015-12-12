#include <QApplication>
#include <iostream>
#include "PlotDTW.h"

using namespace std;

int main(int argc, char *argv[])
{
// Step 1) Validate Input
    /*
    Signal* querySigPtr;
    Signal* refSigPtr;
     //OK, let's not use pointers. See if that fixes it. 
   */
 
  /*if(argc != 3)
    {
	cout << "Usage: " << argv[0] << " path/to/querySignal " <<
		" path/to/referenceSignal" << endl;
	exit(1);
    }*/ //Turned off for gdb 
/*
    try
    {
	querySigPtr = new Signal(argv[1]);
    }
    catch(invalid_argument& ia)
    {
	cout << "Usage: " << argv[0] << " path/to/querySignal " <<
		" path/to/referenceSignal" << endl;
	cout << "Error: querySignal data in " << argv[1] <<
		" could not be read." << endl;
	exit(1);
    }
    try
    {
	refSigPtr = new Signal(argv[2]);
    }
    catch(invalid_argument& ia)
    {
	cout << "Usage: " << argv[0] << " path/to/querySignal " <<
		" path/to/referenceSignal" << endl;
	cout << "Error: referenceSignal data in " << argv[2] <<
		" could not be read." << endl;
	exit(1);
    }   


    cout << "Testing signal construction: " << endl;
    cout << "refSig[54] = " << refSigPtr->getData().at(54) << endl; 
*/

    Signal querySig(argv[1]);
    Signal refSig(argv[2]);

//  Step 2) Construct DTW
    //DTW aDTW(*querySigPtr, *refSigPtr);
    DTW aDTW(querySig, refSig);
    cout << "Testing DTW construction: " << endl;
    cout << "aDTW.getSecond().getData().at(54) = " <<
		aDTW.getSecond().getData().at(54) << endl;

//  Step 3) Tell the DTW to compare signals
    aDTW.compare();
    cout << "Testing the DTW comparison: " << endl;
    cout << "aDTW.getComparison().at(54).x = " << 
		aDTW.getComparison().at(54).x << endl;

//  Step 4) Construct a PlotDTW
    QApplication a(argc, argv);
    cout << "We made a QApplication" << endl;
    PlotDTW w;
    cout << "We constructed the PlotDTW" << endl;
//  Step 5) Pass the DTW to it
    w.setDTW(aDTW);

//  Step 6) Draw the display  
    w.show();

 /*  delete querySigPtr;
    delete refSigPtr; */

    return a.exec();
}
