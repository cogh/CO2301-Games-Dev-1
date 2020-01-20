// SearchBreadth.cpp
// ======^^^^^^====
//
// Implementation of Search class for NoStar algorithm
//

//  NOTE - There is no such thing as the NoStar search algorithm
//         I have implemented it as a pattern for you to follow

#include "SearchBreadth.h" // Declaration of this class

/* TODO - Replace this class with classes to implement real search algorithms*/


// This function takes ownership of the start and goal pointers that are passed in from the calling code.
// Ownership is not returned at the end, so the start and goal nodes are consumed.
// The Path is returned through the reference parameter.

bool CSearchBreadth::FindPath(TerrainMap& terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList& path)
{
    // Add start to open
    //openList.push_back(start);

    // Expand adjacents
    /*while (openList.size() > 0) 
    {
        //AddAdjacents(openList.back);
        //closedList.push_back(move(openList.back));
        //openList.pop_back();
    }*/
    // Rather than finding a real path, my made-up No Star algorithm constructs some nodes and calls them a path.
    unique_ptr <SNode> temp;
    for (int i = 0; i < 4; i++)
    {
        temp.reset(new SNode);
        temp->x = i;
        temp->y = i * 2;
        path.push_back(move(temp));
    }

    return true;
}

void CSearchBreadth::AddAdjacents(unique_ptr<SNode>& arg_node) 
{
    // Create temporary SNode pointer
    unique_ptr <SNode> temp;

    // Up
    /*temp.reset(new SNode);
    temp->x = arg_node->x;
    temp->y = arg_node->y + 1;
    temp->parent = arg_node.get();
    openList.push_back(move(temp));

    // Right
    temp.reset(new SNode);
    temp->x = arg_node->x + 1;
    temp->y = arg_node->y;
    temp->parent = arg_node.get();
    openList.push_back(move(temp));

    // Down
    temp.reset(new SNode);
    temp->x = arg_node->x;
    temp->y = arg_node->y - 1;
    temp->parent = arg_node.get();
    openList.push_back(move(temp));

    // Left
    temp.reset(new SNode);
    temp->x = arg_node->x - 1;
    temp->y = arg_node->y;
    temp->parent = arg_node.get();
    openList.push_back(move(temp));*/
}