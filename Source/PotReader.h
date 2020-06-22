#pragma once
#include <thread>

// The PotReader Clas ("Potentiometer Reader") is tasked with keeping track of the potentiometer values
// This will be done concurrently, IE the potentiometer values will be updated on a regular interval while the DSP code is running
// In the DSP code we often need to check Potentiometer values, and this class will make that very simple.
class PotReader
{
public:
	// Must be called before reading
	void start(bool isMockReader);
	void stop();

	// Get the raw integer value [0-1023]
	int read(int mcp, int pot);

	// Get the value as a float [0.0-1.0]
	float readNormalized(int mcp, int pot);

	// Get the value as a float [0.0-1.0] on a logarithmic scale
	float readLogarithmic(int mcp, int pot);

private:
	int potValues[4*8];
	bool killThread, isMockReader;
	std::thread* updater;
};

void updateValues(int *vals, bool *killSignal);
void initializeMockValues(int* vals);
int getIndex(int mcp, int pot);