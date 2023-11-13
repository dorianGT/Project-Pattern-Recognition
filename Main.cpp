#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <dirent.h>
#include <sys/types.h>
#include <map>
using namespace std;
#include "knn.h" // Include the header file for knn
#include "kmeans.h" // Include the header file for kmeans

// Define a function to get the number of digits in an integer
int numDigits(int num) {
    int count = 0;
    while (num != 0) {
        num /= 10;
        ++count;
    }
    return count;
}

// Function to display the confusion matrix
void displayConfusionMatrix(const vector<vector<int>>& confusionMatrix, int numClasses) {
    // Display confusion matrix
    cout << "Confusion Matrix" << endl;
    cout << "      ";
    int maxDigits = 2;

    // Adjust column width based on the maximum number of digits in any matrix element
    for (int i = 0; i < numClasses; ++i) {
        for (int j = 0; j < numClasses; ++j) {
            int digits = numDigits(confusionMatrix[j][i]);
            if (digits > maxDigits) {
                maxDigits = digits;
            }
        }
    }

    // Set a minimum column width
    maxDigits = max(maxDigits, 3);

    cout << setw(3) << "C1 ";
    for (int i = 1; i < numClasses; ++i) {
        cout << setw(2) << "C" << i + 1 << " ";
    }

    cout << endl;

    for (int i = 0; i < numClasses; ++i) {
        cout << "C" << i + 1 << " | ";
        int digits = numDigits(confusionMatrix[i][0]);
        cout << setw(maxDigits) << confusionMatrix[i][0] << " ";

        for (int j = 1; j < numClasses; ++j) {
            // Center-align each matrix element within its column
            int digits = numDigits(confusionMatrix[i][j]);
            cout << setw(maxDigits) << confusionMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void ShowResults(int numClasses,vector<ImageData>& dataResult){
    // Initialize confusion matrix
    vector<vector<int>> confusionMatrix(numClasses, vector<int>(numClasses, 0));

    // Populate confusion matrix
    for (vector<ImageData>::iterator t = dataResult.begin(); t != dataResult.end(); ++t) {
        confusionMatrix[t->predictedLabel - 1][t->trueLabel - 1]++;
    }

    // Display confusion matrix
    displayConfusionMatrix(confusionMatrix,numClasses);

    // Calculate true positives
    int vp = 0;
    for (int i = 0; i < numClasses; ++i) {
        vp += confusionMatrix[i][i];
    }

    // Calculate and print the success percentage for this value of k
    double successPercentage = (static_cast<double>(vp) / dataResult.size()) * 100;
    printf("Success Percentage: %.2f%% , vp: %d\n", successPercentage, vp);
}

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

            ShowResults(numClasses,test);
        }

    }
}

void kmeansRecognition(int numClasses,std::map<std::string, int> map1){
    std::map<std::string, int>::iterator it;
    for (it = map1.begin(); it != map1.end(); ++it) {
        std::string className = it->first;
        int numData = it->second;
        // Initialisation de `data`
        vector<ImageData> data;

        DIR* repertoire;
        struct dirent* fichier;
        repertoire = opendir(className.c_str());
        if (repertoire == NULL) {
            std::cout << "Erreur lors de l'ouverture du dossier." << std::endl;
            return;
        }
        if (repertoire) {
            while ((fichier = readdir(repertoire)) != NULL) {
                if (fichier->d_name[0] == '.') continue; // Ignore hidden files

                // Create the full file path
                string filePath = className+"/" + string(fichier->d_name);

                // Open the file in read mode
                ifstream file(filePath);
                if (file.is_open()) {
                    ImageData p(numData);
                    int classLabel = stoi(fichier->d_name + 1); // Extract class number from the file name
                    p.trueLabel = classLabel;
                    //cout << p.trueLabel;
                    // Read the values from the file and store them in the features array
                    for (int i = 0; i < numData; ++i) {
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
        cout << "---------------------"<< endl;
        cout << className << endl;
        cout << "---------------------"<< endl;
        kmeans(data,numClasses,centroids,100);
        ShowResults(numClasses,data);
    }
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
