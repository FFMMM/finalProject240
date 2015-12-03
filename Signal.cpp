#include "Signal.h"

//Given a filename, constructs a signal that is normalized and concatenated
Signal::Signal(string filename)
{
	vector< vector<double> > input;
	vector< vector<double> > data;

	ifstream inFile(filename.c_str());

	//Make sure file is good
	if(!inFile){
		throw invalid_argument("Failed to open file.");
	} else {
		double val = 0;
		int i = 0;
		vector<double> tempInput;

		//Reading the values from the file
		while(!inFile.eof())
		{
			inFile >> val;
			tempInput.push_back(val);

			if(i==NUM_DATA_VALS-1) {
				input.push_back(tempInput);
				tempInput.clear();
				i = 0;
			} else {
				i++;
			}
		}

		inFile.close();

		//Taking all the input data and grouping it within its own type
		for(unsigned int i=0; i<input.at(0).size(); i++)
		{
			vector<double> temp;

			for(unsigned int j=0; j<input.size(); j++){
				temp.push_back(input.at(j).at(i));
			}

			data.push_back(temp);
		}

		normalize(data);
		concatenate(data);
	}
}


//Copy Constructor
Signal::Signal(const Signal& copy)
{
	signalData = copy.signalData;
}


//Gives you the data for a given Signal
vector<double> Signal::getSignalData()
{
	return signalData;
}


//Normalizes the signal data
void Signal::normalize(vector< vector<double> >& data)
{	
	for(unsigned int k=0; k<data.size(); k++){
		double sum = 0;
		
		//Find the min and max
		for(unsigned int i=0; i<data.at(0).size(); i++){
			sum+=pow(data[k][i], 2);
		}
		
		double length = sqrt(sum);
		
		//Normalize all the elements
		for(unsigned int i=0; i<data.at(0).size(); i++){
			if(length!=0)
				data[k][i] = data[k][i]/length;
		}
	}
}


//Concatenates all the signal data, making the final single vector
void Signal::concatenate(vector< vector<double> >& data)
{
	for(unsigned int i=0; i<data.size(); i++){
		for(unsigned int k=0; k<data.at(0).size(); k++){
			signalData.push_back(data[i][k]);
		}
	}
}


//Given two signals, determines if they are equal to each other.
bool Signal::operator==(const Signal& other) const
{
	if(other.signalData.size()!=this->signalData.size()){
		return false;
	} else {
		for(unsigned int i=0; i<other.signalData.size(); i++){
			if(other.signalData[i]!=this->signalData[i])
				return false;
		}
		
		return true;
	}
}


//Given two signals, determines if they are not equal to each other.
bool Signal::operator!=(const Signal& other) const
{
	if(*this==other){
		return false;
	}
	
	return true;
}
