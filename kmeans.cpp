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

// Initialise centroides
void init_centroids(vector<vector<float>>& centroids, const vector<ImageData>& data, int k)
{
    srand(time(nullptr));
    for (int i = 0; i < k; i++) {
        const ImageData& imageData = data[rand() % data.size()];
        const vector<float>& features = imageData.features;
        centroids.push_back(features);
    }


    // Afficher les centroides generes
    /*
    cout << "affichage des centroids" << endl;
    int centroid_index = 1; // Variable de compteur pour l'indice du centroid
    
    for (const auto& centroid : centroids) {
        cout << "Centroid " << centroid_index << ": ";
        
        for (const auto& coordinate : centroid) {
            cout << coordinate << " ";
        }
        
        cout << endl;
        
        centroid_index++; 
    }
    */
    
}

void assign_data_to_clusters(vector<ImageData>& data, vector<vector<float>>& centroids) {
    // Boucle sur tous les datas
    for (int i = 0; i < data.size(); i++) {
        int closest_centroid_index = -1;
        float closest_distance = INFINITY;
        // calcul la distance eucli pour chaque centroides
        for (int j = 0; j < centroids.size(); j++) {
            float distance = calculateDistance(data[i].features, centroids[j]);

            if (distance < closest_distance) {
                closest_distance = distance;
                closest_centroid_index = j;
            }
        }

        // Data est associe au centroid le plus proche (+1 car sinon sa commence à 0)
        data[i].predictedLabel = closest_centroid_index + 1;
    }
    for (int i = 0; i < data.size(); i++) {
        cout << "fichier " << i+1<< " : "<< "Label : " << data[i].trueLabel << " Label Predit : "<< data[i].predictedLabel << endl;
    }

}

void update_centroids(vector<ImageData>& data, vector<vector<float>>& centroids) {
    // Loop over all centroids
    for (int i = 0; i < centroids.size(); i++) {
        // Calculate the sum of the features of all data points assigned to the centroid
        vector<float> sum(centroids[i].size(), 0);
        int count = 0;

        for (int j = 0; j < data.size(); j++) {
            if (data[j].predictedLabel == i) {
                for (int k = 0; k < sum.size(); k++) {
                    sum[k] += data[j].features[k];
                }
                count++;
            }
        }

        // Update the centroid by taking the average of the features of all data points assigned to it
        if (count > 0) {
            for (int k = 0; k < sum.size(); k++) {
                centroids[i][k] = sum[k] / count;
            }
        }
    }
}

void kmeans(vector<ImageData>& data, int k, vector<vector<float>>& centroids, int max_iterations)
{
    int iteration = 0;
    // Initialisation des centroïdes
    init_centroids(centroids, data, k);

    // Boucle principale de l'algorithme
    for (iteration = 0; iteration < max_iterations; iteration++) {

        vector<vector<float>> centroids_old = centroids; // Sauvegarde des anciens centroïdes

        // Assignation des points de données aux clusters
        assign_data_to_clusters(data, centroids);

        // Recalcul des centroïdes
        update_centroids(data, centroids);

        // Vérification de la convergence
        bool converged = true;
        for (int i = 0; i < centroids.size(); i++) {
            if (centroids[i] != centroids_old[i]) {
                converged = false;
                break;
            }
        }

        // Sortie de la boucle si convergence atteinte
        if (converged) {
            break;
        }
    }
    cout << "Nombre d'iterations : " << iteration << endl;
}