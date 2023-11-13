#ifndef KNN_H
#define KNN_H

#include <vector>
#include "ImageData.h"
#include "UtilMethods.h"

// Function declarations
int classifyImageData(ImageData arr[], int n, int k, ImageData p, int numClasses);

#endif // KNN_H
