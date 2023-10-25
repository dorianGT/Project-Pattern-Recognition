// C++ program to find groups of unknown
// Points using K nearest neighbour algorithm.
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <dirent.h>
#include <sys/types.h>
#include <vector>
#include <map>
using namespace std;
 
int numClasses = 9;
string nameClasse = "E34";
std::map<string, int> map1 = {
    {"E34", 16},
    {"F0", 128},
    {"GFD", 100},
    {"SA", 90}};

struct Point
{
    int val;                              // Groupe du point
    vector<float> features;                // Vecteur de caractéristiques
    double distance;                       // Distance depuis le point de test

    Point(int size) : features(size, 0) {} // Initialisation du vecteur de caractéristiques
};
 
// This function finds classification of point p using
// k nearest neighbour algorithm. It assumes only two
// groups and returns 0 if p belongs to group 0, else
// 1 (belongs to group 1).


double calculateDistance(vector<float> features1, vector<float> features2)
{
    double sum = 0.0;
    // Assurez-vous que les deux vecteurs ont la même taille
    if (features1.size() != features2.size()) {
        cerr << "Erreur: Les vecteurs n'ont pas la même taille." << endl;
        return -1.0; // Ou utilisez une gestion d'erreur appropriée
    }

    for (int i = 0; i < features1.size(); ++i) {
        sum += pow(features1[i] - features2[i], 2);
    }
    return sqrt(sum);
}

double calculateDistanceManhattan(vector<float> features1, vector<float> features2)
{
    double sum = 0.0;
    // Assurez-vous que les deux vecteurs ont la même taille
    if (features1.size() != features2.size()) {
        cerr << "Erreur: Les vecteurs n'ont pas la même taille." << endl;
        return -1.0; // Ou utilisez une gestion d'erreur appropriée
    }

    for (int i = 0; i < features1.size(); ++i) {
        sum += abs(features1[i] - features2[i]);
    }
    return sum;
}


// Used to sort an array of points by increasing
// order of distance
bool comparison(Point a, Point b)
{
    return (a.distance < b.distance);
}
int classifyAPoint(Point arr[], int n, int k, Point p)
{
    // Remplir les distances de tous les points par rapport à p
    for (int i = 0; i < n; i++)
    {
        arr[i].distance = calculateDistance(arr[i].features, p.features);
    }

    // Trier les points par distance par rapport à p
    sort(arr, arr + n, comparison);

    // Utiliser un tableau pour stocker les fréquences de chaque classe
    vector<int> frequencies(numClasses, 0);

    // Considérer les premiers k éléments et compter les fréquences de chaque classe
    for (int i = 0; i < k; i++)
    {
        frequencies[arr[i].val]++;
    }

    // Trouver la classe avec la fréquence la plus élevée parmi les k voisins
    int maxFreq = frequencies[0];
    int predictedClass = 0;
    for (int i = 1; i < numClasses; ++i)
    {
        if (frequencies[i] > maxFreq)
        {
            maxFreq = frequencies[i];
            predictedClass = i;
        }
    }

    return predictedClass;
}

 
// Driver code
int main()
{
    int numData = map1[nameClasse];

    DIR *dr;
    struct dirent *en;
    dr = opendir(nameClasse.c_str()); // Ouvrir le répertoire
    vector<Point> arr; // Utiliser un vecteur pour stocker les points

    if (dr) {
        while ((en = readdir(dr)) != NULL) {
            if (en->d_name[0] == '.') continue; // Ignorer les fichiers cachés

            // Créer le chemin complet du fichier
            string filePath = nameClasse+"/" + string(en->d_name);

            // Ouvrir le fichier en mode lecture
            ifstream file(filePath);
            if (file.is_open()) {
                Point p(numData);
                int classLabel = stoi(en->d_name + 1); // Extraire le numéro de classe du nom du fichier
                p.val = classLabel;
                
                // Lire les 16 valeurs du fichier et les stocker dans le tableau features
                for (int i = 0; i < numData; ++i) {
                    float value;
                    file >> value;
                    p.features[i] = value;
                }

                // Ajouter le point au vecteur
                arr.push_back(p);

                // Fermer le fichier
                file.close();
            }
        }
        closedir(dr); // Fermer le répertoire
    } 

//////// TEST PART ////////

    dr = opendir((nameClasse + "Test").c_str()); // Ouvrir le répertoire
    vector<Point> test; // Utiliser un vecteur pour stocker les points

    if (dr) {
        while ((en = readdir(dr)) != NULL) {
            if (en->d_name[0] == '.') continue; // Ignorer les fichiers cachés

            // Créer le chemin complet du fichier
            string filePath = nameClasse + "Test"+"/" + string(en->d_name);

            // Ouvrir le fichier en mode lecture
            ifstream file(filePath);
            if (file.is_open()) {
                Point p(numData);
                int classLabel = stoi(en->d_name + 1); // Extraire le numéro de classe du nom du fichier
                p.val = classLabel;

                // Lire les 16 valeurs du fichier et les stocker dans le tableau features
                for (int i = 0; i < numData; ++i) {
                    float value;
                    file >> value;
                    p.features[i] = value;
                }

                // Ajouter le point au vecteur
                test.push_back(p);

                // Fermer le fichier
                file.close();
            }
        }
        closedir(dr); // Fermer le répertoire
    } 

   // Faites varier la valeur de k de 1 à 5
    for (int k = 1; k <= 6; ++k) {
        int correctClassifications = 0; // Réinitialiser le compteur des classifications correctes

        for (vector<Point>::iterator t = test.begin(); t != test.end(); ++t) {
            int c = classifyAPoint(arr.data(), arr.size(), k, *t);
            //printf("k=%d, Classified value: %d, Actual value: %d. ", k, c, t->val);
            if (c == t->val) {
                //printf("Classification Correct\n");
                correctClassifications++; // Incrémenter le compteur des classifications correctes
            } else {
                //printf("Classification Incorrect\n");
            }
        }

        // Calculer et afficher le pourcentage de réussite pour cette valeur de k
        double successPercentage = (static_cast<double>(correctClassifications) / test.size()) * 100;
        printf("Pourcentage de réussite pour k=%d : %.2f%%\n", k, successPercentage);
    }




    /*
    // Créer le point de test (vous devez remplir ses valeurs à partir du dernier fichier)
    Point testPoint;
    // Remplir les valeurs de testPoint à partir du dernier fichier ici...


    // Créer le chemin complet du fichier
    string filePath = "F0Test/s09n008.F0";

    // Ouvrir le fichier en mode lecture
    ifstream file(filePath);
    if (file.is_open()) {
        // Lire les 16 valeurs du fichier et les stocker dans le tableau features
        for (int i = 0; i < 128; ++i) {
            float value;
            file >> value;
            testPoint.features[i] = value;
            std::cout<<testPoint.features[i]<<endl;
        }

        // Fermer le fichier
        file.close();
    }
    // Parameter to decide group of the testing point
    int k = 5;
    printf ("The value classified to unknown point is %d.\n", classifyAPoint(arr.data(), arr.size(), k, testPoint));

*/
    return 0;
}