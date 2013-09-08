//
//  CaptureReal.cpp
//  CaptureReal
//
//  Created by annie zhang on 8/24/13.
//
//

// major chords
// c  {0,4,7};
//    {1,5,8};
//    {2,6,9};
//    {3,7,10};
//    {4,8,11};
//    {0,5,9};
//    {1,6,10};
//    {2,7,11};
//    {0,3,8};
//    {1,4,9};
//    {2,5,10};
// b  {3,6,11};

// minor chords
// c  {0,3,7};
//    {1,4,8};
//    {2,5,9};
//    {3,6,10};
//    {4,7,11};
//    {0,5,8};
//    {1,6,9};
//    {2,7,10};
//    {3,8,11};
//    {0,4,9};
//    {1,5,10};
// b  {2,6,11};

// major7 chords
// c  {0,4,7,11};
//    {0,1,5,8};
//    {1,2,6,9};
//    {2,3,7,10};
//    {3,4,8,11};
//    {0,4,5,9};
//    {1,5,6,10};
//    {2,6,7,11};
//    {0,3,7,8};
//    {1,4,8,9};
//    {2,5,9,10};
// b  {3,6,10,11};

//  minor7 chords
// c  {0,3,7,10};
//    {1,4,8,11};
//    {0,2,5,9};
//    {1,3,6,10};
//    {2,4,7,11};
//    {0,3,5,8};
//    {1,4,6,9};
//    {2,5,7,10};
//    {3,6,8,11};
//    {0,4,7,9};
//    {1,5,8,10};
// b  {2,6,9,11};

// 7 chords
// c  {0,4,7,10};
//    {1,5,8,11};
//    {0,2,6,9};
//    {1,3,7,10};
//    {2,4,8,11};
//    {0,3,5,9};
//    {1,4,6,10};
//    {2,5,7,11};
//    {0,3,6,8};
//    {1,4,7,9};
//    {2,5,8,10};
// b  {3,6,9,11};



#include "CaptureReal.h"



CaptureReal::CaptureReal(long int num){
    
    inNum = num;
    numSamples = ceil((float)inNum*FS/F);
    numChunks = ceil((float)(numSamples-chunkSize)*1.0/hopSize)+1;
    resampleddata = new float[numSamples];
    inputData = new float[(numChunks-1)*hopSize+chunkSize];
    
    cf = new ChromaFeat(chunkSize);
    target3chord = new int*[numChunks];
    for (int i=0; i<numChunks; i++)
        target3chord[i] = new int[3];
    target4chord = new int*[numChunks];
    for (int i=0; i<numChunks; i++)
        target4chord[i] = new int[4];
    targetChord = new int[numChunks];
    targetOnset = new int[numChunks];
    
    generatePattern();
    initTonalCentroid();
}

CaptureReal::~CaptureReal(){
    
    delete cf;
    delete resampleddata;
    delete inputData;
    for (int i=0; i<numChunks; i++)
        delete target3chord[i];
    delete target3chord;
    for (int i=0; i<numChunks; i++)
        delete target4chord[i];
    delete target4chord;
    delete targetChord;
    delete targetOnset;
    for (int i=0; i<PHI_DIM; i++)
        delete phi[i];
    delete phi;
    delete prePhi;
    delete curPhi;
    
    chordnamelist.clear();
    onsetbinlist.clear();
    detfunlist.clear();
    onsetlist.clear();
}


