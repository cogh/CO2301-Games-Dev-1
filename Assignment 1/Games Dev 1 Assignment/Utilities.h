/*** AARON ARMSTRONG***/

#pragma once
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

using namespace std;

TerrainMap create_map_from_file(ifstream& mapFile);

void displayNodePath(NodeList& argNodeList);

void displayTerrainMap(TerrainMap argTerrainMap);

void writeNodeListToFile(NodeList& argPath, string fileName);

void readFile(ifstream& argFile);