#ifndef KNN_H
#define KNN_H

#include <vector>
#include "ImageData.h"

// Function declarations
double calculateDistance(std::vector<float> features1, std::vector<float> features2);
double calculateDistanceManhattan(std::vector<float> features1, std::vector<float> features2);
bool comparison(ImageData a, ImageData b);
int classifyImageData(ImageData arr[], int n, int k, ImageData p, int numClasses);

#endif // KNN_H
