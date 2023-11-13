#ifndef KMEANS_H
#define KMEANS_H

#include <vector>
#include "ImageData.h"
#include "UtilMethods.h"

// Function declarations
void kmeans(vector<ImageData>& data, int k, vector<vector<float>>& centroids, int max_iterations);
void update_centroids(vector<ImageData>& data, vector<vector<float>>& centroids);
void assign_data_to_clusters(vector<ImageData>& data, vector<vector<float>>& centroids);
void init_centroids(vector<vector<float>>& centroids, const vector<ImageData>& data, int k);


#endif // KNN_H
