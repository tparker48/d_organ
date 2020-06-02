#pragma once
#include "MCP3008.h"
#include <thread>

// The PotReader Clas ("Potentiometer Reader") is tasked with keeping track of the potentiometer values
// This will be done concurrently, IE the potentiometer values will be updated on a regular interval while the DSP code is running
// In the DSP code we often need to check Potentiometer values, and this class will make that very simple.
class PotReader
{
public:
	PotReader();
	~PotReader();

	//starts the new thread which updates the pot values
	void start();

	// Get the raw integer value [0-1024]
	int read(int mcp, int pot);

	// Get the value as a float [0.0-1.0]
	float readNormalized(int mcp, int pot);

	// Get the value as a float [0.0-1.0] as if the pot were logarithmic
	// The pots we are using are all linear
	// Usefull for things like filter frequency cutoff ETC
	float readLogarithmic(int mcp, int pot);

private:
	// potValues is frequently read from and written to
	// because of the application, no synchronization is required
	int potValues[8*4];
	std::thread* updater;
	bool killThread;
};

void updateValues(int *vals, bool *killSignal);
int getIndex(int mcp, int pot);
