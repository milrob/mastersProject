/*
  ==============================================================================

    LoopGen.h
    Created: 16 Jul 2014 2:23:14pm
    Author:  milrob

  ==============================================================================
*/

#ifndef LOOPGEN_H_INCLUDED
#define LOOPGEN_H_INCLUDED

#include <vector>
#include "JuceHeader.h"

using namespace std;

const int SR = 44100;
const float BAR_SIZE = 1.0;
    
struct Loop {
    float start, end;
    Loop* prev;
    Loop* next;
    //MATRIX markovChain;
};


vector<Loop> computeLoops(std::string audiofilename);
void createLoopPoints(const vector<float>& onsets);
void connectLoops();
float quantizeToOnset(const vector<float>& onsets, float value);
//template <typename T> T retrieveFeature(T featType, std::string featName);



#endif  // LOOPGEN_H_INCLUDED