#include "PotReader.h"
#include <thread>
#include <iostream>
#include <unistd.h>      //only works on the PI itself (UNIX)

	PotReader::PotReader()
	{
		killThread = false;
	}

	PotReader::~PotReader()
	{
		killThread = true;
		updater->join();
	}

	void PotReader::start()
	{
		updater = new std::thread(updateValues, potValues, &killThread);
	}

	int PotReader::read(int mcp, int pot)
	{
		return potValues[getIndex(mcp, pot)];
	}


	float PotReader::readNormalized(int mcp, int pot)
	{
		return ((float)potValues[getIndex(mcp, pot)])/1024.0;
	}


	float PotReader::readLogarithmic(int mcp, int pot)
	{
		// FINISH THIS
		return 0.0;
	}


	void updateValues(int *vals, bool* killSignal)
	{
		JUCE_GPIO::MCP3008 mcp;
		while (!(*killSignal))
		{
			vals[getIndex(0, 0)] = mcp.mcp3008_value(0, 11, 9, 10, 8);
			vals[getIndex(0, 1)] = mcp.mcp3008_value(1, 11, 9, 10, 8);
			vals[getIndex(0, 2)] = mcp.mcp3008_value(2, 11, 9, 10, 8);
			vals[getIndex(0, 3)] = mcp.mcp3008_value(3, 11, 9, 10, 8);
			//vals[getIndex(0,4)] = mcp.mcp3008_value(4, 11, 9, 10, 8);
			//vals[getIndex(0,5)] = mcp.mcp3008_value(5, 11, 9, 10, 8);
			//vals[getIndex(0,6)] = mcp.mcp3008_value(6, 11, 9, 10, 8);
			//vals[getIndex(0,7)] = mcp.mcp3008_value(7, 11, 9, 10, 8);

			vals[getIndex(1, 0)] = mcp.mcp3008_value(0, 11, 9, 10, 23);
			vals[getIndex(1, 1)] = mcp.mcp3008_value(1, 11, 9, 10, 23);
			vals[getIndex(1, 2)] = mcp.mcp3008_value(2, 11, 9, 10, 23);
			vals[getIndex(1, 3)] = mcp.mcp3008_value(3, 11, 9, 10, 23);
			vals[getIndex(1, 4)] = mcp.mcp3008_value(4, 11, 9, 10, 23);
			vals[getIndex(1, 5)] = mcp.mcp3008_value(5, 11, 9, 10, 23);
			vals[getIndex(1, 6)] = mcp.mcp3008_value(6, 11, 9, 10, 23);
			vals[getIndex(1, 7)] = mcp.mcp3008_value(7, 11, 9, 10, 23);

			vals[getIndex(1, 0)] = mcp.mcp3008_value(0, 11, 9, 10, 25);
			vals[getIndex(1, 1)] = mcp.mcp3008_value(1, 11, 9, 10, 25);
			vals[getIndex(1, 2)] = mcp.mcp3008_value(2, 11, 9, 10, 25);
			vals[getIndex(1, 3)] = mcp.mcp3008_value(3, 11, 9, 10, 25);
			vals[getIndex(1, 4)] = mcp.mcp3008_value(4, 11, 9, 10, 25);
			vals[getIndex(1, 5)] = mcp.mcp3008_value(5, 11, 9, 10, 25);
			vals[getIndex(1, 6)] = mcp.mcp3008_value(6, 11, 9, 10, 25);
			vals[getIndex(1, 7)] = mcp.mcp3008_value(7, 11, 9, 10, 25);

			//vals[getIndex(1, 0)] = mcp.mcp3008_value(0, 11, 9, 10, 4th PIN HERE);
			//vals[getIndex(1, 1)] = mcp.mcp3008_value(1, 11, 9, 10, 4th PIN HERE);
			//vals[getIndex(1, 2)] = mcp.mcp3008_value(2, 11, 9, 10, 4th PIN HERE);
			//vals[getIndex(1, 3)] = mcp.mcp3008_value(3, 11, 9, 10, 4th PIN HERE);
			//vals[getIndex(1, 4)] = mcp.mcp3008_value(4, 11, 9, 10, 4th PIN HERE);
			//vals[getIndex(1, 5)] = mcp.mcp3008_value(5, 11, 9, 10, 4th PIN HERE);
			//vals[getIndex(1, 6)] = mcp.mcp3008_value(6, 11, 9, 10, 4th PIN HERE);
			//vals[getIndex(1, 7)] = mcp.mcp3008_value(7, 11, 9, 10, 4th PIN HERE);

			usleep(11609);     //ONLY WORKS ON PI (UNIX)
		}
	}

	int getIndex(int mcp, int pot)
	{
		return (mcp * 8) + pot;
	}
