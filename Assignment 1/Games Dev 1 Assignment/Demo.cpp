#include "Demo.h"

class Demo {
public:
    Demo(IMesh* argCubeMesh, int argScale)
    {
        cubeMesh = argCubeMesh;
    }
    bool searchActive;
    int iterations;
    IMesh* cubeMesh;
    vector<vector<TLNode*>> terrainGrid;
    deque<unique_ptr<SNode>> openList;
    deque<unique_ptr<SNode>> closedList;
    unique_ptr<SNode> start;
    unique_ptr<SNode> goal;
    int pathIndex;
    void setTerrain(TerrainMap argTerrainMap);
    void setPath(NodeList& argNodeList);
    void runPath();
    void clearTerrain(string mapIdentifier);
    void clearPath(string mapIdentifier);
    void startSearch(TerrainMap& terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList& path)
    {
        // Add start to open
        start->parent = 0;
        openList.push_back(move(start));

    }
    void continueSearch()
    {

    }
    void displaySearchProgress()
    {
        // Create empty display grid
        vector<vector<TLNode*>> displayGrid;
        int width = argTerrain.size();
        int height = argTerrain.size();
        for (int x = 0; x < width; x++) {
            vector<string> row;
            for (int y = 0; y < height; y++) {
                row.push_back("-");
            }
            displayGrid.push_back(row);
        }

        // Overwrite with terrain data
        /*for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                displayGrid[x][y] = to_string(argTerrain[x][y]);
            }
        }*/

        // Overwrite with node data
        for (auto iter = openList.begin(); iter != openList.end(); ++iter) {
            displayGrid[(*iter)->x][(*iter)->y] = "O";
        }
        for (auto iter = closedList.begin(); iter != closedList.end(); ++iter) {
            displayGrid[(*iter)->x][(*iter)->y] = "X";
        }

        // Display whole grid
        for (int y = displayGrid.size() - 1; y >= 0; y--) {
            for (int x = 0; x < displayGrid.size(); x++) {
                cout << displayGrid[x][y];
            }
            cout << endl;
        }
    }
};