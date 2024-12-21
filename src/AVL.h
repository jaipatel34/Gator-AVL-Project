
#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
using namespace std;

// Student class
class Student {
public:
    int UFID;
    string name;


    Student(string name, int UFID) {
        this->name = name;
        this->UFID = UFID;
    }
    ~Student() {
    }
};


// AVL Tree class
class AVLTree {
private:
    // AVL Node class
    class AVLNodes {
    public:
        Student* studentS;
        AVLNodes* left;
        AVLNodes* right;
        int height;

        AVLNodes(Student *studentS) {
            this->studentS = studentS;

            this->left = nullptr;
            this->right = nullptr;
            this->height = 1;
        }

    };

    AVLNodes* theRoot;

    // get height
    int height(AVLNodes* theNode) {
        if (theNode == nullptr) {
            return 0;
        }
        return theNode->height;
    }
    // get balance
    int Balance(AVLNodes* theNode) {
        if (theNode == nullptr) {
            return 0;
        }
        return height(theNode->left) - height(theNode->right);    }


    // Right rotate
    AVLNodes* rightRotate(AVLNodes* rhs) {
        AVLNodes* lhs = rhs->left;
        AVLNodes* m = lhs->right;
        lhs->right = rhs;
        rhs->left = m;
        rhs->height = max(height(rhs->left), height(rhs->right)) + 1;
        lhs->height = max(height(lhs->left), height(lhs->right)) + 1;
        return lhs;
    }
    // Postorder
    void postorder(AVLNodes* theNode, vector<string>& names) {
        if (theNode == nullptr)
            return;
        postorder(theNode->left, names);
        postorder(theNode->right, names);
        names.push_back(theNode->studentS->name);
    }
    // Left rotate
    AVLNodes* leftRotate(AVLNodes* lhs) {
        AVLNodes* rhs = lhs->right;
        AVLNodes* m = rhs->left;
        rhs->left = lhs;
        lhs->right = m;
        lhs->height = max(height(lhs->left), height(lhs->right)) + 1;
        rhs->height = max(height(rhs->left), height(rhs->right)) + 1;
        return rhs;
    }



    // search by ID
    AVLNodes* search(AVLNodes* theNode, int UFID, const string& name) {
        if (theNode == nullptr) {
            return nullptr;
        }
        if (UFID < theNode->studentS->UFID) {
            return search(theNode->left, UFID, name);
        }
        if (theNode->studentS->name == name || theNode->studentS->UFID == UFID) {
            return theNode;
        }

        else {
            return search(theNode->right, UFID, name);
        }
    }

    // Insert helper function
    AVLNodes* insert(AVLNodes* theNode, Student* studentS, bool& successful) {

        if (theNode == nullptr) {
            successful = true;
            return new AVLNodes(studentS);
        }

        if (studentS->UFID < theNode->studentS->UFID) {
            theNode->left = insert(theNode->left, studentS, successful);
        }
        else if (studentS->UFID > theNode->studentS->UFID) {
            theNode->right = insert(theNode->right, studentS, successful);
        }
        else {
            successful = false;
            return theNode;
        }

        int balance = Balance(theNode);

        theNode->height = 1 + max(height(theNode->left), height(theNode->right));


        // Right Right
        if (balance < -1 && studentS->UFID > theNode->right->studentS->UFID)
            return leftRotate(theNode);

        // Right Left
        if (balance < -1 && studentS->UFID < theNode->right->studentS->UFID) {
            theNode->right = rightRotate(theNode->right);
            return leftRotate(theNode);

        }
        // Left Left
        if (balance > 1 && studentS->UFID < theNode->left->studentS->UFID)
            return rightRotate(theNode);
        // Left Right
        if (balance > 1 && studentS->UFID > theNode->left->studentS->UFID) {
            theNode->left = leftRotate(theNode->left);
            return rightRotate(theNode);
        }

        return theNode;
    }
    // Preorder
    void preorder(AVLNodes* theNode, vector<string>& names) {
        if (theNode == nullptr)
            return;
        names.push_back(theNode->studentS->name);
        preorder(theNode->left, names);
        preorder(theNode->right, names);
    }
    // search by name
    void searchSecond(AVLNodes* theNode, const string& name, vector<int>& UFIDs) {
        if (theNode == nullptr) {
            return;
        }

        if (theNode->studentS->name == name) {
            UFIDs.push_back(theNode->studentS->UFID);
        }

        searchSecond(theNode->left, name, UFIDs);
        searchSecond(theNode->right, name, UFIDs);
    }

