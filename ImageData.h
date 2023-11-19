#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <vector>

struct ImageData {
    int trueLabel; // Class of the image
    int predictedLabel; // The predicted class
    std::vector<float> features; // Feature vector
    double distance; // Distance from the test ImageData

    ImageData(int size) : features(size, 0) {} // Initialize the feature vector
};

struct centroid {
    int label;
    std::vector<float> features;
    centroid(int size) :features(size,0) {}
};

#endif
