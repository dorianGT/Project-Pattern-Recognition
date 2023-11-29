#ifndef KNN_H
#define KNN_H

#include <vector>
#include "ImageData.h"
#include "UtilMethods.h"

// Function to classify an ImageData using the k-Nearest Neighbors algorithm
// Parameters:
//   arr: Array of ImageData representing the dataset
//   n: Size of the dataset
//   k: Number of nearest neighbors to consider
//   testData: ImageData to be classified
//   numClasses: Number of classes in the dataset
// Returns:
//   - The predicted class
int knn(ImageData arr[], int n, int k, ImageData testData, int numClasses);

#endif // KNN_H
