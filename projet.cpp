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
    int trueLabel; // Class of the image
    int predictedLabel; // The predicted class
    vector<float> features; // Feature vector
    double distance; // Distance from the test ImageData

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


int main() {

    // Initialisation de `data`
    vector<ImageData> data;

    string dossier = "C:\\Users\\jiang\\OneDrive\\Documents\\RF\\E34";
    DIR* repertoire;
    struct dirent* fichier;
    repertoire = opendir(dossier.c_str());
    if (repertoire == NULL) {
        std::cout << "Erreur lors de l'ouverture du dossier." << std::endl;
        return 1;
    }
        // Parcourir les fichiers du dossier
    while ((fichier = readdir(repertoire)) != NULL) {
        std::string nomFichier = fichier->d_name;
        // Vérifier si le fichier est un fichier E34 en vérifiant l'extension
        if (nomFichier.find(".E34") != std::string::npos) {
            std::ifstream fichierE34(dossier + "\\" + nomFichier); // Ouvrir le fichier E34

            if (fichierE34) {
                std::string ligne;
                std::vector<float> valeurs; // Vecteur temp pour stocker les valeurs
                // Lire chaque ligne du fichier
                while (getline(fichierE34, ligne)) {
                    float valeur = stof(ligne);
                    valeurs.push_back(valeur); // Stocker la valeur lue dans le vecteur
                }
                ImageData imageData(valeurs.size());
                // Récupérer le deuxième chiffre du nom du fichier = la classe 
                int truelabel = std::stoi(nomFichier.substr(2, 1));
                imageData.features = valeurs;
                imageData.trueLabel = truelabel;
                fichierE34.close(); // Fermer le fichier E34
                data.push_back(imageData); // Met a jour le vecteur data
            }
            else {
                std::cout << "Erreur lors de l'ouverture du fichier : " << nomFichier << std::endl;
            }
        }
    }
    closedir(repertoire); // Fermer le rep

    // Afficher les features de data
    /*
    int index =1;
    for (const auto& imageData : data) {
        std::cout << "Data " << index << " :" ;
        for (const auto& feature : imageData.features) {
            std::cout << " " << feature;
        }
        index++;
        std::cout << std::endl;
    }
    */
    
    // Initialize the centroids
    vector<vector<float>> centroids;
    //init_centroids(centroids, data, numClasses);
    //assign_data_to_clusters(data,centroids);
    //update_centroids(data,centroids);
    kmeans(data,numClasses,centroids,200);
    return 0;
}