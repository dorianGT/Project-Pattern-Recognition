#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <dirent.h>
#include <sys/types.h>
#include <map>
using namespace std;
#include "knn.h" // Include the header file for knn

int main() {
    int numClasses = 9;
    std::map<std::string, int> map1 = {
        {"E34", 16},
        {"F0", 128},
        {"GFD", 100},
        {"SA", 90}
    };

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
                string filePath = className + "/" + string(en->d_name);

                // Open the file in read mode
                ifstream file(filePath);
                if (file.is_open()) {
                    ImageData p(numData);
                    int classLabel = stoi(en->d_name + 1); // Extract class number from the file name
                    p.val = classLabel;

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
                    p.val = classLabel;

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

        cout << className << endl;

        // Vary the value of k from 1 to 6
        for (int k = 1; k <= 6; ++k) {
            int correctClassifications = 0; // Reset the correct classification counter

            for (std::vector<ImageData>::iterator t = test.begin(); t != test.end(); ++t) {
                int c = classifyImageData(arr.data(), arr.size(), k, *t,numClasses);
                
                if (c == t->val) {
                    correctClassifications++; // Increment the correct classification counter
                }
            }

            // Calculate and print the success percentage for this value of k
            double successPercentage = (static_cast<double>(correctClassifications) / test.size()) * 100;
            printf("Success Percentage for k=%d: %.2f%%\n", k, successPercentage);
        }

    }
    return 0;
}
