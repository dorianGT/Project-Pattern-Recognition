#include "UtilMethods.h"
#include <dirent.h>
using namespace std;
#include <iostream>
#include <bits/stdc++.h>

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
