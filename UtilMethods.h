#ifndef UTILMETHODS_H
#define UTILMETHODS_H

#include <vector>
#include <string>
#include "ImageData.h"
using namespace std;

// Function to calculate Euclidean distance between two feature vectors
// Parameters:
//   - features1: Feature vector of the first data point
//   - features2: Feature vector of the second data point
// Returns:
//   - Euclidean distance between the two feature vectors
double calculateDistance(std::vector<float> features1, std::vector<float> features2);

// Function to calculate Manhattan distance between two feature vectors
// Parameters:
//   - features1: Feature vector of the first data point
//   - features2: Feature vector of the second data point
// Returns:
//   - Manhattan distance between the two feature vectors
double calculateDistanceManhattan(std::vector<float> features1, std::vector<float> features2);

// Compare two ImageData structures based on their distance
// Parameters:
//   - a: First ImageData structure for comparison
//   - b: Second ImageData structure for comparison
// Returns:
//   - True if the distance of 'a' is less than the distance of 'b', false otherwise
bool comparison(ImageData a, ImageData b);

// Get the number of digits in an integer
// Parameters:
//   - num: Integer for which the number of digits is calculated
// Returns:
//   - Number of digits in the integer
int numDigits(int num);

// Function to display the confusion matrix
// Parameters:
//   - confusionMatrix: 2D vector representing the confusion matrix
//   - numClasses: Number of classes in the dataset
void displayConfusionMatrix(const vector<vector<int>>& confusionMatrix, int numClasses);

// Function to show results, including confusion matrix and success percentage
// Parameters:
//   - numClasses: Number of classes in the dataset
//   - dataResult: Vector of ImageData containing the results
// Returns:
//   - The number of true positives
int ShowResults(int numClasses, vector<ImageData>& dataResult);

// Function to get data from a directory
// Parameters:
//   - className: Name of the class or directory from which data is retrieved
//   - numData: Number of data values to be retrieved
//   - classCategory: Category specifying whether it's training or test data
// Returns:
//   - Vector of ImageData containing the retrieved data
vector<ImageData> GetDataDirectory(string className, int numData, string classCategory);

#endif // UTILMETHODS_H
