#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <vector>

// Structure representing image data
struct ImageData {
    int trueLabel; // Class of the image
    int predictedLabel; // Predicted class
    std::vector<float> features; // Feature vector
    double distance; // Distance from the test ImageData

    ImageData(int size) : features(size, 0) {} // Initialize the feature vector
};

// Structure representing a centroid
struct centroid {
    int label; // Label of the centroid
    std::vector<float> features; // Feature vector of the centroid
    centroid(int size) : features(size, 0) {} // Initialize the centroid's feature vector
};

#endif
