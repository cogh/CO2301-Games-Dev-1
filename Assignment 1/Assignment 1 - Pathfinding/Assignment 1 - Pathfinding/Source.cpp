#include "Definitions.h"
#include "Search.h"
#include "SearchFactory.h"
#include "SearchNoStar.h"
#include <fstream>
#include <iostream>
#include <string>
#include "ConsoleManager.h"

using namespace std;

TerrainMap create_map_from_file(string arg_file_name) {
    TerrainMap map;
    int width;
    int length;
    ifstream file(arg_file_name);
    char character;
    int entry;
    file >> width;
    file >> length;
    for (int x = 0; x < width; x++) {
        vector<ETerrainCost> row;
        for (int y = 0; y < width; y++) {
            //test_file >> character;
            file >> entry;
            row.push_back((ETerrainCost)entry);
        }
        map.push_back(row);
    }
    return map;
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
            while (!test_file.fail() && !test_file.eof())
            {
                test_file >> character;
                cout << character << endl;
            }
        }
        // Add map
        else if (console_manager.answer == 2)
        {
            map = create_map_from_file("mMap.txt");
        }
        // Read map
        else if (console_manager.answer == 2)
        {
            for (int x = 0; x < map.size(); x++)
            {
                for (int y = 0; y < map.size(); y++)
                {
                    cout << map[x][y];
                }
            }
        }
        // Exit
        else if (console_manager.answer == 3)
        {
            cout << "Exiting" << endl << endl;
            quit = true;
        }

        // Stall
        console_manager.stall();
        console_manager.clear();
    }
} 