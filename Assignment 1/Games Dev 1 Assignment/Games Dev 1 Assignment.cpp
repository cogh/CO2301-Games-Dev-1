/*** AARON ARMSTRONG***/

// Games Dev 1 Assignment.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
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
#include "Utilities.h"

using namespace tle;

class TLNode {
public:
    IModel* model;
    int x;
    int y;
};

class Demo {
public:
    Demo(IMesh* argCubeMesh, IMesh* argArrowMesh, I3DEngine* argEngine, int argScale)
    {
        cubeMesh = argCubeMesh;
        arrowMesh = argArrowMesh;
        engine = argEngine;
        scale = argScale;
    }
    int scale;
    I3DEngine* engine;
    IMesh* cubeMesh;
    IMesh* arrowMesh;
    vector<vector<TLNode*>> terrainGrid;
    vector<TLNode*> path;
    IModel* pathPlotter;
    int pathIndex;
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


void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( "C:\\ProgramData\\TL-Engine\\Media" );

	// Meshes
	IMesh* cubeMesh = myEngine->LoadMesh("Cube.x");
    IMesh* arrowMesh = myEngine->LoadMesh("Sphere.x");

    // Demo
    Demo demo(cubeMesh, arrowMesh, myEngine, 10);

	// Camera
	ICamera* camera = myEngine->CreateCamera(kManual);
	camera->MoveZ(-50);
	camera->MoveY(50);
	camera->RotateX(45);

    // Current algorithm type
    ESearchType currentAlgorithm = AStar;

    // Create terrain
    TerrainMap map = TerrainMap();

    // Start and end nodes
    SNode* startNode = new SNode();
    SNode* endNode = new SNode();

    // Create path
    NodeList path;

    // Map identifier
    string mapIdentifier = "m";
    
    // Create console manager
    ConsoleManager console_manager;
    bool runConsoleManager = true;

    // Set console manager
    console_manager.set_prompt("What to do?");
    console_manager.add_answer("Choose map identifier");
    console_manager.add_answer("Read file");
    console_manager.add_answer("Add map");
    console_manager.add_answer("Read map");
    console_manager.add_answer("Set default coordinates");
    console_manager.add_answer("Set custom coordinates");
    console_manager.add_answer("Generate path");
    console_manager.add_answer("Read path");
    console_manager.add_answer("Graphical display");
    console_manager.add_answer("Exit");
    console_manager.add_answer("Change algorithm");

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
        // Run console
        while (runConsoleManager)
        {
            // Get answer
            console_manager.run();

            // Choose map identifier
            if (console_manager.answer == 1)
            {
                cout << "Choose map identifier (one character):" << endl;
                cin >> mapIdentifier;
            }
            // Read file
            if (console_manager.answer == 2)
            {
                char character;
                ifstream mapFile(mapIdentifier + "Map.txt");
                readFile(mapFile);
            }
            // Add map
            else if (console_manager.answer == 3)
            {
                ifstream mapFile(mapIdentifier + "Map.txt");
                map = create_map_from_file(mapFile);
                cout << "Added.";
            }
            // Read map
            else if (console_manager.answer == 4)
            {
                displayTerrainMap(map);
            }
            // Set default coordinates
            else if (console_manager.answer == 5)
            {
                ifstream coordsFile(mapIdentifier + "Coords.txt");
                int coord;
                coordsFile >> coord;
                startNode->x = coord;
                coordsFile >> coord;
                startNode->y = coord;
                coordsFile >> coord;
                endNode->x = coord;
                coordsFile >> coord;
                endNode->y = coord;
            }
            // Set custom coordinates
            else if (console_manager.answer == 6)
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
                startNode->x = startX;
                startNode->y = startY;
                endNode->x = endX;
                endNode->y = endY;
            }
            // Generate path
            else if (console_manager.answer == 7)
            {
                ISearch* search = NewSearch(currentAlgorithm);
                unique_ptr<SNode> searchStartNode(new SNode(startNode->x,startNode->y));
                unique_ptr<SNode> searchEndNode(new SNode(endNode->x, endNode->y));
                bool success = search->FindPath(map, move(searchStartNode), move(searchEndNode), path);
                cout << "Your node path: " << endl;
                displayNodePath(path);
                writeNodeListToFile(path, mapIdentifier);
            }
            // Read path
            else if (console_manager.answer == 8)
            {
                ifstream pathFile(mapIdentifier + "Path.txt");
                readFile(pathFile);
            }
            // Graphical display
            else if (console_manager.answer == 9)
            {
                demo.setTerrain(map);
                demo.setPath(path);
                cout << "Exiting" << endl << endl;
                runConsoleManager = false;
            }
            // Exit
            else if (console_manager.answer == 10)
            {
                cout << "Exiting" << endl << endl;
                runConsoleManager = false;
                myEngine->Stop();
            }
            // Switch algorithm
            else if (console_manager.answer == 11)
            {
                switch (currentAlgorithm)
                {
                case AStar:
                    currentAlgorithm = BreadthFirst;
                    cout << "Switched to breadth first!" << endl;
                    break;
                case BreadthFirst:
                    currentAlgorithm = AStar;
                    cout << "Switched to A*!" << endl;
                    break;
                }
            }

            // Stall
            console_manager.stall();
            console_manager.clear();
        }

        // Run path
        demo.runPath();


		// Draw the scene
		myEngine->DrawScene();

		/**** Update your scene each frame here ****/

        if (myEngine->KeyHit(Key_Escape))
        {
            myEngine->Stop();
        }
	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
