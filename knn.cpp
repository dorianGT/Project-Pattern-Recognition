#include <iostream>
#include "knn.h"
#include <algorithm>    // std::sort

// Function to classify an ImageData using the k-Nearest Neighbors algorithm
// Parameters:
//   arr: Array of ImageData representing the dataset
//   n: Size of the dataset
//   k: Number of nearest neighbors to consider
//   testData: ImageData to be classified
//   numClasses: Number of classes in the dataset
int knn(ImageData arr[], int n, int k, ImageData testData, int numClasses) {
    // Calculate distances from the test ImageData to all elements in the dataset
    for (int i = 0; i < n; i++) {
        arr[i].distance = calculateDistance(arr[i].features, testData.features);
    }

    // Sort ImageData array by distances from the test ImageData
    sort(arr, arr + n, comparison);

    // Use an array to store frequencies of each class
    vector<int> frequencies(numClasses, 0);

    // Consider the first k elements and count frequencies of each class
    for (int i = 0; i < k; i++) {
        frequencies[arr[i].trueLabel - 1]++;
    }

    // Find the class with the highest frequency among k neighbors
    int maxFreq = frequencies[0];
    int predictedClass = 0;
    for (int i = 1; i < numClasses; ++i) {
        if (frequencies[i] > maxFreq) {
            maxFreq = frequencies[i];
            predictedClass = i;
        }
    }

    // Return the predicted class (adding 1 to match class labels starting from 1)
    return predictedClass + 1;
}
