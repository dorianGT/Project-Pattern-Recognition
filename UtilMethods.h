#ifndef UTILMETHODS_H
#define UTILMETHODS_H

#include <vector>
#include "ImageData.h"
using namespace std;

// Function declarations
double calculateDistance(std::vector<float> features1, std::vector<float> features2);
double calculateDistanceManhattan(std::vector<float> features1, std::vector<float> features2);
bool comparison(ImageData a, ImageData b);

#endif // METHODUTIL_H
