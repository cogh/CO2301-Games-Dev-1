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

void PathfindDemo::OpenAdjacents(unique_ptr<SNode>& arg_node, TerrainMap arg_terrain)
{
    // Create temporary SNode pointer
    unique_ptr <SNode> temp;
    //cout << "Opening adjacents for (" << arg_node->x << ", " << arg_node->y << ")" << endl;

    // Up
    if (arg_node->y + 1 < 10 && arg_terrain[arg_node->x][arg_node->y + 1] != 0)
    {
        temp.reset(new SNode);
        temp->x = arg_node->x;
        temp->y = arg_node->y + 1;
        temp->score = arg_node->score + arg_terrain[temp->x][temp->y];
        temp->parent = arg_node.get();
        if (!NodeExists(temp, openList) && !NodeExists(temp, closedList))
        {
            openList.push_front(move(temp));
            //cout << "Creating up" << endl;
        }
    }

    // Right
    if (arg_node->x + 1 < 10 && arg_terrain[arg_node->x + 1][arg_node->y] != 0)
    {
        temp.reset(new SNode);
        temp->x = arg_node->x + 1;
        temp->y = arg_node->y;
        temp->score = arg_node->score + arg_terrain[temp->x][temp->y];
        temp->parent = arg_node.get();
        if (!NodeExists(temp, openList) && !NodeExists(temp, closedList))
        {
            openList.push_front(move(temp));
            //cout << "Creating right" << endl;
        }
    }

    // Down
    if (arg_node->y - 1 >= 0 && arg_terrain[arg_node->x][arg_node->y - 1] != 0)
    {
        temp.reset(new SNode);
        temp->x = arg_node->x;
        temp->y = arg_node->y - 1;
        temp->score = arg_node->score + arg_terrain[temp->x][temp->y];
        temp->parent = arg_node.get();
        if (!NodeExists(temp, openList) && !NodeExists(temp, closedList))
        {
            openList.push_front(move(temp));
            //cout << "Creating down" << endl;
        }
    }

    // Left
    if (arg_node->x - 1 >= 0 && arg_terrain[arg_node->x - 1][arg_node->y] != 0)
    {
        temp.reset(new SNode);
        temp->x = arg_node->x - 1;
        temp->y = arg_node->y;
        temp->score = arg_node->score + arg_terrain[temp->x][temp->y];
        temp->parent = arg_node.get();
        if (!NodeExists(temp, openList) && !NodeExists(temp, closedList))
        {
            //cout << "Creating left" << endl;
            openList.push_front(move(temp));
        }
    }
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
}

void PathfindDemo::ContinueSearch()
{
    if (openList.size() > 0)
    {
        // Count iterations
        iterations++;
        // Check for end
        if (openList.back()->x == goal->x && openList.back()->y == goal->y)
        {
            // Clear models
            ClearModelList(openListModels);
            ClearModelList(closedListModels);
            // Add through goal's hierarchy
            path.push_back(move(openList.back()));
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

            // Open adjacents
            OpenAdjacents(*it, terrainMap);

            // Move node from open to closed
            //cout << "Closing (" << openList.back()->x << ", " << openList.back()->y << ")" << endl;
            closedList.push_back(move(openList.back()));
            openList.pop_back();
        }
    }
    else
    {
        // Stop running
        searchActive = false;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////