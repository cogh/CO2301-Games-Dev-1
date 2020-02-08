#pragma once
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

void displayNodePath(NodeList& argNodeList)
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
