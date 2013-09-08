//
//  CaptureReal.h
//  CaptureReal
//
//  Created by annie zhang on 8/24/13.

#ifndef __CaptureReal__CaptureReal__
#define __CaptureReal__CaptureReal__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include "ChromaFeat.h"

#define ONSET_TRACK_SIZE 5                                  // keep track of the previous 5 onset bin vectors
#define DETECTIONFUN_TRACK_SIZE 10                          // keep track of the previous 10 detection functions
#define ONSET_WINDOW 30                                     // allow only one onset within 6 concatenate frames
#define CHORD_WINDOW 3                                      // keep track of 5 chords after the onset
#define PHI_DIM  6

using namespace std;

class CaptureReal{
    
public:
    CaptureReal(long int num);
    ~CaptureReal();
    void generatePattern();
	int getPeak(float* x, int xsize);
    float L1norm(float* vec, int vecSize);
    int harmonicChange(float* currChroma);
    void getChordPattern(float* x, int* chordindex, int xsize);
    int matchChord(int targetp);
    int match(int p);
    float getThreshold();
    float getHarmonicThreshold();
//    int onsetDetect(float *curr);
    double sinc(double x);
    void smooth(int* c, long csize);
    bool allowOnset();
    void initTonalCentroid();
    int vote();
    void capture(float* samples);
    void resample(float* input, float* output, unsigned in_rate, unsigned out_rate, long in_length);
    bool convolve1D(short* in, float* out, long dataSize, float* kernel, int kernelSize);
    void pitcher(float* gWavDataIn);
    
    ChromaFeat *cf;
    int** target3chord;
    int** target4chord;
    int* targetChord;
    int* targetOnset;
    float** phi;
    float* prePhi;
    float* curPhi;
    
    string chordDetected = "";
    int sensitivity = 1;                                         // 1 -- complicated chords, 0 -- simple chords only
    float threshold = 1.0;                                       // sensitivity to complicated chords
    
protected:
    const int chunkSize = 1024;
    const int hopSize = 100;
    const int base = 1;                                          // pattern base number
    const int pow11 = 2048;
    const float r1 = 1;                                          // radius of circle of 5
    const float r2 = 1;                                          // radius of circle of major 3
    const float r3 = 0.5;                                        // radius of circle of minor 3
    
    long int inNum;
    long int numSamples;
    int numChunks;                                               // num of chunks
    float* resampleddata;                                        // data after downsampling
    float* inputData;
    long pmajor = 1;                                             // major value
    long pminor = 1;                                             // minor chord
    long pmajor7 = 1;                                            // major7 chord
    long pminor7 = 1;                                            // minor7 chord
    long p7 = 1;                                                 // 7 chord
    bool collectChord = false;
    
    vector<string> chordnamelist;
    vector<float*> onsetbinlist;
    vector<int> onsetlist;
    vector<int> chordlist;
    vector<float> detfunlist;
    vector<float> harmonicChangelist;
};


#endif /* defined(__CaptureReal__CaptureReal__) */
