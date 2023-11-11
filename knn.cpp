#include <dirent.h>
using namespace std;
#include <iostream>
#include <bits/stdc++.h>
#include "knn.h" // Include the header file for knn

// Function to calculate Euclidean distance between two feature vectors
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
    return sqrt(sum);}

// Function to calculate Manhattan distance between two feature vectors
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
    return sum;}

// Used to sort an array of ImageDatas by increasing order of distance
bool comparison(ImageData a, ImageData b) {
    return (a.distance <= b.distance);
}

int classifyImageData(ImageData arr[], int n, int k, ImageData p,int numClasses) {
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
        frequencies[arr[i].trueLabel]++;
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
    predictedClass++;
    if(predictedClass == 1){
        predictedClass = 9;
    }
    else{
        predictedClass--;
    }
    return predictedClass;
}
