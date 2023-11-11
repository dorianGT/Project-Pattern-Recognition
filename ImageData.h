#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <vector>

struct ImageData {
    int val; // Class of the image
    std::vector<float> features; // Feature vector
    double distance; // Distance from the test ImageData

    ImageData(int size) : features(size, 0) {} // Initialize the feature vector
};

#endif
