#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <dirent.h>
#include <sys/types.h>
#include <map>
using namespace std;
#include "knn.h" // Include the header file for knn
#include "kmeans.h" // Include the header file for kmeans

void knnRecognition(int numClasses,std::map<std::string, int> map1){
    std::map<std::string, int>::iterator it;
    for (it = map1.begin(); it != map1.end(); ++it) {
        std::string className = it->first;
        int numData = it->second;

        DIR *dr;
        struct dirent *en;
        dr = opendir(className.c_str()); // Open the directory
        vector<ImageData> arr; // Use a vector to store the ImageDatas

        if (dr) {
            while ((en = readdir(dr)) != NULL) {
                if (en->d_name[0] == '.') continue; // Ignore hidden files

                // Create the full file path
                string filePath = className+"Training" + "/" + string(en->d_name);

                // Open the file in read mode
                ifstream file(filePath);
                if (file.is_open()) {
                    ImageData p(numData);
                    int classLabel = stoi(en->d_name + 1); // Extract class number from the file name
                    p.trueLabel = classLabel;
                    //cout << p.trueLabel;
                    // Read the values from the file and store them in the features array
                    for (int i = 0; i < numData; ++i) {
                        float value;
                        file >> value;
                        p.features[i] = value;
                    }

                    // Add the ImageData to the vector
                    arr.push_back(p);

                    // Close the file
                    file.close();
                }
            }
            closedir(dr); // Close the directory
        }

    //////// TEST PART ////////

        dr = opendir((className + "Test").c_str()); // Open the directory
        vector<ImageData> test; // Use a vector to store the test ImageDatas

        if (dr) {
            while ((en = readdir(dr)) != NULL) {
                if (en->d_name[0] == '.') continue; // Ignore hidden files

                // Create the full file path
                string filePath = className + "Test" + "/" + string(en->d_name);

                // Open the file in read mode
                ifstream file(filePath);
                if (file.is_open()) {
                    ImageData p(numData);
                    int classLabel = stoi(en->d_name + 1); // Extract class number from the file name
                    p.trueLabel = classLabel;
                    //cout << p.trueLabel;
                    // Read the values from the file and store them in the features array
                    for (int i = 0; i < numData; ++i) {
                        float value;
                        file >> value;
                        p.features[i] = value;
                    }

                    // Add the ImageData to the vector
                    test.push_back(p);

                    // Close the file
                    file.close();
                }
            }
            closedir(dr); // Close the directory
        }
        cout << "---------------------"<< endl;
        cout << className << endl;
        cout << "---------------------"<< endl;

        // Vary the value of k from 1 to 6
        for (int k = 1; k <= 6; ++k) {
            //int correctClassifications = 0; // Reset the correct classification counter
            // Reset the predicted labels for each iteration
            for (vector<ImageData>::iterator t = test.begin(); t != test.end(); ++t) {
                int c = classifyImageData(arr.data(), arr.size(), k, *t, numClasses);
                t->predictedLabel = c;
            }   

            // Initialize confusion matrix
            vector<vector<int>> confusionMatrix(numClasses, vector<int>(numClasses, 0));

            // Populate confusion matrix
            for (vector<ImageData>::iterator t = test.begin(); t != test.end(); ++t) {
                confusionMatrix[t->predictedLabel - 1][t->trueLabel - 1]++;
            }

            // Display confusion matrix
            cout << "Confusion Matrix for k=" << k << endl;
            cout << "      ";
            for (int i = 0; i < numClasses; ++i) {
                cout << "C" << i+1 << " ";
            }
            cout << endl;

            for (int i = 0; i < numClasses; ++i) {
                cout << "C" << i+1 << " | ";
                for (int j = 0; j < numClasses; ++j) {
                    cout << confusionMatrix[i][j] << "    ";
                }
                cout << endl;
            }

            // Calculate true positives, false positives, and false negatives
            int vp = 0;
            for (int i = 0; i < numClasses; ++i) {
                vp += confusionMatrix[i][i];
            }

            // Calculate and print the success percentage for this value of k
            double successPercentage = (static_cast<double>(vp) / test.size()) * 100;
            printf("k=%d: Success Percentage: %.2f%% , vp: %d\n", k, successPercentage, vp);
        }

    }
}

void kmeansRecognition(int numClasses,std::map<std::string, int> map1){
    // Initialisation de `data`
    vector<ImageData> data;

    DIR* repertoire;
    struct dirent* fichier;
    string d = "E34";
    repertoire = opendir(d.c_str());
    if (repertoire == NULL) {
        std::cout << "Erreur lors de l'ouverture du dossier." << std::endl;
        return;
    }
    if (repertoire) {
        while ((fichier = readdir(repertoire)) != NULL) {
            if (fichier->d_name[0] == '.') continue; // Ignore hidden files

            // Create the full file path
            string filePath = d+"/" + string(fichier->d_name);

            // Open the file in read mode
            ifstream file(filePath);
            if (file.is_open()) {
                ImageData p(16);
                int classLabel = stoi(fichier->d_name + 1); // Extract class number from the file name
                p.trueLabel = classLabel;
                //cout << p.trueLabel;
                // Read the values from the file and store them in the features array
                for (int i = 0; i < 16; ++i) {
                    float value;
                    file >> value;
                    p.features[i] = value;
                }

                // Add the ImageData to the vector
                data.push_back(p);

                // Close the file
                file.close();
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
}



int main() {
    int numClasses = 9;
    std::map<std::string, int> map1 = {
        {"E34", 16},
        {"F0", 128},
        {"GFD", 100},
        {"SA", 90}
    };

    cout << "---------------------"<< endl;
    cout << "KNN" << endl;
    cout << "---------------------"<< endl;
    knnRecognition(numClasses,map1);
    cout << "---------------------"<< endl;
    cout << "KMEANS" << endl;
    cout << "---------------------"<< endl;
    kmeansRecognition(numClasses,map1);

    return 0;
}
