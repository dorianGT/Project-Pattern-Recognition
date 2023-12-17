# Project-Pattern-Recognition
 The objective of the project is to evaluate, on a small complex basis, the behavior of classics methods of shape recognition (ME34, MGFD, etc.) by associating their representation with a classifier.

# Using the Executable - Tutorial

To use the executable, follow these steps:

## 1. Navigate to the Directory:
Open the command prompt (`cmd`) and navigate to the directory where your executable file is located. You can use the cd command to change directories.
`cd path\to\your\directory`

## 2. Run the Executable:
Type the following command to run the executable:
Main `<Algorithm>` `<minK>` `<maxK>`

Replace `<Algorithm>`, `<minK>`, and `<maxK>` with the appropriate values.

`<Algorithm>` can take the value KNN or KMEANS.
`<minK>` and `<maxK>` should be integer values.

For example:
`Main KNN 3 8`
This command runs the executable using the KNN algorithm for each value of `K` ranging from `3` to `8`.

## 3. Execute the Program:
Press Enter to execute the program with the specified parameters.

Your program will now run with the chosen algorithm and parameter values.

Example:

`cd path\to\your\directory`

`Main KMEANS 2 5`

This command runs the program with the KMEANS algorithm for each value of `K` ranging from `2` to `5`.

# Building the Executable - Tutorial

To build the executable, follow these steps in the command prompt (cmd):

## 1. Navigate to the Source Code Directory:

Open the command prompt (`cmd`) and navigate to the directory where your executable file is located. You can use the cd command to change directories.
`cd path\to\your\source\code`

## 2. Use the g++ compiler to compile your source code files and generate the executable. In this project, we have source code files Main.cpp, knn.cpp, kmeans.cpp, and UtilMethods.cpp.
`g++ Main.cpp knn.cpp kmeans.cpp UtilMethods.cpp -o Main`

This command compiles the source code files and links them to create the executable named Main.
