// File name: GuitarString.cpp
// Author: Braeden Rose
// Email: braeden.rose@vanderbilt.edu
// Class: CS2201 @ Vanderbilt U.
// Assignment Number: 6
// Description: 
//Maintains the guitars string methods. The sound code goes here.
//Simulates a guitar string plucking, utilizes random number generator to create
//sound for the guitar. Methods such as tic, pluck, and sample give info
//as to the guitar step.
// Honor statement: This is my original work. 
// Last Changed:  11-12-16

#include <cstddef>
#include <chrono>
#include <random>
#include "GuitarString.h"
 
//create a guitar string representing the given frequency
GuitarString::GuitarString(double frequency):
	steps(0),
	frequency(frequency),
	buffer(DblQueue())
{
	double samples = (((double)SAMPLE_RATE)) / frequency;
	size_t totSample = size_t (samples + 0.5);
	for (size_t i = 0; i < totSample; i++)
	{
		buffer.enqueue(0.0);
	}
}


// pluck the string - excite with white noise between -0.5 and 0.5
void GuitarString::pluck() {
	// create the seed
	unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
	// create the generator using the seed
	std::default_random_engine generator(seed);
	// create the appropriate distribution
	std::uniform_real_distribution<double> distribution(-0.5, 0.5);
	// create random numbers as needed
	double num = distribution(generator);

	double samples = (((double)SAMPLE_RATE)) / frequency;
	size_t totSample = size_t(samples + 0.5);

	//dequeues all of the 0's and replaces them with a random number
	for (size_t i = 0; i < totSample; i++)
	{
		buffer.enqueue(num);
		num=distribution(generator);
		buffer.dequeue();
	}
}

// advance the simulation one step
void GuitarString::tic() {
	karplusCalc();
	steps++;
}

// current sample
double GuitarString::sample() const {
	return buffer.front();
}

// number of time steps = number of calls to tic()
int GuitarString::getTime() const {
	return steps;
}

// return the frequency of the string
double GuitarString::getFrequency() const {
	return frequency;
}

 void GuitarString::karplusCalc() {
	 ItemType i = buffer.front();
	 buffer.dequeue();
	 buffer.enqueue(((i + buffer.front())/2.0) * (ItemType)DECAY_FACTOR);
}