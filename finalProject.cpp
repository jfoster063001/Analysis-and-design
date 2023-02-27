//============================================================================
// Name        : finalProject.cpp
// Author      : Jackson Foster
// Version     : 1.0
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Course {
    //making the course object
    string code;
    string name;
    string prereqs;
    Course* left;
    Course* right;
    Course(string code, string name, string prereqs ) : code(code), name(name), prereqs(prereqs), left(nullptr), right(nullptr) {}
};

void insert(Course*& root, string code, string name, string prereqs) {
    //used for sorting the nodes into the tree
    if (root == nullptr) {
        root = new Course(code, name, prereqs);
    }
    else if (code < root->code) {
        insert(root->left, code, name, prereqs);
    }
    else {
        insert(root->right, code, name, prereqs);
    }
}

Course* search(Course* root, string code) {
    if (root == nullptr || root->code == code) {
        return root;
    }
    else if (code < root->code) {
        return search(root->left, code);
    }
    else {
        return search(root->right, code);
    }
}

void printInorder(Course* root) {
    if (root != nullptr) {
        printInorder(root->left);
        cout << root->code << ", " << root->name << endl;
        printInorder(root->right);
    }
}

int main() {
    Course* root = nullptr;
    cout << "\nWelcome to the course planner.\n" << endl;

    

    // Menu
    int choice;
    do {
        
        cout << "\n1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit\n" << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        if (choice == 1) {
            // Load data
            string filename;
            cout << "What file do you want to load?\n" << endl;
            cin >> filename;
            ifstream inputFile(filename);
            if (!inputFile.is_open()) {
                cerr << "Error: Failed to open "<< filename << endl;
            }

            string line;
            while (getline(inputFile, line)) {
                //this is building each class into the object
                stringstream ss(line);
                string code, name, prereq;
                getline(ss, code, ',');
                getline(ss, name, ',');
                getline(ss, prereq);
                insert(root, code, name, prereq);
            }
        }
        else if (choice == 2) {
            // Print course list
            cout << "Here is a sample schedule: \n\n" << endl;
            printInorder(root);
            cout << "\n\n" << endl;
        }
        else if (choice == 3) {
            // Print course
            string code;
            cout << "Enter course code: ";
            cin >> code;


            transform(code.begin(), code.end(), code.begin(), toupper);

            Course* course = search(root, code);
            if (course != nullptr) {
                cout << course->code << ", " << course->name << "\nPrerequisites:" << course->prereqs << endl;
            }
                
            else {
                cout << "Error: Course not found" << endl;
            }
        }
        else if (choice != 9) {
            cout << choice<<" is not a valid option." << endl;
        }
    } while (choice != 9);

    cout << "Thank you for using the course planner!" << endl;
    return 0;
}
