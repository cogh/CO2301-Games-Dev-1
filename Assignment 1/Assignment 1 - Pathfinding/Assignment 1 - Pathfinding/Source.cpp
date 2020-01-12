#include "Definitions.h"
#include "Search.h"
#include "SearchFactory.h"
#include "SearchNoStar.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    // Read file
    string line;
    std::ifstream test_file("mMap.txt");
    while (!test_file.fail() && !test_file.eof())
    {
        test_file >> line;
        cout << line << endl;
    }
    // Stall
    string stall;
    cin >> stall;
}