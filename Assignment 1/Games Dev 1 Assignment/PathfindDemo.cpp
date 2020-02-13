#include "PathfindDemo.h"

PathfindDemo::PathfindDemo(IMesh* argCubeMesh, int argScale)
{
	cubeMesh = argCubeMesh;
    scale = argScale;
}

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

void PathfindDemo::InstantiateModelsFromTerrainMap(TerrainMap argTerrainMap)
{
    for (int x = 0; x < argTerrainMap.size(); x++)
    {
        for (int y = 0; y < argTerrainMap[0].size(); y++)
        {
            IModel* model = cubeMesh->CreateModel();
            model->SetSkin("brick1.jpg");
            model->SetPosition(x * scale, 0, y * scale);
        }
    }
}

void PathfindDemo::InstantiateModelsFromNodeList(NodeList& argNodeList, IMesh* mesh, string skin)
{
    for (auto& node : argNodeList)
    {
        if (node != nullptr)
        {
            int x = node->x * scale;
            int y = scale;
            int z = node->y * scale;
            cout << "creating model at (x: " << x << ", y: " << y << ", z: " << z << ")" << endl;
            IModel* model = mesh->CreateModel();
            model->SetSkin(skin);
            model->SetPosition(x, y, z);
        }
    }
}

void PathfindDemo::ClearModelList(vector<IModel*> modelList)
{
    for (int i = 0; i < modelList.size(); i++)
    {
        delete modelList[i];
    }
}

void PathfindDemo::StartSearch()
{
	// Add start to open
	start->parent = 0;
	openList.push_back(move(start));
    leftBorder = -(terrainMap.size() * scale / 2);
    backBorder = -(terrainMap[0].size() * scale / 2);
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
            // Add through goal's hierarchy
            path.push_back(move(openList.back()));
            while (path.front()->parent != 0)
            {
                unique_ptr<SNode> parentNode;
                parentNode.reset(move(path.front()->parent));
                path.push_front(move(parentNode));
            }
            searchActive = false;
        }
        else // Open adjacents
        {
            // Find best node to open
            NodeList::iterator it = FindClosestNode(openList, goal);

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
        // Generate path


        // Stop running
        searchActive = false;
    }
}

void PathfindDemo::UpdateDisplay()
{
    ClearModelList(openListModels);
    ClearModelList(closedListModels);
    InstantiateModelsFromNodeList(openList, cubeMesh, "Baize.jpg");
    InstantiateModelsFromNodeList(closedList, cubeMesh, "BaizeDark.jpg");
}

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