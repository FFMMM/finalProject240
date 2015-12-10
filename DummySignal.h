#ifndef DummySignal_H
#define DummySignal_H

#include <vector>

class DummySignal
{
	private:
		std::vector<double> value;

	public:
		DummySignal(char* filename);
		DummySignal();
		~DummySignal();
		std::vector<double> getData();
		static std::vector<double> genSignal();
};

#endif // DummySignal_H
