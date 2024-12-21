

/* Note:
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include "AVL.h"
using namespace std;



int main() {
    AVLTree AVlTree;

    int commandAmount;
    cin >> commandAmount; // read commands number
    cin.ignore();

    string command;
    for (int i = 0; i < commandAmount; i++) {
        getline(cin, command);

        if (command.substr(0, 6) == "insert") {
            size_t startq = command.find('"');
            size_t finishq = command.rfind('"');
            string name = command.substr(1 + startq, finishq - startq - 1);

            size_t dif = command.find(' ', finishq);
            int UFID = stoi(command.substr(dif + 1));
            AVlTree.insert(name, UFID);
        }
        else if (command == "printInorder") {
            AVlTree.printInorder();
        }
        else if (command == "printPreorder") {
            AVlTree.printPreorder();
        }
        else if (command == "printPostorder") {
            AVlTree.printPostorder();
        }
        else if (command == "printLevelCount") {
            AVlTree.printLevelCount();
        }
        else if (command.substr(0, 14) == "removeInorder ") {
            int N = stoi(command.substr(14));
            AVlTree.removeInorder(N);
        }
        else if (command.substr(0, 10) == "searchByName") {
            size_t startq = command.find('"');
            size_t finishq = command.rfind('"');
            string UFiD = command.substr(1 + startq, finishq - startq - 1);
            AVlTree.searchSecond(UFiD);
        }
        else if (command.substr(0, 7) == "remove ") {
            int UFID = stoi(command.substr(7));
            AVlTree.remove(UFID);
        }
        else if (command.substr(0, 6) == "search") {
            string line = command.substr(7);

            if (!isdigit(line[0])) {
                line.erase(remove(line.begin(), line.end(), '"'), line.end());
                AVlTree.search(0, line);

            }
            else {
                int UFID = stoi(line);
                AVlTree.search(UFID);
            }
        }
        
        else {
            cout << "unsuccessful" << endl;
        }
    }

    return 0;
}

