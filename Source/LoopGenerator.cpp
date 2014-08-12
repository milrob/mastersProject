/*
  ==============================================================================

    Here, the audio buffer is initialized; global onsets and beats are detected;
        loop points are created using those onsets/beats; features for each
        created loop is then extracted

  ==============================================================================
*/

#include "LoopGenerator.h"
#include "FeatureExtractor.h"


using namespace std;

const int SR = 44100;
const float BAR_SIZE = 1.0;

float LAST_ONSET;


vector<Loop> computeLoops(const std::string audiofilename) {
    std::vector<Loop> theLoops;
    const std::vector<essentia::Real> onsets(computeGlobalBeatsOnsets(audiofilename));
    LAST_ONSET = onsets.back();
    
    essentia::init();
        juce::ScopedPointer<essentia::standard::Algorithm> loader = essentia::standard::AlgorithmFactory::create("MonoLoader",
                                                                                                                 "filename", audiofilename, "sampleRate", SR);
        std::vector<essentia::Real> tempBuffer;
        loader->output("audio").set(tempBuffer);
        loader->compute();
    essentia::shutdown();
    
    juce::String s("Initializing Loop Generator");
    BackgroundThread progressWindow(static_cast<int>(onsets.size()), s);
    
    if (progressWindow.runThread()){
        progressWindow.setStatusMessage("Finding all possible loop points...");
        createLoopPoints(onsets, tempBuffer, theLoops);
        connectLoops(theLoops);
        progressWindow.setStatusMessage("Computing features for loops...");
        for (auto& lp : theLoops){
            std::vector<essentia::Real> loopBuffer(tempBuffer.begin() + lp.head, tempBuffer.begin() + lp.tail);
            computeFeaturesForLoop(lp, loopBuffer);
        }
    } else {
        progressWindow.threadComplete(true);
    }
    
    return theLoops;
}

void createLoopPoints(const std::vector<float>& onsets, const std::vector<essentia::Real>& AUDIO_BUFFER, std::vector<Loop>& loops){
    float lPoint;
    Loop curr;

    for (int i = 0; i < onsets.size(); ++i) {
        if (onsets[i] + BAR_SIZE <= LAST_ONSET) {
            curr.start = onsets[i];
            lPoint     = onsets[i] + BAR_SIZE;
            curr.end   = quantizeToOnset(onsets, lPoint);
            if (curr.start > curr.end)
                std::swap(curr.start, curr.end);
            curr.head = static_cast<int>(onsets[i] * SR);
            curr.tail = static_cast<int>(onsets[i+1] * SR);
            loops.push_back(curr);
        }
    }

}

void connectLoops(std::vector<Loop>& loops){
    for (int i = 0; i < loops.size(); ++i) {
        if (i == 0) {
            loops[i].prev = &loops[i];
            loops[i].next = &loops[1];
        } else if (i == loops.size() - 1){
            loops[i].prev = &loops[i-1];
            loops[i].next = &loops[i];
        } else {
            loops[i].prev = &loops[i-1];
            loops[i].next = &loops[i+1];
        }
        if (loops[i].end > loops[i].start) {
            std::swap(loops[i].end, loops[i].start);
        }
    }
}

inline float quantizeToOnset(const vector<float>& onsets, float value){
    if (value > LAST_ONSET) {
        value = LAST_ONSET;
        return value;
    }
    auto limit = std::equal_range(onsets.begin(), onsets.end(), value);
    float diff1 = abs(value - onsets[limit.first - onsets.begin()]);
    float diff2 = abs(onsets[limit.second - onsets.begin()] - value);
    
    if (diff1 > diff2) return onsets[limit.second - onsets.begin()];
    else               return onsets[limit.first - onsets.begin()];
}