void CaptureReal::generatePattern()
{
    int major[2] = {4,7};
    int minor[2] = {3,7};
    int major7[3] = {4,7,11};
    int minor7[3] = {3,7,10};
    int r7[3] = {4,7,10};
    
    for(int i=0; i<sizeof(major)/sizeof(int); i++)
        pmajor += base<<major[i];
    for(int i=0; i<sizeof(minor)/sizeof(int); i++)
        pminor += base<<minor[i];
    for(int i=0; i<sizeof(major7)/sizeof(int); i++)
        pmajor7 += base<<major7[i];
    for(int i=0; i<sizeof(minor7)/sizeof(int); i++)
        pminor7 += base<<minor7[i];
    for(int i=0; i<sizeof(r7)/sizeof(int); i++)
        p7 += base<<r7[i];
    
    chordnamelist.push_back("C major");
    chordnamelist.push_back("C# major");
    chordnamelist.push_back("D major");
    chordnamelist.push_back("D# major");
    chordnamelist.push_back("E major");
    chordnamelist.push_back("F major");
    chordnamelist.push_back("F# major");
    chordnamelist.push_back("G major");
    chordnamelist.push_back("G# major");
    chordnamelist.push_back("A major");
    chordnamelist.push_back("A# major");
    chordnamelist.push_back("B major");
    
    chordnamelist.push_back("C minor");
    chordnamelist.push_back("C# minor");
    chordnamelist.push_back("D minor");
    chordnamelist.push_back("D# minor");
    chordnamelist.push_back("E minor");
    chordnamelist.push_back("F minor");
    chordnamelist.push_back("F# minor");
    chordnamelist.push_back("G minor");
    chordnamelist.push_back("G# minor");
    chordnamelist.push_back("A minor");
    chordnamelist.push_back("A# minor");
    chordnamelist.push_back("B minor");
    
    chordnamelist.push_back("C major7");
    chordnamelist.push_back("C# major7");
    chordnamelist.push_back("D major7");
    chordnamelist.push_back("D# major7");
    chordnamelist.push_back("E major7");
    chordnamelist.push_back("F major7");
    chordnamelist.push_back("F# major7");
    chordnamelist.push_back("G major7");
    chordnamelist.push_back("G# major7");
    chordnamelist.push_back("A major7");
    chordnamelist.push_back("A# major7");
    chordnamelist.push_back("B major7");
    
    chordnamelist.push_back("C minor7");
    chordnamelist.push_back("C# minor7");
    chordnamelist.push_back("D minor7");
    chordnamelist.push_back("D# minor7");
    chordnamelist.push_back("E minor7");
    chordnamelist.push_back("F minor7");
    chordnamelist.push_back("F# minor7");
    chordnamelist.push_back("G minor7");
    chordnamelist.push_back("G# minor7");
    chordnamelist.push_back("A minor7");
    chordnamelist.push_back("A# minor7");
    chordnamelist.push_back("B minor7");
    
    chordnamelist.push_back("C 7");
    chordnamelist.push_back("C# 7");
    chordnamelist.push_back("D 7");
    chordnamelist.push_back("D# 7");
    chordnamelist.push_back("E 7");
    chordnamelist.push_back("F 7");
    chordnamelist.push_back("F# 7");
    chordnamelist.push_back("G 7");
    chordnamelist.push_back("G# 7");
    chordnamelist.push_back("A 7");
    chordnamelist.push_back("A# 7");
    chordnamelist.push_back("B 7");
    
}


void CaptureReal::initTonalCentroid()
{
    phi = new float*[PHI_DIM];
    for (int i=0; i<PHI_DIM; i++)
        phi[i] = new float[NUMCHROMAGRAM];
    
    for (int i=0; i<NUMCHROMAGRAM; i++)
        phi[0][i] = r1 * sin(7*PI/6*i);
    for (int i=0; i<NUMCHROMAGRAM; i++)
        phi[1][i] = r1 * cos(7*PI/6*i);
    for (int i=0; i<NUMCHROMAGRAM; i++)
        phi[2][i] = r2 * sin(7*PI/6*i);
    for (int i=0; i<NUMCHROMAGRAM; i++)
        phi[3][i] = r2 * cos(7*PI/6*i);
    for (int i=0; i<NUMCHROMAGRAM; i++)
        phi[4][i] = r3 * sin(7*PI/6*i);
    for (int i=0; i<NUMCHROMAGRAM; i++)
        phi[5][i] = r3 * cos(7*PI/6*i);
    
    prePhi = new float[PHI_DIM];
    curPhi = new float[PHI_DIM];
    
    // init previous frame's phi vector to be 0
    memset(prePhi, 0, PHI_DIM*sizeof(float));
}


int CaptureReal::getPeak(float* x, int xsize)
{
    int index = 0;
    float max = x[0];
    for (int k=1; k< xsize; k++){
        if (x[k]>max){
            index = k;
            max = x[k];
        }
    }
    return index;
}


float CaptureReal::L1norm(float* vec, int vecSize){
    float th = 0;
    for(int k=0; k<vecSize; k++)
        th += fabs(vec[k]);
    return th;
}

float CaptureReal::getHarmonicThreshold(){
    float th = 0;
    for(int k=0; k<harmonicChangelist.size(); k++)
        th += harmonicChangelist[k];
    th /= harmonicChangelist.size();
    return th;
}

