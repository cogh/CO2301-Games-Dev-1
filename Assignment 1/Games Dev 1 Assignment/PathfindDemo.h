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
    PathfindDemo(IMesh* argCubeMesh, IMesh* argBushMesh, int argScale);
    ESearchType searchMode = AStar;
    void SetTerrainMapFromFile(string mapIdentifier);
    void SetCoordsFromFile(string mapIdentifier);
    void InstantiateModelsFromTerrainMap(TerrainMap argTerrainMap);
    void InstantiateModelsFromNodeList(NodeList& argNodeList, vector<IModel*>& modelList, IMesh* mesh, string skin);
	void InstantiateModelsFromNode(unique_ptr<SNode>& node, IMesh* mesh, string skin);
    bool searchActive;
    int iterations;
    int scale;
    float leftBorder;
    float backBorder;
    IMesh* cubeMesh;
    IMesh* bushMesh;
    TerrainMap terrainMap;
    NodeList path;
    NodeList openList;
    NodeList closedList;
    unique_ptr<SNode> start;
    unique_ptr<SNode> goal;
    vector<IModel*> openListModels;
    vector<IModel*> closedListModels;
    vector<IModel*> terrainMapModels;
    vector<IModel*> pathModels;
    void ClearModelList(vector<IModel*> modelList);
    void StartSearch();
    void ContinueSearch();
    void UpdateDisplay();
    void ClearModels();
	void DeleteModelFromNodeList(vector<IModel*>::iterator modelList);
    void OpenAdjacents(unique_ptr<SNode>& arg_node, TerrainMap arg_terrain);
	void DisplayPathfinding(TerrainMap argTerrain);
};

