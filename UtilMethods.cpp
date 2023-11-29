#include "UtilMethods.h"
using namespace std;
#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <dirent.h>
#include <map>

// Function to calculate Euclidean distance between two feature vectors
// Parameters:
//   - features1: Feature vector of the first data point
//   - features2: Feature vector of the second data point
// Returns:
//   - Euclidean distance between the two feature vectors
double calculateDistance(std::vector<float> features1, std::vector<float> features2) {
    double sum = 0.0;
    // Ensure both vectors have the same size
    if (features1.size() != features2.size()) {
        cerr << "Error: Vectors do not have the same size." << endl;
        return -1.0; // Or use appropriate error handling
    }

    for (int i = 0; i < features1.size(); ++i) {
        sum += pow(features1[i] - features2[i], 2);
    }
    return sqrt(sum);
}

// Function to calculate Manhattan distance between two feature vectors
// Parameters:
//   - features1: Feature vector of the first data point
//   - features2: Feature vector of the second data point
// Returns:
//   - Manhattan distance between the two feature vectors
double calculateDistanceManhattan(std::vector<float> features1, std::vector<float> features2) {
    double sum = 0.0;
    // Ensure both vectors have the same size
    if (features1.size() != features2.size()) {
        cerr << "Error: Vectors do not have the same size." << endl;
        return -1.0; // Or use appropriate error handling
    }

    for (int i = 0; i < features1.size(); ++i) {
        sum += abs(features1[i] - features2[i]);
    }
    return sum;
}

// Compare two ImageData structures based on their distance
// Parameters:
//   - a: First ImageData structure for comparison
//   - b: Second ImageData structure for comparison
// Returns:
//   - True if the distance of 'a' is less than the distance of 'b', false otherwise
bool comparison(ImageData a, ImageData b) {
    return (a.distance <= b.distance);
}

// Get the number of digits in an integer
// Parameters:
//   - num: Integer for which the number of digits is calculated
// Returns:
//   - Number of digits in the integer
int numDigits(int num) {
    int count = 0;
    while (num != 0) {
        num /= 10;
        ++count;
    }
    return count;
}

// Function to display the confusion matrix
// Parameters:
//   - confusionMatrix: 2D vector representing the confusion matrix
//   - numClasses: Number of classes in the dataset
void displayConfusionMatrix(const vector<vector<int>>& confusionMatrix, int numClasses) {
    // Display confusion matrix
    cout << "Confusion Matrix" << endl;
    cout << "      ";
    int maxDigits = 2;

    // Adjust column width based on the maximum number of digits in any matrix element
    for (int i = 0; i < numClasses; ++i) {
        for (int j = 0; j < numClasses; ++j) {
            int digits = numDigits(confusionMatrix[j][i]);
            if (digits > maxDigits) {
                maxDigits = digits;
            }
        }
    }

    // Set a minimum column width
    maxDigits = max(maxDigits, 3);

    cout << setw(3) << "C1 ";
    for (int i = 1; i < numClasses; ++i) {
        cout << setw(2) << "C" << i + 1 << " ";
    }

    cout << endl;

    for (int i = 0; i < numClasses; ++i) {
        cout << "C" << i + 1 << " | ";
        int digits = numDigits(confusionMatrix[i][0]);
        cout << setw(maxDigits) << confusionMatrix[i][0] << " ";

        for (int j = 1; j < numClasses; ++j) {
            // Center-align each matrix element within its column
            int digits = numDigits(confusionMatrix[i][j]);
            cout << setw(maxDigits) << confusionMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to show results, including confusion matrix and success percentage
// Parameters:
//   - numClasses: Number of classes in the dataset
//   - dataResult: Vector of ImageData containing the results
// Returns:
//   - The number of true positives
int ShowResults(int numClasses, vector<ImageData>& dataResult) {
    // Initialize confusion matrix
    vector<vector<int>> confusionMatrix(numClasses, vector<int>(numClasses, 0));

    // Populate confusion matrix
    for (vector<ImageData>::iterator t = dataResult.begin(); t != dataResult.end(); ++t) {
        confusionMatrix[t->trueLabel - 1][t->predictedLabel - 1]++;
    }

    // Display confusion matrix
    displayConfusionMatrix(confusionMatrix, numClasses);

    // Calculate true positives
    int vp = 0;
    for (int i = 0; i < numClasses; ++i) {
        vp += confusionMatrix[i][i];
    }

    // Calculate and print the success percentage for this value of k
    double successPercentage = (static_cast<double>(vp) / dataResult.size()) * 100;
    printf("Success Percentage: %.2f%% , vp: %d\n", successPercentage, vp);
    return vp;
}

// Function to get data from a directory
// Parameters:
//   - className: Name of the class or directory from which data is retrieved
//   - numData: Number of data values to be retrieved
//   - classCategory: Category specifying whether it's training or test data
// Returns:
//   - Vector of ImageData containing the retrieved data
vector<ImageData> GetDataDirectory(string className, int numData, string classCategory) {
    DIR *dr;
    struct dirent *en;
    dr = opendir(className.c_str()); // Open the directory
    vector<ImageData> arr; // Use a vector to store the ImageDatas

    if (dr) {
        while ((en = readdir(dr)) != NULL) {
            if (en->d_name[0] == '.') continue; // Ignore hidden files

            // Create the full file path
            string filePath = className + classCategory + "/" + string(en->d_name);

            // Open the file in read mode
            ifstream file(filePath);
            if (file.is_open()) {
                ImageData p(numData);
                int classLabel = stoi(en->d_name + 1); // Extract class number from the file name
                p.trueLabel = classLabel;
                // Read the values from the file and store them in the features array
                for (int i = 0; i < numData; ++i) {
                    float value;
                    file >> value;
                    p.features[i] = value;
                }

                // Add the ImageData to the vector
                arr.push_back(p);

                // Close the file
                file.close();
            }
        }
        closedir(dr); // Close the directory
    }
    return arr;
}