int CaptureReal::harmonicChange(float* currChroma){
    int isOnset = 0;
    
    // calculate current phi vector
    for (int i=0; i<PHI_DIM; i++){
        curPhi[i] = 0;
        for (int j=0; j<NUMCHROMAGRAM; j++)
            curPhi[i] += phi[i][j]*currChroma[j];
        curPhi[i] /= L1norm(currChroma, NUMCHROMAGRAM);
    }
    // calculate euclidian distance between tonal centroid vectors prePhi and currPhi
    float diffPhi = 0;
    for (int k=0; k<PHI_DIM; k++)
        diffPhi += (curPhi[k] - prePhi[k])*(curPhi[k] - prePhi[k]);
    diffPhi = sqrt(diffPhi);
    
    if (diffPhi > getHarmonicThreshold()*threshold)
        isOnset = 1;
    else{
        // update detection function list being tracking
        if(harmonicChangelist.size()<10)
            harmonicChangelist.push_back(diffPhi);
        else{
            harmonicChangelist.erase(harmonicChangelist.begin());
            harmonicChangelist.push_back(diffPhi);
        }
    }
    for (int k=0; k<PHI_DIM; k++)
        prePhi[k] = curPhi[k];

    return isOnset;
}


void CaptureReal::getChordPattern(float* x, int* chordindex, int peaknum){
    for (int i=0; i<peaknum; i++){
        chordindex[i] = getPeak(x, NUMCHROMAGRAM);
        x[chordindex[i]] = -1;
    }
}


int CaptureReal::matchChord(int targetp){
    
    int i = NUMCHROMAGRAM;
    int k = match(targetp);
    if(k<0){
        for (i=1; i<NUMCHROMAGRAM; i++){
            int v11 = (targetp&(1<<11))/pow11;
            targetp = targetp*2 - v11*pow11*2 + v11;
            k = match(targetp);
            if (k>=0)
                break;
        }
    }
    
    int chordIndex = k*NUMCHROMAGRAM + NUMCHROMAGRAM - i;
    
    return chordIndex;
}


int CaptureReal::match(int p){
    if (p == pmajor7)
        return 2;
    else if (p == pminor7)
        return 3;
    else if (p == p7)
        return 4;
    else if (p == pmajor)
        return 0;
    else if (p == pminor)
        return 1;
    else
        return -1;
}


void CaptureReal::smooth(int* c, long csize)
{
    for (int i=1; i<csize-1; i++)
        if(c[i-1] == c[i+1])
            c[i] = c[i-1];
}


float CaptureReal::getThreshold(){
    float th = 0;
    for(int k=0; k<detfunlist.size(); k++)
        th += detfunlist[k];
    th /= detfunlist.size();
    return th;
}


//int CaptureReal::onsetDetect(float *curr)
//{
//    int isOnset = 0;
//    
//    float* onsetbinmean = new float[NUMONSETBIN];
//    for(int k=0; k<NUMONSETBIN; k++)
//        onsetbinmean[k] = 0;
//    if(onsetbinlist.size() == ONSET_TRACK_SIZE){
//        for(int i=0; i<NUMONSETBIN; i++){
//            for(int j=0; j<ONSET_TRACK_SIZE; j++)
//                onsetbinmean[i] += onsetbinlist[j][i];
//            onsetbinmean[i] /= ONSET_TRACK_SIZE;
//        }
//    }
//    delete onsetbinmean;
//    
//    float detFun = 0;
//    for(int k=0; k<NUMONSETBIN; k++)
//        if (curr[k]>onsetbinmean[k])
//            detFun += curr[k] - onsetbinmean[k];
//    
//    float th = getThreshold();
//    
//    if(detFun > th*threshold)
//        isOnset = 1;
//    
//    // update onset bin list being tracking
//    if(onsetbinlist.size()<ONSET_TRACK_SIZE)
//        onsetbinlist.push_back(curr);
//    else{
//        onsetbinlist.erase(onsetbinlist.begin());
//        onsetbinlist.push_back(curr);
//    }
//    
//    // update detection function list being tracking
//    if(detfunlist.size()<DETECTIONFUN_TRACK_SIZE)
//        detfunlist.push_back(detFun);
//    else{
//        detfunlist.erase(detfunlist.begin());
//        detfunlist.push_back(detFun);
//    }
//    
//    return isOnset;
//}


// check if the previous 6 frames has no onset in it
bool CaptureReal::allowOnset()
{
    int sum = 0;
    if(onsetlist.size() > 0)
        for (int k=0; k<onsetlist.size(); k++)
            sum += onsetlist[k];
    if (sum == 0)
        return true;
    
    return false;
}


// calculate the majority chord index
int CaptureReal::vote()
{
    int i;
    int elem = -1;
    int count = 1, count1 = 1;
    for(i = 0; i < CHORD_WINDOW; ) {
        while(chordlist[i]==chordlist[i+1]) {
            count++;
            i++;
        }
        if(count > count1) {
            count1 = count;
            elem = chordlist[i];
        }
        count = 1;
        i++;
    }
    return elem;
}


