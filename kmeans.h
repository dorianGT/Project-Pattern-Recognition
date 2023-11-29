#ifndef KMEANS_H
#define KMEANS_H

#include <vector>
#include "ImageData.h"
#include "UtilMethods.h"

// Perform k-means clustering on the given dataset
// Parameters:
//   data: The dataset to be clustered
//   k: The number of clusters
//   centroids: Output vector to store the final centroids of the clusters
//   max_iterations: The maximum number of iterations for the k-means algorithm
void kmeans(std::vector<ImageData>& data, int k, std::vector<centroid>& centroids, int max_iterations);

// Update the centroids based on the current assignment of data points to clusters
// Parameters:
//   data: The dataset
//   centroids: The centroids of clusters to be updated
void update_centroids(std::vector<ImageData>& data, std::vector<centroid>& centroids);

// Assign each data point to the cluster with the nearest centroid
// Parameters:
//   data: The dataset
//   centroids: The current centroids of clusters
void assign_data_to_clusters(std::vector<ImageData>& data, std::vector<centroid>& centroids);

// Initialize the centroids based on the initial configuration of the dataset
// Parameters:
//   centroids: Output vector to store the initialized centroids
//   data: The dataset used for initialization
//   k: The number of clusters
void init_centroids(std::vector<centroid>& centroids, const std::vector<ImageData>& data, int k);

#endif // KMEANS_H
