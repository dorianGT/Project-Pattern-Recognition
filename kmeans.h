#ifndef KMEANS_H
#define KMEANS_H

#include <vector>
#include "ImageData.h"
#include "UtilMethods.h"

// Function declarations
void kmeans(vector<ImageData>& data, int k, vector<centroid>& centroids, int max_iterations);
void update_centroids(vector<ImageData>& data, vector<centroid>& centroids);
void assign_data_to_clusters(vector<ImageData>& data, vector<centroid>& centroids);
void init_centroids(vector<centroid>& centroids, const vector<ImageData>& data, int k);


#endif // KNN_H