void CaptureReal::capture(float* samples)
{
    for(int j=0; j<numChunks; j++){
        
        memset(cf->chromagram, 0, NUMCHROMAGRAM*sizeof(float));
        
        cf->Chroma(&samples[j*hopSize]);
       
        // detect chord
        memset(target3chord[j], 0, 3*sizeof(int));
        memset(target4chord[j], 0, 4*sizeof(int));
        getChordPattern(cf->chromagram, target3chord[j], 3);                           // chromagram chord 3 peaks
        for (int i=0; i<3; i++)
            target4chord[j][i] = target3chord[j][i];
        target4chord[j][3] = getPeak(cf->chromagram, NUMCHROMAGRAM);                    // chromagram chord 4 peaks
        
        // detect onset
        if (allowOnset())
            targetOnset[j] = harmonicChange(cf->chromagram);
//            targetOnset[j] = onsetDetect(cf->onsetbin);
        else
            targetOnset[j] = 0;
   
        
        // update onsetlist
        if(onsetlist.size()<ONSET_WINDOW)
            onsetlist.push_back(targetOnset[j]);
        else{
            onsetlist.erase(onsetlist.begin());
            onsetlist.push_back(targetOnset[j]);
        }
        
        int targetp4 = 0;
        for(int i=0; i<4; i++)
            targetp4 += base << target4chord[j][i];
        int targetp3 = 0;
        for(int i=0; i<3; i++)
            targetp3 += base << target3chord[j][i];
        
        if(sensitivity == 1){
            targetChord[j] = matchChord(targetp4);
//            if(targetChord[j]<0)
//                targetChord[j] = matchChord(targetp3);
        }
        else
            targetChord[j] = matchChord(targetp3);
        
        // store deteced chord index after the onset (inside sustain)
        if(collectChord){
            if(chordlist.size() < CHORD_WINDOW)
                chordlist.push_back(targetChord[j]);
            else{
                int targetVote = vote();
                if(targetVote >= 0 && targetVote<chordnamelist.size())
                    chordDetected = chordnamelist[targetVote];
                chordlist.clear();
                collectChord = false;
            }
        }
        
        if(targetOnset[j]==1)
            collectChord = true;
    }
    
}


double CaptureReal::sinc(double x)
{
    if(x == 0.0) return 1.0;
    x *= PI;
    return std::sin(x) / x;
}


void CaptureReal::resample(float* input, float* output, unsigned in_rate, unsigned out_rate, long in_length)
{
    double ratio         = in_rate / (double)out_rate;
    unsigned out_length  = std::ceil(in_length / ratio);
    const double support = 4.0;
    
    for(unsigned i=0; i<out_length; ++i)
    {
        double center = i * ratio;
        double min    = center-support;
        double max    = center+support;
        
        unsigned min_in = std::max( 0,                 (int)(min + 0.5) );
        unsigned max_in = std::min( (int)in_length-1,  (int)(max + 0.5) );
        double sum    = 0.0;
        double result = 0.0;
        for(unsigned i=min_in; i<=max_in; ++i)
        {
            double factor = sinc(i-center);
            result += input[i] * factor;
            sum    += factor;
        }
        if(sum != 0.0) result /= sum;
        //        if(result <= -32768) output[i] = -32768;
        //        else if(result > 32767) output[i] = 32767;
        output[i] = result + 0.5;
    }
}



bool CaptureReal::convolve1D(short* in, float* out, long dataSize, float* kernel, int kernelSize)
{
    int i, j, k;
    
    // check validity of params
    if(!in || !out || !kernel) return false;
    if(dataSize <=0 || kernelSize <= 0) return false;
    
    // start convolution from out[kernelSize-1] to out[dataSize-1] (last)
    for(i = kernelSize-1; i < dataSize; ++i)
    {
        out[i] = 0;                             // init to 0 before accumulate
        
        for(j = i, k = 0; k < kernelSize; --j, ++k)
            out[i] += in[j] * kernel[k];
    }
    
    // convolution from out[0] to out[kernelSize-2]
    for(i = 0; i < kernelSize - 1; ++i)
    {
        out[i] = 0;                             // init to 0 before sum
        
        for(j = i, k = 0; j >= 0; --j, ++k)
            out[i] += in[j] * kernel[k];
    }
    return true;
}


void CaptureReal::pitcher(float* gWavDataIn){
    
    // downsample to sample rate FS
    resample(gWavDataIn, resampleddata, F, FS, inNum);
    
    memset(inputData, 0, sizeof(float)*((numChunks-1)*hopSize+chunkSize));
    for(int i=0; i<numSamples; i++)
        inputData[i] = resampleddata[i];
    
    // get pitch value
    capture(inputData);
    
}
