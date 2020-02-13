#pragma once
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

class PathfindDemo
{
public:
    PathfindDemo(IMesh* argCubeMesh, int argScale);
    void SetTerrainMapFromFile(string mapIdentifier);
    void SetCoordsFromFile(string mapIdentifier);
    void InstantiateModelsFromTerrainMap(TerrainMap argTerrainMap);
    void InstantiateModelsFromNodeList(NodeList& argNodeList, IMesh* mesh, string skin);
    bool searchActive;
    int iterations;
    int scale;
    float leftBorder;
    float backBorder;
    IMesh* cubeMesh;
    TerrainMap terrainMap;
    NodeList path;
    NodeList openList;
    NodeList closedList;
    unique_ptr<SNode> start;
    unique_ptr<SNode> goal;
    vector<IModel*> openListModels;
    vector<IModel*> closedListModels;
    vector<IModel*> terrainMapModels;
    void ClearModelList(vector<IModel*> modelList);
    void StartSearch();
    void ContinueSearch();
    void UpdateDisplay();
    void OpenAdjacents(unique_ptr<SNode>& arg_node, TerrainMap arg_terrain);
};

