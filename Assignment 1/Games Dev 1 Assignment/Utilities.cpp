#include "Utilities.h"

TerrainMap create_map_from_file(ifstream& mapFile) {
    // Vars
    TerrainMap map;
    int width;
    int height;
    int entry;
    mapFile >> width;
    mapFile >> height;
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
    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            mapFile >> skipws >> character;
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

void writeNodeListToFile(NodeList& nodeList, string fileName)
{
    ofstream pathfindFile;
    // With Path.txt ending
    pathfindFile.open(fileName + "Path.txt");
    for (int i = 0; i < nodeList.size(); i++)
    {
        pathfindFile << "Node " << i << ": " << nodeList[i]->x << ", " << nodeList[i]->y << endl;
    }
    pathfindFile.close();
    // As output.txt
    pathfindFile.open("output.txt");
    for (int i = 0; i < nodeList.size(); i++)
    {
        pathfindFile << "Node " << i << ": " << nodeList[i]->x << ", " << nodeList[i]->y << endl;
    }
    pathfindFile.close();
}

void readFile(ifstream& argFile)
{
    char character;
    while (argFile >> noskipws >> character) {
        cout << character;
    }
}
