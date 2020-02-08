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

class TLNode {
public:
    IModel* model;
    int x;
    int y;
};

class Demo {
public:
    Demo(IMesh* argCubeMesh, IMesh* argArrowMesh, I3DEngine* argEngine, int argScale);
    void setTerrain(TerrainMap argTerrainMap);
    void setPath(NodeList& argNodeList);
    void runPath();
    void clearTerrain(string mapIdentifier);
    void clearPath(string mapIdentifier);
};

