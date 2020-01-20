#pragma once

#include "Definitions.h"  // Type definitions
#include "Search.h"       // Base (=interface) class definition
#include <deque>

// Breadth First search class definition

/* TODO - Replace this class with classes to implement real search algorithms*/

// Inherit from interface and provide implementation for Breadth algorithm
class CSearchBreadth : public ISearch
{
    // I have not implemented any constructors or destructors.
    // Whether you need some is up to how you choose to do your implementation.

    // Constructs the path from start to goal for the given terrain
    bool FindPath(TerrainMap& terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList& path);
    void AddAdjacents(unique_ptr<SNode>& arg_node);

    deque<unique_ptr<SNode>> openList;
    deque<unique_ptr<SNode>> closedList;
};