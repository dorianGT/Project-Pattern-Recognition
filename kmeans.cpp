#include <iostream>
#include <limits>
#include <set>
#include <ctime>
#include "ImageData.h"
#include "kmeans.h"
using namespace std;

bool vector_contains(const std::vector<int>& values, int val) {
    for (size_t i = 0; i < values.size(); ++i) {
        if (values[i] == val) {
            return true;
        }
    }
    return false;
}


// Initialize the centroids based on the initial configuration of the dataset
// Parameters:
//   centroids: Output vector to store the initialized centroids
//   data: The dataset used for initialization
//   k: The number of clustersvoid
void init_centroids(vector<centroid>& centroids, const vector<ImageData>& data, int k) {
    srand(time(nullptr)); // Seed for random number generation

    vector<int> selectedIndices;

    // Continue until the desired number of centroids is reached
    while (centroids.size() < k) {
        int random_index = rand() % data.size(); // Choose a random index from the dataset

        if (!vector_contains(selectedIndices,random_index)) {
            const ImageData& imageData = data[random_index];
            const vector<float>& features = imageData.features;
            // Create a new centroid 
            centroid new_centroid(features.size()); // Create a new centroid with the same dimension as the feature vector
            new_centroid.features = features; // Set the features of the centroid
            centroids.push_back(new_centroid); // Add the new centroid to the list    
            selectedIndices.push_back(random_index); 
        }
    }
}

// Assign each data point to the cluster with the nearest centroid
// Parameters:
//   data: The dataset
//   centroids: The current centroids of clusters
void assign_data_to_clusters(vector<ImageData>& data, vector<centroid>& centroids) {
    // Loop through all data points
    for (int i = 0; i < data.size(); i++) {
        int closest_centroid_index = -1;
        float closest_distance = numeric_limits<double>::infinity();

        // Calculate the Euclidean distance for each centroid
        for (int j = 0; j < centroids.size(); j++) {
            float distance = calculateDistance(data[i].features, centroids[j].features);

            // Update the closest centroid if a closer one is found
            if (distance < closest_distance) {
                closest_distance = distance;
                closest_centroid_index = j;
            }
        }

        // Assign data to the nearest centroid
        data[i].centroid_index = closest_centroid_index;
    }
}

// Update the centroids based on the current assignment of data points to clusters
// Parameters:
//   data: The dataset
//   centroids: The centroids of clusters to be updated
void update_centroids(vector<ImageData>& data, vector<centroid>& centroids) {
    // Loop over all centroids
    for (int i = 0; i < centroids.size(); i++) {
        // Calculate the sum of the features of all data points assigned to the centroid
        vector<float> sum(centroids[i].features.size(), 0);
        int count = 0;

        // Iterate through all data points
        for (int j = 0; j < data.size(); j++) {
            // Check if the data point belongs to the current centroid's cluster
            if (data[j].centroid_index == i) {
                // Accumulate the features of the data point to update the centroid
                for (int k = 0; k < sum.size(); k++) {
                    sum[k] += data[j].features[k];
                }
                count++;
            }
        }

        // Update the centroid by taking the average of the features of all data points assigned to it
        if (count > 0) {
            for (int k = 0; k < sum.size(); k++) {
                centroids[i].features[k] = sum[k] / count;
            }
        }
    }
}

void assign_label_to_data_cluster(vector<ImageData>& data, vector<centroid>& centroids,int numClasses) {

    for (int i = 0; i < centroids.size(); i++) {
        // Use an array to store frequencies of each class
        vector<int> frequencies(numClasses, 0);
        for(int j = 0;j<data.size();j++){
            if(data[j].centroid_index == i){
                frequencies[data[j].trueLabel - 1]++;
            }
        }
    
        // Find the class with the highest frequency among k neighbors
        int maxFreq = frequencies[0];
        int predictedClass = 0;
        for (int i = 1; i < numClasses; ++i) {
            if (frequencies[i] > maxFreq) {
                maxFreq = frequencies[i];
                predictedClass = i;
            }
        }

        // Loop through all data points
        for(int j = 0;j<data.size();j++){
            if(data[j].centroid_index == i){
                data[j].predictedLabel = predictedClass+1;
            }
        }
    }
}

// Perform k-means clustering on the given dataset
// Parameters:
//   data: The dataset to be clustered
//   k: The number of clusters
//   centroids: Output vector to store the final centroids of the clusters
//   max_iterations: The maximum number of iterations for the k-means algorithm
//   numClasses: Number of classes in the dataset
void kmeans(vector<ImageData>& data, int k, vector<centroid>& centroids, int max_iterations,int numClasses) {
    int iteration = 0;
    // Initialize centroids
    init_centroids(centroids, data, k);

    // Main loop of the k-means algorithm
    for (iteration = 0; iteration < max_iterations; iteration++) {
        vector<centroid> centroids_old = centroids; // Save the old centroids

        // Assign data points to clusters
        assign_data_to_clusters(data, centroids);

        // Update the centroids
        update_centroids(data, centroids);

        // Verify convergence by comparing new centroids with the old ones
        bool converged = true;
        for (int i = 0; i < centroids.size(); i++) {
            if (centroids[i].features != centroids_old[i].features) {
                converged = false;
                break;
            }
        }

        // End the algorithm if convergence is achieved
        if (converged) {
            break;
        }
    }

    // Function to choose the label of each cluster, so the label of each image in the cluster
    assign_label_to_data_cluster(data, centroids,numClasses);

    cout << "Number of iterations: " << iteration << endl;
}
