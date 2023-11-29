#include <iostream>
#include <string>
#include <map>
using namespace std;
#include "knn.h"
#include "kmeans.h"
#include "UtilMethods.h"

// Function to perform k-NN recognition for a given class
// Parameters:
//   - numClasses: Total number of classes in the dataset
//   - classDataMap: A map containing class names as keys and the corresponding number of data points as values
void knnRecognition(int numClasses, std::map<std::string, int> classDataMap) {
    // Iterate through each class and its associated data size
    std::map<std::string, int>::iterator it;
    for (it = classDataMap.begin(); it != classDataMap.end(); ++it) {
        // Extract class name and the number of data points for the class
        std::string className = it->first;
        int numData = it->second;

        // Retrieve training and test data for the current class
        vector<ImageData> arr = GetDataDirectory(className, numData, "Training");
        vector<ImageData> test = GetDataDirectory(className, numData, "Test");

        // Display class information
        cout << "---------------------" << endl;
        cout << className << endl;
        cout << "---------------------" << endl;

        // Initialize an array to store results for different values of k
        vector<int> arrayK(20);

        // Vary the value of k from 1 to 6
        for (int k = 1; k <= 5; ++k) {
            // Reset the predicted labels for each iteration
            for (vector<ImageData>::iterator t = test.begin(); t != test.end(); ++t) {
                int c = knn(arr.data(), arr.size(), k, *t, numClasses);
                t->predictedLabel = c;
            }
            // Display results for the current value of k
            cout << "k = " << k << endl;
            arrayK[k - 1] = ShowResults(numClasses, test);
        }
        
        // Choose the best k based on the highest true positives
        int kbestval = 0;
        int maxVp = 0;
        for (int k = 0; k < 20; ++k) {
            if (arrayK[k] >= maxVp) {
                kbestval = k;
                maxVp = arrayK[k];
            }
        }
        cout << "BEST K VALUE : " << kbestval + 1 << " WITH VP : " << maxVp << endl;
    }
}


// Function to perform k-means recognition for a given class
// Parameters:
//   - numClasses: Total number of classes in the dataset
//   - classDataMap: A map containing class names as keys and the corresponding number of data points as values
void kmeansRecognition(int numClasses, std::map<std::string, int> classDataMap) {
    // Iterate through each class and its associated data size
    std::map<std::string, int>::iterator it;
    for (it = classDataMap.begin(); it != classDataMap.end(); ++it) {
        // Extract class name and the number of data points for the class
        std::string className = it->first;
        int numData = it->second;

        // Retrieve data for the current class
        vector<ImageData> data = GetDataDirectory(className, numData, "");

        // Initialize the centroids
        vector<centroid> centroids;

        // Display class information
        cout << "---------------------"<< endl;
        cout << className << endl;
        cout << "---------------------"<< endl;

        // Perform k-means
        kmeans(data,numClasses,centroids,100);
        // Display results
        ShowResults(numClasses,data);
    }
}

int main() {
    // Number of classes in the dataset
    int numClasses = 9;

    // Map containing class names and corresponding number of data points
    std::map<std::string, int> classDataMap = {
        {"E34", 16},
        {"F0", 128},
        {"GFD", 100},
        {"SA", 90}
    };

    cout << "---------------------"<< endl;
    cout << "KNN" << endl;
    cout << "---------------------"<< endl;

    // Call the k-NN recognition function with the specified parameters
    knnRecognition(numClasses, classDataMap);

    cout << "---------------------"<< endl;
    cout << "KMEANS" << endl;
    cout << "---------------------"<< endl;

    // Call the k-means recognition function with the specified parameters
    kmeansRecognition(numClasses, classDataMap);

    return 0;
}

