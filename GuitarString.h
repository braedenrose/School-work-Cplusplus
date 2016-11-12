// File name: GuitarString.h
// Author: Braeden Rose
// Email: braeden.rose@vanderbilt.edu
// Assignment Number: 6
// Description:  
// The automation of a single guitar string. Uses a queue to hold all of the
// waves interfering on the string as they decay
// Honor statement: This is my original work
// Last Changed: 11-12-16

#ifndef GUITARSTRING_H
#define GUITARSTRING_H

#include "DblQueue.h"
using namespace std;

const int SAMPLE_RATE = 44100;
const double DECAY_FACTOR = 0.996;

class GuitarString
{
  private :

	  DblQueue buffer;

	  double frequency; //frequency of the note being played

	  size_t steps; //how many time steps are accounted for 

	  //calculate the Karplus-Strong algorithm value, then return it to the front
	  //delete last node in the stack
	  void karplusCalc();


  public:
	// create a guitar string representing the given frequency
	// frequency - determines the note that the guitar string is called for
	GuitarString(double frequency);

	// pluck the string - excite with white noise between -0.5 and 0.5
	void pluck();

	// advance the simulation one step
	void tic();
	
	// current sample
	double sample() const;

	// number of time steps = number of calls to tic()
	int getTime() const;

	// return the frequency of the string
	double getFrequency() const;

};

#endif