    // Delete Node
    AVLNodes* remove(AVLNodes* theNode, int UFID, bool& successful) {
        if (theNode == nullptr) {
            successful = false;
            return theNode;
        }

        if (UFID < theNode->studentS->UFID) {
            theNode->left = remove(theNode->left, UFID, successful);
        }
        else if (UFID > theNode->studentS->UFID) {
            theNode->right = remove(theNode->right, UFID, successful);
        }
        else {
            successful = true;

            //Node with no child
            if (theNode->right == nullptr && theNode->left == nullptr) {
                delete theNode;
                return nullptr;
            }

            //Node with one child
            if (theNode->right == nullptr || theNode->left == nullptr) {
                AVLNodes* var;
                if (theNode->left) {
                    var = theNode->left;
                } else {
                    var = theNode->right;
                }
                delete theNode;
                return var;
            }

            // Node with two children
            AVLNodes* var = MinValueNode(theNode->right);
            theNode->studentS->name = var->studentS->name;
            theNode->studentS->UFID = var->studentS->UFID;

            theNode->right = remove(theNode->right, var->studentS->UFID, successful);
        }

        theNode->height = 1 + max(height(theNode->left), height(theNode->right));

        return theNode;
    }

    // Helper function to get minimum value node
    AVLNodes* MinValueNode(AVLNodes* theNode) {
        AVLNodes* curr = theNode;
        while (curr->left != nullptr) {
            curr = curr->left;
        }
        return curr;
    }


    // Inorder
    void inorder(AVLNodes* theNode, vector<string>& names) {
        if (theNode == nullptr)
            return;
        inorder(theNode->left, names);
        names.push_back(theNode->studentS->name);
        inorder(theNode->right, names);
    }

    //Helper function to remove inorder
    void removeInorderHelper(AVLNodes*& theNode, int N, int &location, bool& successful) {
        if (successful ||theNode == nullptr) {
            return;
        }

        removeInorderHelper(theNode->left, N, location, successful);

        if (!successful && location == N) {
            theNode = remove(theNode, theNode->studentS->UFID, successful);
            successful = true;
            return;
        }
        location++;
        removeInorderHelper(theNode->right,  N, location, successful);
    }
    // print names
    void printNames(const vector<string>& names) {
        for (size_t i = 0; i < names.size(); i++) {
            cout << names[i];
            if (i < (names.size()) - 1)
                cout << ", ";
        }
        cout << endl;
    }

public:
    AVLTree() {
        theRoot = nullptr;
    }
    ~AVLTree() {
        delete theRoot;
    }

    // Insert function
    void insert(string name, int UFID) {


        if (to_string(UFID).length() != 8) {
            cout << "unsuccessful"<< endl;
            return;
        }


        for (char ch : name) {
            if (ch != ' ' && !isalpha(ch)) {
                cout << "unsuccessful" << endl;
                return;
            }
        }

        Student* studentS = new Student(name, UFID);
        bool successful = false;
        theRoot = insert(theRoot, studentS, successful);

        if (successful == true) {
            cout << "successful" << endl;
        }
        else {
            cout << "unsuccessful" << endl;
        }
    }

    // remove
    void remove(int UFID) {
        bool successful = false;
        theRoot = remove(theRoot, UFID, successful);

        if (successful== true) {
            cout << "successful" << endl;
        }
        else {
            cout << "unsuccessful" << endl;
        }
    }
    //search by id
    void search(int UFID, const string& name = "") {
        if (!name.empty()) {
            vector<int> UFIDs;
            searchSecond(theRoot, name, UFIDs);

            if (UFIDs.empty()) {
                cout << "unsuccessful" << endl;
            }
            else {
                for (int UFid : UFIDs) {
                    cout << UFid << endl;
                }
            }
        }
        else {
            AVLNodes* result = search(theRoot, UFID, name);
            if (result != nullptr) {
                cout << result->studentS->name << endl;
            }
            else {
                cout << "unsuccessful" << endl;
            }
        }
    }

    //search by name
    void searchSecond(const string& byName) {
        vector<int> UFIDs;
        searchSecond(theRoot, byName, UFIDs);

        if (UFIDs.empty()) {
            cout << "unsuccessful" << endl;
        }
        else {
            for (int UFid : UFIDs) {
                cout << UFid << endl;
            }
        }
    }



    // Print inorder
    void printInorder() {
        vector<string> nam;
        inorder(theRoot, nam);
        printNames(nam);
    }


    // Print postorder
    void printPostorder() {
        vector<string> nam;
        postorder(theRoot, nam);
        printNames(nam);
    }


    // remove the Nth theNode in inorder
    void removeInorder(int Nth) {
        int location = 0;
        bool successful = false;
        removeInorderHelper(theRoot, Nth, location, successful);

        if (successful) {
            cout << "successful" << endl;
        }
        else {
            cout << "unsuccessful" << endl;
        }
    }
    //print Level Count
    void printLevelCount() {
        if (theRoot == nullptr) {
            cout << "0" << endl;
        }
        else {
            cout << height(theRoot)<< endl;
        }
    }
    // Print preorder
    void printPreorder() {
        vector<string> nam;
        preorder(theRoot, nam);
        printNames(nam);
    }


};
#endif // AVL_H