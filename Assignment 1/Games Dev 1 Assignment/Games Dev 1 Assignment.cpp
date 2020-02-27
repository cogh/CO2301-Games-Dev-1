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
#include "PathfindDemo.h"

using namespace tle;

class TLNode 
{
public:
    IModel* model;
    int x;
    int y;
};

class PathPlotter
{
public:
    IMesh* mMesh;
    IModel* mModel;
    int mScale;
    NodeList mPath;
    NodeList::iterator mTargetIndex;
    bool running;
    PathPlotter(IMesh* mesh, int scale)
    {
        mMesh = mesh;
        mModel = mesh->CreateModel();
        mModel->Scale(0.5);
        mModel->MoveY(scale*2);
        mScale = scale;
        running = false;
    }
    void CopyPath(NodeList& path)
    {
        for (auto& node : path)
        {
            mPath.push_back(move(node));
        }
        mTargetIndex = mPath.begin();
        SNode target = **mTargetIndex;
        mModel->SetX(target.x * mScale);
        mModel->SetZ(target.y * mScale);
    }
    void Run(float deltaTime)
    {
        float distance = DistanceToNextNode();
        if (distance > 5.0f)
        {
            SNode target = **mTargetIndex;
            float xDif = (target.x * mScale) - mModel->GetX();
            float zDif = (target.y * mScale) - mModel->GetZ();
            mModel->MoveX(xDif * 0.03);
            mModel->MoveZ(zDif * 0.03);
        }
        else
        {
            NodeList::iterator mNextTargetIndex = mTargetIndex;
            mNextTargetIndex++;
            if (mNextTargetIndex != mPath.end())
            {
                mTargetIndex = mNextTargetIndex;
            }
            else
            {
                mTargetIndex = mPath.begin();
                SNode target = **mTargetIndex;
                mModel->SetX(target.x * mScale);
                mModel->SetZ(target.y * mScale);
            }
        }
    }
    float DistanceToNextNode()
    {
        SNode target = **mTargetIndex;
        float xDif = (target.x * mScale) - mModel->GetX();
        float zDif = (target.y * mScale) - mModel->GetZ();
        return abs((sqrt((xDif * xDif) + (zDif * zDif))));
    }
};

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
    myEngine->AddMediaFolder("C:\\ProgramData\\TL-Engine\\Media");
    myEngine->AddMediaFolder("./Media");

	// Meshes
	IMesh* cubeMesh = myEngine->LoadMesh("Cube.x");
    IMesh* sphereMesh = myEngine->LoadMesh("Sphere.x");
    IMesh* bushMesh = myEngine->LoadMesh("bush.x");

    // Demo
    PathfindDemo demo = PathfindDemo(cubeMesh, bushMesh, 10);
    PathPlotter pathPlotter = PathPlotter(sphereMesh, 10);


    // Time
    float time = 1;

	// Camera
	ICamera* camera = myEngine->CreateCamera(kManual);
	camera->MoveZ(75);
	camera->MoveY(100);
	camera->MoveX(50);
	camera->RotateX(90);

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
                demo.searchMode = currentAlgorithm;
                demo.SetCoordsFromFile(mapIdentifier);
                demo.start->x = startNode->x;
                demo.start->y = startNode->y;
                demo.goal->x = endNode->x;
                demo.goal->y = endNode->y;
                demo.SetTerrainMapFromFile(mapIdentifier);
                demo.StartSearch();
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
    
        // Time
        time -= myEngine->Timer()*5;
        float deltaTime = myEngine->Timer();

        // Run path
        if (demo.searchActive == true)
        {
            if (time <= 0)
            {
                demo.UpdateDisplay();
                demo.ContinueSearch();
                time = 1.0f;
            }
        }
        else // reset to console
        {
            if (pathPlotter.running == false)
            {
                // Set target node iterator
                pathPlotter.CopyPath(demo.path);
                // Set running
                pathPlotter.running = true;
            }
            else
            {
                pathPlotter.Run(deltaTime);
            }
            //demo.openList.clear();
            //demo.closedList.clear();
            //demo.path.clear();
            //runConsoleManager = true;
            cout << endl << "Search complete. Define new search?" << endl;
        }


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
