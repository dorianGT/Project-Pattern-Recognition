#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <dirent.h>
#include <sys/types.h>
#include <vector>
#include <map>
#include "ImageData.h"
#include "kmeans.h"
using namespace std;

// Initialize centroids
void init_centroids(vector<centroid>& centroids, const vector<ImageData>& data, int k)
{
    srand(time(nullptr));
    set<int> unique_labels;

    while (centroids.size() < k) {
        int random_index = rand() % data.size();
        const ImageData& imageData = data[random_index];
        const vector<float>& features = imageData.features;

        if (unique_labels.find(imageData.trueLabel) == unique_labels.end()) {
            centroid centroid(features.size());
            centroid.label = imageData.trueLabel;
            centroid.features = features;

            unique_labels.insert(imageData.trueLabel);
            centroids.push_back(centroid);
        }
    }


    // Display centroids
    /*
    cout << "affichage des centroids" << endl;
    int centroid_index = 1; // Variable de compteur pour l'indice du centroid
    
    for (const centroid& centroid : centroids) {
        cout << "Centroid " << centroid_index << ": ";
        
        for (const float& feature : centroid.features) {
            cout << feature << endl;
        }
        
        cout << endl;
        
        centroid_index++; 
    }
    */
    
}

void assign_data_to_clusters(vector<ImageData>& data, vector<centroid>& centroids) {
    // Loop on datas
    for (int i = 0; i < data.size(); i++) {
        int closest_centroid_index = -1;
        float closest_distance = INFINITY;
        // calcul la distance eucli pour chaque centroides
        for (int j = 0; j < centroids.size(); j++) {
            float distance = calculateDistance(data[i].features, centroids[j].features);

            if (distance < closest_distance) {
                closest_distance = distance;
                closest_centroid_index = j;
            }
        }

        // assign data to nearest centroid
        data[i].predictedLabel = centroids[closest_centroid_index].label;
    }
    /*
    //Display datas label
    for (int i = 0; i < data.size(); i++) {
        cout << "fichier " << i+1<< " : "<< "Label : " << data[i].trueLabel << " Label Predit : "<< data[i].predictedLabel << endl;
    }
    */
}

void update_centroids(vector<ImageData>& data, vector<centroid>& centroids) {
    // Loop over all centroids
    for (int i = 0; i < centroids.size(); i++) {
        // Calculate the sum of the features of all data points assigned to the centroid
        vector<float> sum(centroids[i].features.size(), 0);
        int count = 0;

        for (int j = 0; j < data.size(); j++) {
            if (data[j].predictedLabel == centroids[i].label) {
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

void kmeans(vector<ImageData>& data, int k, vector<centroid>& centroids, int max_iterations)
{
    int iteration = 0;
    // Initialisation des centroïdes
    init_centroids(centroids, data, k);

    // Main loop of algo
    for (iteration = 0; iteration < max_iterations; iteration++) {

        vector<centroid> centroids_old = centroids; // Sauvegarde des anciens centroïdes

        // Assign data to clusters
        assign_data_to_clusters(data, centroids);

        // Update the centroids
        update_centroids(data, centroids);

        // Verify the convergence
        bool converged = true;
        for (int i = 0; i < centroids.size(); i++) {
            if (centroids[i].features != centroids_old[i].features) {
                converged = false;
                break;
            }
        }

        // Force end of algo if convergence is true
        if (converged) {
            break;
        }
    }
    cout << "Nombre d'iterations : " << iteration << endl;
}
