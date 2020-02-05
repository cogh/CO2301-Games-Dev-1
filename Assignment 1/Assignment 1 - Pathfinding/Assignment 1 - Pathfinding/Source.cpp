#include "Definitions.h"
#include "Search.h"
#include "SearchFactory.h"
#include "SearchNoStar.h"
#include "SearchBreadth.h"
#include <fstream>
#include <iostream>
#include <string>
#include "ConsoleManager.h"
#include <sstream>

using namespace std;

TerrainMap create_map_from_file(string arg_file_name) {
    TerrainMap map;
    ifstream file(arg_file_name);
    int width;
    int length;
    int entry;
    file >> width;
    file >> length;
    char character;
    for (int x = 0; x < width; x++) {
        vector<ETerrainCost> row;
        for (int y = 0; y < length; y++) {
            file >> skipws >> character;
            entry = character;
            row.push_back((ETerrainCost)(entry - '0'));
        }
        map.push_back(row);
    }
    return map;
}

void displayNodePath(NodeList &argNodeList) 
{
    for (int i = 0; i < argNodeList.size(); i++)
    {
        cout << "Node " << i << ": " << argNodeList[i]->x << ", " << argNodeList[i]->y << endl;
    }
}

void displayTerrainMap(TerrainMap argTerrainMap) 
{
    for (int x = 0; x < argTerrainMap.size(); x++)
    {
        for (int y = 0; y < argTerrainMap.size(); y++)
        {
            cout << argTerrainMap[x][y];
        }
        cout << endl;
    }
}

int main() {
    // Create terrain
    TerrainMap map = TerrainMap();

    // Create console manager
    ConsoleManager console_manager;

    // Set console manager
    console_manager.set_prompt("What to do?");
    console_manager.add_answer("Read file");
    console_manager.add_answer("Add map");
    console_manager.add_answer("Read map");
    console_manager.add_answer("Pathfind");
    console_manager.add_answer("Exit");

    // Game loop
    bool quit = false;
    while (!quit) 
    {
        // Get answer
        console_manager.run();

        // Read file
        if (console_manager.answer == 1) 
        {
            char character;
            ifstream test_file("mMap.txt");
            while (test_file >> noskipws >> character) {
                cout << character; // Or whatever
            }
        }
        // Add map
        else if (console_manager.answer == 2)
        {
            map = create_map_from_file("mMap.txt");
            cout << "Added.";
        }
        // Read map
        else if (console_manager.answer == 3)
        {
            displayTerrainMap(map);
        }
        // Pathfind
        else if (console_manager.answer == 4)
        {
            int startX, startY, endX, endY;
            cout << "Starting x: ";
            cin >> startX;
            cout << "Starting y: ";
            cin >> startY;
            cout << "End x: ";
            cin >> endX;
            cout << "End y: ";
            cin >> endY;
            ISearch* search = NewSearch(NoStar);
            unique_ptr<SNode> startNode(new SNode(startX, startY));
            unique_ptr<SNode> targetNode(new SNode(endX, endY));
            NodeList path;
            bool success = search->FindPath(map, move(startNode), move(targetNode), path);
            displayNodePath(path);
        }
        // Exit
        else if (console_manager.answer == 5)
        {
            cout << "Exiting" << endl << endl;
            quit = true;
        }

        // Stall
        console_manager.stall();
        console_manager.clear();
    }
} 