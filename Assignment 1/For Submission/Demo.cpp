#include "Demo.h"

class Demo {
public:
    int scale;
    I3DEngine* engine;
    IMesh* cubeMesh;
    IMesh* arrowMesh;
    vector<vector<TLNode*>> terrainGrid;
    vector<TLNode*> path;
    IModel* pathPlotter;
    int pathIndex;
    Demo(IMesh* argCubeMesh, IMesh* argArrowMesh, I3DEngine* argEngine, int argScale);
    int scale;
    I3DEngine* engine;
    IMesh* cubeMesh;
    IMesh* arrowMesh;
    vector<vector<TLNode*>> terrainGrid;
    vector<TLNode*> path;
    IModel* pathPlotter;
    int pathIndex;
    Demo(IMesh* argCubeMesh, IMesh* argArrowMesh, I3DEngine* argEngine, int argScale)
    {
        cubeMesh = argCubeMesh;
        arrowMesh = argArrowMesh;
        engine = argEngine;
        scale = argScale;
    }
    void setTerrain(TerrainMap argTerrainMap)
    {
        int mapSize = argTerrainMap.size();
        int leftBorder = -(mapSize * scale / 2);
        int backBorder = -(mapSize * scale / 2);
        // Expand map
        for (int y = mapSize - 1; y >= 0; y--) {
            vector<TLNode*> row;
            for (int x = 0; x < mapSize; x++) {
                TLNode* node = new TLNode();
                node->model = cubeMesh->CreateModel();
                row.push_back(node);
            }
            terrainGrid.push_back(row);
            cout << endl;
        }
        // Initialise TLNodes
        for (int y = mapSize - 1; y >= 0; y--) {
            for (int x = 0; x < mapSize; x++)
            {
                // Set skin
                string skinName;
                switch (argTerrainMap[x][y])
                {
                case 0:
                    skinName = "Sun.jpg";
                    break;
                case 1:
                    skinName = "wood1.jpg";
                    break;
                case 2:
                    skinName = "CueTip.jpg";
                    break;
                case 3:
                    skinName = "Grass1.jpg";
                    break;
                }
                terrainGrid[x][y]->model->SetSkin(skinName);

                // Set coordinates
                terrainGrid[x][y]->x = leftBorder + (x * scale);
                terrainGrid[x][y]->y = backBorder + (y * scale);
                if (argTerrainMap[x][y] == 0)
                {
                    terrainGrid[x][y]->model->MoveY(-scale);
                }
                terrainGrid[x][y]->model->SetPosition(terrainGrid[x][y]->x, 0, terrainGrid[x][y]->y);
            }
            cout << endl;
        }
    }
    void setPath(NodeList& argNodeList)
    {
        pathPlotter = arrowMesh->CreateModel();
        pathIndex = 0;
        for (int i = 0; i < argNodeList.size(); i++)
        {
            int x = argNodeList[i]->x;
            int y = argNodeList[i]->y;
            path.push_back(terrainGrid[x][y]);
        }
        pathPlotter->SetY(10);
        pathPlotter->Scale(0.5);
    }
    void runPath()
    {
        TLNode targetNode = *path[pathIndex];
        float xDistance = targetNode.x - pathPlotter->GetX();
        float zDistance = targetNode.y - pathPlotter->GetZ();
        pathPlotter->MoveX(xDistance * 0.01);
        pathPlotter->MoveZ(zDistance * 0.01);
        if (abs(xDistance) < 0.5 && abs(zDistance) < 0.5)
        {
            pathIndex++;
            cout << pathIndex;
        }
        if (pathIndex == path.size())
        {
            pathIndex = 0;
            TLNode resetNode = *path[pathIndex];
            pathPlotter->SetPosition(resetNode.x, 10, resetNode.y);
        }
    }
    void clearTerrain(string mapIdentifier);
    void clearPath(string mapIdentifier);
};