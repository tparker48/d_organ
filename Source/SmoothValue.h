#pragma once

// This class is designed to smooth the quick changes of numeric types
// Solves the common popping/crackling issue that arrises when certain values change too quickly

template <class T> class SmoothValue {
public:
	// transitionSpeed [0-1] determines how fast the value can change. 0 will never change, 1 will change instantaneously.
	void init(T startingValue, float transitionSpeed)
	{
		currentValue = startingValue;
		targetValue = startingValue;
		this->transitionSpeed = transitionSpeed;
	}

	T getValue()
	{
		if(abs(targetValue - currentValue) <= (.1f * targetValue)) currentValue = targetValue;
		currentValue = currentValue + (targetValue - currentValue) * transitionSpeed;
		return currentValue;
	}

	void setValue(T newVal)
	{
		targetValue = newVal;
	}

private:
	T targetValue, currentValue;
	float transitionSpeed;
};
