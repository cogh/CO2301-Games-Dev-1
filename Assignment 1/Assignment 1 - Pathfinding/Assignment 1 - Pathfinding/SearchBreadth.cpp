// SearchBreadth.cpp
// ======^^^^^^====
//
// Implementation of Search class for NoStar algorithm
//

//  NOTE - There is no such thing as the NoStar search algorithm
//         I have implemented it as a pattern for you to follow

#include "SearchBreadth.h" // Declaration of this class
#include <iostream> // for debugging

/* TODO - Replace this class with classes to implement real search algorithms*/


// This function takes ownership of the start and goal pointers that are passed in from the calling code.
// Ownership is not returned at the end, so the start and goal nodes are consumed.
// The Path is returned through the reference parameter.

bool CSearchBreadth::FindPath(TerrainMap& terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList& path)
{
    // Add start to open
    start->parent = 0;
    openList.push_back(move(start));

    // Expand adjacents
    while (openList.size() > 0) 
    {
        // Check for end
        if (openList.back() == goal) 
        {
            // Add through goal's hierarchy
            path.push_back(move(openList.back()));
            while (path.back()->parent != 0) 
            {
                unique_ptr<SNode> parentNode;
                parentNode.reset(move(path.back()->parent));
                path.push_back(move(parentNode));
            }
            return true;
        }
        else 
        {
            // Open adjacents
            OpenAdjacents(openList.back(), terrain);

            // Move node from open to closed
            closedList.push_back(move(openList.back()));
            cout << "Popping back" << endl;
            openList.pop_back();
        }
    }

    return false;
}

void CSearchBreadth::OpenAdjacents(unique_ptr<SNode>& arg_node, TerrainMap arg_terrain)
{
    // Create temporary SNode pointer
    unique_ptr <SNode> temp;
    cout << "Opening adjacents for new node:" << endl;
    cout << "   x: " << arg_node->x << endl;
    cout << "   y: " << arg_node->y << endl;
    cout << "   score: " << arg_node->score << endl;
    if (arg_node->parent != 0) {
        cout << "   parent: (x:" << arg_node->parent->x << ", y:" << arg_node->parent->y << ")" << endl;
    }

    // Up
    if (arg_node->y + 1 < 10 && !arg_node->upOpened) 
    {
        cout << "Creating up" << endl;
        temp.reset(new SNode);
        temp->x = arg_node->x;
        temp->y = arg_node->y + 1;
        temp->score = arg_terrain[temp->x][temp->y];
        temp->parent = arg_node.get();
        openList.push_back(move(temp));
        arg_node->upOpened = true;
    }

    // Right
    if (arg_node->x + 1 < 10 && !arg_node->rightOpened)
    {
        cout << "Creating right" << endl;
        temp.reset(new SNode);
        temp->x = arg_node->x + 1;
        temp->y = arg_node->y;
        temp->score = arg_terrain[temp->x][temp->y];
        temp->parent = arg_node.get();
        openList.push_back(move(temp));
        arg_node->rightOpened = true;
    }

    // Down
    if (arg_node->y - 1 >= 0 && !arg_node->downOpened)
    {
        cout << "Creating down" << endl;
        temp.reset(new SNode);
        temp->x = arg_node->x;
        temp->y = arg_node->y - 1;
        temp->score = arg_terrain[temp->x][temp->y];
        temp->parent = arg_node.get();
        openList.push_back(move(temp));
        arg_node->downOpened = true;
    }

    // Left
    if (arg_node->x - 1 >= 0 && !arg_node->leftOpened)
    {
        cout << "Creating left" << endl;
        temp.reset(new SNode);
        temp->x = arg_node->x - 1;
        temp->y = arg_node->y;
        temp->score = arg_terrain[temp->x][temp->y];
        temp->parent = arg_node.get();
        openList.push_back(move(temp));
        arg_node->leftOpened = true;
    }
}

void CSearchBreadth::displayTerrainMap(TerrainMap argTerrainMap)
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