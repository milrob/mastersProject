/*
  ==============================================================================

    FeatureExtractor.h
    Created: 28 Jul 2014 1:53:06pm
    Author:  milrob

  ==============================================================================
*/

#ifndef FEATUREEXTRACTOR_H_INCLUDED
#define FEATUREEXTRACTOR_H_INCLUDED

#include "pool.h"
#include "ProgressWindow.h"

/* ===========================================================================*//*
|               [List of features]                                              |
|                                                                               |
| Rhythm:                                                                       |
|    Tempogram, onsetTimes, Beats, beatIntervals                                |
| ----------------------------------------------------------------------------- |
| Dynamics:                                                                     |
|    dynamicRangeCoeff, RMS, Loudness                                           |
| ----------------------------------------------------------------------------- |
| MFCCs:                                                                        |
|    mfccBands, mfccCoeffs, centroid                                            |
| ----------------------------------------------------------------------------- |
| Tonal:                                                                        |
|    Chords:                                                                    |
|        changeRate, numberRate, key, scale, histogram, strength, progression   |
|    Key:                                                                       |
|        scale, key                                                             |
|    Pitch:                                                                     |
|        hpcp, hpcpHighRes                                                      |
|                                                                               |
*//*=========================================================================== */


extern int FRAME_SIZE;
extern int HOP;
extern int NumFeatures;

extern bool successfulExtraction;

extern essentia::Pool* featureBin;

void computeFeatures(std::string song);


#endif  // FEATUREEXTRACTOR_H_INCLUDED
