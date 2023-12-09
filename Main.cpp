#include <iostream>
#include <string>
#include <map>
using namespace std;
#include "knn.h"
#include "kmeans.h"
#include "UtilMethods.h"
#include <ctime> 

// Number of classes in the dataset
const int numClasses = 9;

// Map containing class names and corresponding number of data points
const std::map<std::string, int> classDataMap = {
    {"E34", 16},
    {"F0", 128},
    {"GFD", 100},
    {"SA", 90}
};

// Function to perform k-NN recognition for each class and determine the best k value
// Parameters:
//   - minK: Minimum value of k for classification
//   - maxK: Maximum value of k for classification
//   - numClasses: Total number of classes in the dataset
//   - classDataMap: A map containing class names as keys and the corresponding number of data points as values
void knnRecognition(int minK,int maxK, int numClasses, std::map<std::string, int> classDataMap) {
    // Iterate through each class and its associated data size
    std::map<std::string, int>::iterator it;
    for (it = classDataMap.begin(); it != classDataMap.end(); ++it) {
        // Extract class name and the number of data points for the class
        std::string className = it->first;
        int numData = it->second;

        // Initialize an array to store results for different values of k
        vector<int> arrayK(maxK-minK+1);

        // Retrieve training and test data for the current class
        vector<ImageData> arr = GetDataDirectory(className, numData, "Training");
        vector<ImageData> test = GetDataDirectory(className, numData, "Test");

        // Display class information
        cout << "---------------------" << endl;
        cout << className << endl;
        cout << "---------------------" << endl;

        // Vary the value of k from minK to maxK
        for (int k = minK; k <= maxK; ++k) {
            clock_t start = clock();
            // Reset the predicted labels for each iteration
            for (vector<ImageData>::iterator t = test.begin(); t != test.end(); ++t) {
                
                int c = knn(arr.data(), arr.size(), k, *t, numClasses);
                
                t->predictedLabel = c;
            }
            clock_t end = clock();
            double time_taken = (end - start) / (double)CLOCKS_PER_SEC;

            // Display results for the current value of k
            cout <<"---------------------"<<endl<< "k = " << k << endl<<"---------------------"<<endl;
            cout << "knnRecognition execution time: " << time_taken << " seconds" << endl<<"---------------------"<<endl;
            arrayK[k - minK] = ShowResults(numClasses, test);
        }
        // Choose the best k based on the highest true positives
        int kbestval = minK;
        int maxVp = 0;
        for (int k = 0; k < arrayK.size(); ++k) {
            if (arrayK[k] >= maxVp) {
                kbestval = k+minK;
                maxVp = arrayK[k];
            }
        }
        cout << endl << "------------------------------------------" << endl;
        cout << "BEST K VALUE : " << kbestval << " WITH VP : " << maxVp << endl;
        cout << "------------------------------------------" << endl;
    } 
}


// Function to perform k-means recognition for each class and determine the best k value
// Parameters:
//   - minK: Minimum value of k for clustering
//   - maxK: Maximum value of k for clustering
//   - numClasses: Total number of classes in the dataset
//   - classDataMap: A map containing class names as keys and the corresponding number of data points as values
void kmeansRecognition(int minK,int maxK,int numClasses, std::map<std::string, int> classDataMap) {
    // Iterate through each class and its associated data size
    std::map<std::string, int>::iterator it;
    for (it = classDataMap.begin(); it != classDataMap.end(); ++it) {
        // Extract class name and the number of data points for the class
        std::string className = it->first;
        int numData = it->second;

        // Initialize an array to store results for different values of k
        vector<int> arrayK(maxK-minK+1);

        // Vary the value of k from minK to maxK
        for (int k = minK; k <= maxK; ++k) {
            // Retrieve data for the current class
            vector<ImageData> data = GetDataDirectory(className, numData, "");

            // Initialize the centroids
            vector<centroid> centroids;

            // Display class information
            cout << "------------------------------------------"<< endl;
            cout << className << endl;
            cout << "------------------------------------------"<< endl;

            // Perform k-means
            clock_t start = clock();
            kmeans(data,k,centroids,100,numClasses);
            clock_t end = clock();
            double time_taken = (end - start) / (double)CLOCKS_PER_SEC;

            cout <<"---------------------"<<endl<< "k = " << k << endl<<"---------------------"<<endl;
            cout << "kMeansRecognition execution time: " << time_taken << " seconds" << endl<<"---------------------"<<endl;
            // Display results
            arrayK[k - minK] = ShowResults(numClasses,data);
        }
        // Choose the best k based on the highest true positives
        int kbestval = minK;
        int maxVp = 0;
        for (int k = 0; k < arrayK.size(); ++k) {
            if (arrayK[k] >= maxVp) {
                kbestval = k+minK;
                maxVp = arrayK[k];
            }
        }
        cout << endl << "---------------------" << endl;
        cout << "BEST K VALUE : " << kbestval << " WITH VP : " << maxVp << endl;
        cout << "---------------------" << endl;   
    }
}

int main(int argc, char *argv[]) {
    // Check if the correct number of command-line arguments is provided
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <Algorithm> <minK> <maxK>" << std::endl;
        return 1;
    }

    // Extract command-line arguments
    std::string algorithm = argv[1];
    int minK = std::stoi(argv[2]);
    int maxK = std::stoi(argv[3]);

    // Perform actions based on the specified algorithm
    if (algorithm == "KNN") {
        std::cout << "---------------------" << std::endl;
        std::cout << "KNN" << std::endl;
        std::cout << "---------------------" << std::endl;

        // Call the k-NN recognition function with the specified parameters
        knnRecognition(minK, maxK, numClasses, classDataMap);
    } else if (algorithm == "KMEANS") {
        std::cout << "---------------------" << std::endl;
        std::cout << "KMEANS" << std::endl;
        std::cout << "---------------------" << std::endl;

        // Call the k-means recognition function with the specified parameters
        kmeansRecognition(minK, maxK, numClasses, classDataMap);
    } else {
        // Handle the case where an invalid algorithm is specified
        std::cerr << "Invalid algorithm specified. Use 'KNN' or 'KMEANS'." << std::endl;
        return 1;
    }

    return 0;
}


