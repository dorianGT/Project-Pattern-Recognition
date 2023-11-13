#include <dirent.h>
using namespace std;
#include <iostream>
#include <bits/stdc++.h>
#include "knn.h" // Include the header file for knn

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
        frequencies[arr[i].trueLabel-1]++;
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
    return predictedClass+1;
}
