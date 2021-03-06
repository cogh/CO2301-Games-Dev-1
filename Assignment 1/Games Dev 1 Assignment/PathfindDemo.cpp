#include "PathfindDemo.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////

////////  CONSTRUCTOR  ////////

PathfindDemo::PathfindDemo(IMesh* argCubeMesh, IMesh* argBushMesh, int argScale)
{
	cubeMesh = argCubeMesh;
    scale = argScale;
    bushMesh = argBushMesh;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

////////  FILE FUNCTIONS  ////////

void PathfindDemo::SetTerrainMapFromFile(string mapIdentifier)
{
    ifstream mapFile(mapIdentifier + "Map.txt");
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
    terrainMap = map;
}

void PathfindDemo::SetCoordsFromFile(string mapIdentifier)
{
    ifstream coordsFile(mapIdentifier + "Coords.txt");
    int coord;
    SNode startNode;
    SNode goalNode;
    coordsFile >> startNode.x;
    coordsFile >> startNode.y;
    coordsFile >> goalNode.x;
    coordsFile >> goalNode.y;
    start.reset(new SNode(startNode));
    goal.reset(new SNode(goalNode));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

////////  DISPLAY FUNCTIONS  ////////

void PathfindDemo::InstantiateModelsFromTerrainMap(TerrainMap argTerrainMap)
{
	string skin;
	int modelX;
	int modelY;
	int modelZ;
    for (int x = 0; x < argTerrainMap.size(); x++)
    {
        for (int y = 0; y < argTerrainMap[0].size(); y++)
        {
			modelX = x * scale;
			modelY = 0;
			modelZ = y * scale;
            bool hasBush = false;
			switch (argTerrainMap[x][y]) 
			{
			case Clear:
				skin = "Grass1.jpg";
				break;
			case Wood:
				skin = "Grass1.jpg";
                hasBush = true;
				break;
			case Water:
				skin = "Neptune.jpg";
                modelY -= scale;
				break;
            case Wall:
                skin = "brick1.jpg";
                modelY += scale;
                break;
			}
            IModel* model = cubeMesh->CreateModel();
            model->SetSkin(skin);
            model->SetPosition(modelX, modelY, modelZ);
            terrainMapModels.push_back(model);
            if (hasBush)
            {
                IModel* bushModel = bushMesh->CreateModel();
                bushModel->SetPosition(modelX, modelY+scale, modelZ);
                bushModel->Scale(10);
                terrainMapModels.push_back(bushModel);
            }
        }
    }
}

void PathfindDemo::InstantiateModelsFromNodeList(NodeList& argNodeList, vector<IModel*>& modelList, IMesh* mesh, string skin)
{
	for (auto& node : argNodeList)
	{
		if (node != nullptr)
		{
			int x = node->x * scale;
			int y = scale;
			int z = node->y * scale;
			IModel* model = mesh->CreateModel();
			model->SetSkin(skin);
			model->SetPosition(x, y, z);
            modelList.push_back(model);
		}
	}
}

void PathfindDemo::InstantiateModelsFromNode(unique_ptr<SNode>& node, IMesh* mesh, string skin)
{
    int x = node->x * scale;
    int y = scale;
    int z = node->y * scale;
    IModel* model = mesh->CreateModel();
    model->SetSkin(skin);
    model->SetPosition(x, y, z);
}

void PathfindDemo::ClearModelList(vector<IModel*> modelList)
{
    while (modelList.size() > 0)
    {
        IModel* model = modelList.back();
        IMesh* mesh = model->GetMesh();
        mesh->RemoveModel(model);
        modelList.pop_back();
    }
}

void PathfindDemo::ClearModels()
{
    ClearModelList(openListModels);
    ClearModelList(closedListModels);
    ClearModelList(terrainMapModels);
}

void PathfindDemo::DeleteModelFromNodeList(vector<IModel*>::iterator model)
{
    //IMesh* mesh = *model->GetMesh();
    //mesh->RemoveModel(*model);
    //modelList.pop_back();
}

void PathfindDemo::UpdateDisplay()
{
    //ClearModelList(openListModels);
    //ClearModelList(closedListModels);
    InstantiateModelsFromTerrainMap(terrainMap);
    InstantiateModelsFromNodeList(openList, openListModels, cubeMesh, "Baize.jpg");
    InstantiateModelsFromNodeList(closedList, closedListModels, cubeMesh, "BaizeDark.jpg");
    InstantiateModelsFromNode(start, cubeMesh, "start.jpg");
    InstantiateModelsFromNode(goal, cubeMesh, "end.jpg");
    DisplayPathfinding(terrainMap);
}

void PathfindDemo::DisplayPathfinding(TerrainMap argTerrain)
{
    // Create empty display grid
    system("CLS");
    cout << "Iteration: " << iterations << endl;
    vector<vector<string>> displayGrid;
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

//////////////////////////////////////////////////////////////////////////////////////////////////////

////////  PATHFINDING FUNCTIONS  ////////

NodeList PathfindDemo::GetAdjacents(unique_ptr<SNode>& node, TerrainMap arg_terrain)
{
	// Create adjacent list
	NodeList adjacentList;

	// Get size
	int width = arg_terrain.size();
	int height = arg_terrain[0].size();

	// Create original position node pointer
	unique_ptr<SNode> original(new SNode());
	original->x = node->x;
	original->y = node->y;
	original->score = node->score;
	original->parent = node->parent;

	// Create temporary node pointer for new nodes
	unique_ptr <SNode> temp(new SNode());

	// Up
	if (original->y + 1 < height && arg_terrain[original->x][original->y + 1] != 0)
	{
		temp.reset(new SNode(original->x, original->y + 1));
		temp->score = original->score + arg_terrain[temp->x][temp->y];
		temp->parent = node.get();
		cout << "temp for up: " << endl;
		DisplayNode(temp);
		if (!NodeExists(temp, openList) && !NodeExists(temp, closedList))
		{
			adjacentList.push_front(move(temp));
		}
	}

	// Right
	if (original->x + 1 < width && arg_terrain[original->x + 1][original->y] != 0)
	{
		temp.reset(new SNode(original->x + 1, original->y));
		temp->score = original->score + arg_terrain[temp->x][temp->y];
		temp->parent = node.get();
		cout << "temp for right: " << endl;
		DisplayNode(temp);
		if (!NodeExists(temp, openList) && !NodeExists(temp, closedList))
		{
			adjacentList.push_front(move(temp));
		}
	}

	// Down
	if (original->y - 1 >= 0 && arg_terrain[original->x][original->y - 1] != 0)
	{
		temp.reset(new SNode(original->x, original->y - 1));
		temp->score = original->score + arg_terrain[temp->x][temp->y];
		temp->parent = node.get();
		cout << "temp for down: " << endl;
		DisplayNode(temp);
		if (!NodeExists(temp, openList) && !NodeExists(temp, closedList))
		{
			adjacentList.push_front(move(temp));
		}
	}

	// Left
	if (original->x - 1 >= 0 && arg_terrain[original->x - 1][original->y] != 0)
	{
		temp.reset(new SNode(original->x - 1, original->y));
		temp->score = original->score + arg_terrain[temp->x][temp->y];
		temp->parent = node.get();
		cout << "temp for left: " << endl;
		DisplayNode(temp);
		if (!NodeExists(temp, openList) && !NodeExists(temp, closedList))
		{
			adjacentList.push_front(move(temp));
		}
	}

	// Return adjacents
	return adjacentList;
}

void PathfindDemo::StartSearch()
{
    // Reset iterations
    iterations = 0;
    // Add start to open
    start->parent = 0;
    unique_ptr<SNode> temp;
    temp.reset(new SNode(start->x, start->y));
    openList.push_back(move(temp));
    leftBorder = -20;
    backBorder = -20;
    searchActive = true;

    // Find best node to open
    NodeList::iterator it;
    if (searchMode == AStar)
    {
        it = FindClosestNode(openList, goal);
    }
    else
    {
        it = openList.begin();
    }

    // Create temp variable from chosen node on open
    unique_ptr<SNode> tmp(new SNode());
    tmp->x = (*it)->x;
    tmp->y = (*it)->y;
    tmp->score = (*it)->score;
    tmp->parent = (*it)->parent;

    // Get adjacents for temp variable
    cout << "getting adjacents for " << endl;
    DisplayNode(tmp);
    NodeList adjacents = GetAdjacents(tmp, terrainMap);

    // Push temp onto closed list and erase entry from open list
    closedList.push_back(move(tmp));
    openList.erase(it);

    // Add adjacents
    for (auto& nodePointer : adjacents)
    {
        cout << "Adding node from adjacents to open" << endl;
        DisplayNode(nodePointer);
        openList.push_back(move(nodePointer));
    }
}

void PathfindDemo::ContinueSearch()
{
    if (openList.size() > 0)
    {
        // Count iterations
        iterations++;
        // Check for end
        if (closedList.back()->x == goal->x && closedList.back()->y == goal->y)
        {
            // Clear models
            ClearModelList(openListModels);
            ClearModelList(closedListModels);
            // Add through goal's hierarchy
            path.push_front(move(closedList.back()));
            while (path.front()->parent != 0)
            {
                unique_ptr<SNode> parentNode;
                parentNode.reset(move(path.front()->parent));
                path.push_front(move(parentNode));
            }
            InstantiateModelsFromNodeList(path, pathModels, cubeMesh, "path.jpg");
            searchActive = false;
        }
        else // Open adjacents
        {
            // Find best node to open
            NodeList::iterator it;
            if (searchMode == AStar)
            {
                it = FindClosestNode(openList, goal);
            }
            else
            {
                it = openList.begin();
            }

			// Create temp variable from chosen node on open
			unique_ptr<SNode> tmp(new SNode());
			tmp->x = (*it)->x;
			tmp->y = (*it)->y;
			tmp->score = (*it)->score;
			tmp->parent = (*it)->parent;

			// Get adjacents for temp variable
			cout << "getting adjacents for " << endl;
			DisplayNode(tmp);
			NodeList adjacents = GetAdjacents(tmp, terrainMap);

			// Push temp onto closed list and erase entry from open list
			closedList.push_back(move(tmp));
			openList.erase(it); 

			// Add adjacents
			for (auto& nodePointer : adjacents)
			{
				cout << "Adding node from adjacents to open" << endl;
				DisplayNode(nodePointer);
				openList.push_back(move(nodePointer));
			}
        }
    }
    else
    {
        // Stop running
        searchActive = false;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////