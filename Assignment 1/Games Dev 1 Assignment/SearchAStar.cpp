/*** AARON ARMSTRONG***/

// SearchBreadth.cpp
// ======^^^^^^====
//
// Implementation of Search class for AStar algorithm
//

#include "SearchAStar.h" // Declaration of this class
#include <iostream> // for debugging/step display
#include <string>


// This function takes ownership of the start and goal pointers that are passed in from the calling code.
// Ownership is not returned at the end, so the start and goal nodes are consumed.
// The Path is returned through the reference parameter.

bool CSearchAStar::FindPath(TerrainMap& terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList& path)
{
    // Add start to open
    start->parent = 0;
    openList.push_back(move(start));

    // Expand adjacents
    while (openList.size() > 0)
    {
        // Display grid
        cout << "Iterations: " << iterations << endl;
        iterations++;
        cout << "Pathfinding grid:" << endl;
        DisplayPathfinding(terrain);
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
            return true;
        }
        else
        {
            // Find best node to open
            NodeList::iterator it = FindClosestNode(openList,goal);

            // Open adjacents
            OpenAdjacents(*it, terrain);

            // Move node from open to closed
            //cout << "Closing (" << openList.back()->x << ", " << openList.back()->y << ")" << endl;
            closedList.push_back(move(openList.back()));
            openList.pop_back();
        }
    }

    return false;
}

void CSearchAStar::OpenAdjacents(unique_ptr<SNode>& arg_node, TerrainMap arg_terrain)
{
    // Boundaries
    int terrainWidth = arg_terrain.size();
    int terrainHeight = arg_terrain[0].size();
    // Create temporary SNode pointer
    unique_ptr <SNode> temp;
    //cout << "Opening adjacents for (" << arg_node->x << ", " << arg_node->y << ")" << endl;

    // Up
    if (arg_node->y + 1 < terrainHeight && arg_terrain[arg_node->x][arg_node->y+1] != 0)
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
    if (arg_node->x + 1 < terrainWidth && arg_terrain[arg_node->x+1][arg_node->y] != 0)
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
    if (arg_node->y - 1 >= 0 && arg_terrain[arg_node->x][arg_node->y-1] != 0)
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
    if (arg_node->x - 1 >= 0 && arg_terrain[arg_node->x-1][arg_node->y] != 0)
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

bool CSearchAStar::NodeExists(unique_ptr<SNode>& argNode, deque<unique_ptr<SNode>>& argNodeList) {
    for (auto& element : argNodeList)
    {
        if (element->x == argNode->x && element->y == argNode->y)
        {
            return true;
        }
    }
    return false;
}

unique_ptr<SNode> CSearchAStar::findNode(unique_ptr<SNode>& argNode, deque<unique_ptr<SNode>>& argNodeList) {
    for (auto& element : argNodeList)
    {
        if (element->x == argNode->x && element->y == argNode->y)
        {
            return move(element);
        }
    }
    return nullptr;
}

int CSearchAStar::Heuristic(unique_ptr<SNode>& origin, unique_ptr<SNode>& target) 
{
    // Get Manhattan distance
    return origin->score + abs(origin->x - target->x) + abs(origin->y - target->y);
}

NodeList::iterator CSearchAStar::FindClosestNode(NodeList& argNodeList, unique_ptr<SNode>& argTarget) {
    auto closestNode = argNodeList.begin();
    for (auto iter = argNodeList.begin(); iter != argNodeList.end(); ++iter) {
        if (Heuristic(*iter, argTarget) < Heuristic(*closestNode, argTarget)) {
            closestNode = iter;
        }
    }
    return closestNode;
}

void CSearchAStar::DisplayPathfinding(TerrainMap argTerrain) 
{
    // Create empty display grid
    vector<vector<string>> displayGrid;
    int width = argTerrain.size();
    int height = argTerrain[0].size();
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
    for (int y = height- 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            cout << displayGrid[x][y];
        }
        cout << endl;
    }
}