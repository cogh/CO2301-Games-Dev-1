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
    // Vars
    TerrainMap map;
    ifstream file(arg_file_name);
    int width;
    int height;
    int entry;
    file >> width;
    file >> height;
    char character;
    // Create empty
    for (int x = 0; x < width; x++) {
        vector<ETerrainCost> row;
        for (int y = 0; y < height; y++) {
            row.push_back((ETerrainCost)0);
        }
        map.push_back(row);
    }
    // Assign values
    for (int y = height-1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            file >> skipws >> character;
            entry = character;
            map[x][y] = (ETerrainCost)(entry - '0');
        }
    }
    return map;
}

void displayNodePath(NodeList& argNodeList)
{
    for (int i = 0; i < argNodeList.size(); i++)
    {
        cout << "Node " << i << ": " << argNodeList[i]->x << ", " << argNodeList[i]->y << endl;
    }
}

void displayTerrainMap(TerrainMap argTerrainMap)
{
    for (int y = argTerrainMap.size() - 1; y >= 0; y--) {
        for (int x = 0; x < argTerrainMap.size(); x++) {
            cout << argTerrainMap[x][y];
        }
        cout << endl;
    }
}

int main() {
    // Create terrain
    TerrainMap map = TerrainMap();

    // Map name
    string mapName = "mMap.txt";

    // Create console manager
    ConsoleManager console_manager;

    // Set console manager
    console_manager.set_prompt("What to do?");
    console_manager.add_answer("Read file");
    console_manager.add_answer("Add map");
    console_manager.add_answer("Read map");
    console_manager.add_answer("Pathfind");
    console_manager.add_answer("Display coordinate");
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
            ifstream test_file(mapName);
            while (test_file >> noskipws >> character) {
                cout << character; // Or whatever
            }
        }
        // Add map
        else if (console_manager.answer == 2)
        {
            map = create_map_from_file(mapName);
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
            ISearch* search = NewSearch(BreadthFirst);
            unique_ptr<SNode> startNode(new SNode(startX, startY));
            unique_ptr<SNode> targetNode(new SNode(endX, endY));
            NodeList path;
            bool success = search->FindPath(map, move(startNode), move(targetNode), path);
            displayNodePath(path);
        }
        // Display coordinate
        else if (console_manager.answer == 5)
        {
            int targetX, targetY;
            cout << "x: ";
            cin >> targetX;
            cout << "y: ";
            cin >> targetY;
            cout << "Cost of (" << targetX << ", " << targetY << ")" << map[targetX][targetY] << endl;
        }
        // Exit
        else if (console_manager.answer == 6)
        {
            cout << "Exiting" << endl << endl;
            quit = true;
        }

        // Stall
        console_manager.stall();
        console_manager.clear();
    }
} 