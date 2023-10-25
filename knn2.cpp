// C++ program to find groups of unknown
// Points using K nearest neighbor algorithm.
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <dirent.h>
#include <sys/types.h>
#include <vector>
#include <map>
using namespace std;

int numClasses = 9;
string className = "E34";
std::map<string, int> map1 = {
    {"E34", 16},
    {"F0", 128},
    {"GFD", 100},
    {"SA", 90}};

struct ImageData
{
    int val;                              // Class of the image
    vector<float> features;                // Feature vector
    double distance;                       // Distance from the test ImageData

    ImageData(int size) : features(size, 0) {} // Initialize the feature vector
};

// Function to calculate Euclidean distance between two feature vectors
double calculateDistance(vector<float> features1, vector<float> features2)
{
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
double calculateDistanceManhattan(vector<float> features1, vector<float> features2)
{
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

// Used to sort an array of ImageDatas by increasing order of distance
bool comparison(ImageData a, ImageData b)
{
    return (a.distance < b.distance);
}

int classifyImageData(ImageData arr[], int n, int k, ImageData p)
{
    // Fill distances of all ImageDatas from p
    for (int i = 0; i < n; i++)
    {
        arr[i].distance = calculateDistance(arr[i].features, p.features);
    }

    // Sort ImageDatas by distance from p
    sort(arr, arr + n, comparison);

    // Use an array to store frequencies of each class
    vector<int> frequencies(numClasses, 0);

    // Consider first k elements and count frequencies of each class
    for (int i = 0; i < k; i++)
    {
        frequencies[arr[i].val]++;
    }

    // Find the class with the highest frequency among k neighbors
    int maxFreq = frequencies[0];
    int predictedClass = 0;
    for (int i = 1; i < numClasses; ++i)
    {
        if (frequencies[i] > maxFreq)
        {
            maxFreq = frequencies[i];
            predictedClass = i;
        }
    }

    return predictedClass;
}

// Driver code
int main()
{
    int numData = map1[className];

    DIR *dr;
    struct dirent *en;
    dr = opendir(className.c_str()); // Open the directory
    vector<ImageData> arr; // Use a vector to store the ImageDatas

    if (dr) {
        while ((en = readdir(dr)) != NULL) {
            if (en->d_name[0] == '.') continue; // Ignore hidden files

            // Create the full file path
            string filePath = className + "/" + string(en->d_name);

            // Open the file in read mode
            ifstream file(filePath);
            if (file.is_open()) {
                ImageData p(numData);
                int classLabel = stoi(en->d_name + 1); // Extract class number from the file name
                p.val = classLabel;

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

//////// TEST PART ////////

    dr = opendir((className + "Test").c_str()); // Open the directory
    vector<ImageData> test; // Use a vector to store the test ImageDatas

    if (dr) {
        while ((en = readdir(dr)) != NULL) {
            if (en->d_name[0] == '.') continue; // Ignore hidden files

            // Create the full file path
            string filePath = className + "Test" + "/" + string(en->d_name);

            // Open the file in read mode
            ifstream file(filePath);
            if (file.is_open()) {
                ImageData p(numData);
                int classLabel = stoi(en->d_name + 1); // Extract class number from the file name
                p.val = classLabel;

                // Read the values from the file and store them in the features array
                for (int i = 0; i < numData; ++i) {
                    float value;
                    file >> value;
                    p.features[i] = value;
                }

                // Add the ImageData to the vector
                test.push_back(p);

                // Close the file
                file.close();
            }
        }
        closedir(dr); // Close the directory
    }

   // Vary the value of k from 1 to 6
    for (int k = 1; k <= 6; ++k) {
        int correctClassifications = 0; // Reset the correct classification counter

        for (vector<ImageData>::iterator t = test.begin(); t != test.end(); ++t) {
            int c = classifyImageData(arr.data(), arr.size(), k, *t);
            //printf("k=%d, Classified value: %d, Actual value: %d. ", k, c, t->val);
            if (c == t->val) {
                //printf("Classification Correct\n");
                correctClassifications++; // Increment the correct classification counter
            } else {
                //printf("Classification Incorrect\n");
            }
        }

        // Calculate and print the success percentage for this value of k
        double successPercentage = (static_cast<double>(correctClassifications) / test.size()) * 100;
        printf("Success Percentage for k=%d: %.2f%%\n", k, successPercentage);
    }
    return 0;
}
