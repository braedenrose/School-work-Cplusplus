// File name: GuitarHero.cpp
// Author: Braeden Rose
// userid: roseb2
// Email: braeden.rose@vanderbilt.edu
// Assignment Number: 6
// Description:  
// Simulates a guitar playing. Creates a 3-octaves scale of musical notes based on frequency 
// Reads a .dat file in from the computer consisting of note values 0-36 and 
// time stamps, then creates a .dat file that gives the time stamps and the
// frequencies related to each note. The .dat file can be converted into a playable
// .wav file
// Honor statement: This is my original work.
// Last Changed: 11-12-16

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include "GuitarString.h"
using namespace std;


const double CONCERT_A = 440.0;
const int NUM_STRINGS = 37;
const double STEP = (double)1/((double)SAMPLE_RATE);   //SAMPLE_RATE declared in GuitarString.h


// open input and output files
// pre: user is prepared to enter file names at the keyboard
// post: files have been opened
void openFiles (ifstream &infile, ofstream &outfile);

//increases the time count by 1/44100, simulating a step in time
double timeStep(double d);

int main() {

	// creates the array of guitar strings (3 octaves)
	GuitarString* strings[NUM_STRINGS];
	for (int i = 0; i < NUM_STRINGS; i++) {
		double factor = pow(2, (i - 24) / 12.0);
		strings[i] = new GuitarString(CONCERT_A * factor);
	}

	//open data file
	ifstream infile;
	ofstream outfile;
	openFiles(infile, outfile);

	cout << "Reading the input file and generating a .dat file for sox" << endl;
	outfile.setf(ios::fixed, ios::floatfield);
	outfile.precision(10);

	//prime the output file 
	string firstLine  = "; Sample Rate 44100";
	string secondLine = "; Channels 1";
	outfile << firstLine << endl;
	outfile << secondLine << endl;

	// Here I will read & process all the data in the input stream "infile", 
	// and create & write the correct data to the output stream "outfile".
	// After the file are fully processed/written, close them
	

	double dbl;
	double timeCount = 0.0;
	while (infile >> dbl)
	{
		if (timeCount > timeStep(dbl))						//if any of the timestamps that succeed the previous one are for a previous time, the cut them. 
		{
			throw std::out_of_range("Not in chronological order");
			cout << "Not in chronological order." << endl;
		}
		else
			while (timeCount <= dbl)
			{
				double sum = 0.0;
				for (int i = 0; i < NUM_STRINGS; i++)
				{
					sum += strings[i]->sample();			//takes a sample of each guitar string' vibration
					strings[i]->tic();						//then steps the function
				}
				outfile << "  " << timeCount << "\t" << sum << endl;
				timeCount = timeStep(timeCount);
			}
		(infile >> dbl);
		
		//if the inputted note is outside of the range of the strings, the simulation stops
		if (dbl != ((int)dbl) || dbl < -1.0 || dbl > NUM_STRINGS-1) 
			throw std::out_of_range("out of range");
		else if (dbl == -1.0)
			break;
		else 
		{
			(*strings[(int)dbl]).pluck();
			cout << "pluck " << dbl << endl; //outputs pluck whenever a timestamp indicates a not to be played
		}									 // no. of plucks = no. of timestamps	
	}

	// close the files
	infile.close();
	outfile.close();
	cout << "Done." << endl;

	//Clean up all the strings
	for (int i = 0; i < NUM_STRINGS; i++) {
		if(strings[i] != 0)
			delete strings[i];
	}
	return 1;
}



// open input and output files
// pre: user is prepared to enter file names at the keyboard
// post: files have been opened
void openFiles (ifstream &infile, ofstream &outfile)
{

	// open input data file
	string inFileName;
	cout << "Enter the name of the input file: ";
	cin >> inFileName;
	infile.open(inFileName.c_str());
	if (infile.fail()) {
		cout << "Error opening input data file" << endl;
		char junk;
		cout << "press enter to exit";
		junk = cin.get();
		junk = cin.get();
		exit(1);
	}
	// open output data file
	string outFileName;
	cout << "Enter the name of the output file: ";
	cin >> outFileName;
	outfile.open(outFileName.c_str());
	if (outfile.fail()) {
		cout << "Error opening output data file" << endl;
		char junk;
		cout << "press enter to exit";
		junk = cin.get();
		junk = cin.get();
		exit(1);
	}

}

//increases the time count by 1/44100, simulating a step in time
double timeStep(double d) {
	return d + ((double)1.0 / ((double)SAMPLE_RATE));
}
