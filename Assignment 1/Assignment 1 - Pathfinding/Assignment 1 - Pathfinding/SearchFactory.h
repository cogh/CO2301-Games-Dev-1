// SearchFactory.h
// ===============
//
// Factory function declaration to create CSearchXXX objects 
//

#pragma once

#include "Search.h" // Search interface class

// List of implemented seach algorithms
enum ESearchType
{
  // BreadthFirst,
  // Dijkstra,
  // AStar,
  
  /* TODO - Add type elements for each implemented search */

  NoStar // Not a real algorithm - remove when ready! 
};

// Factory function to create CSearchXXX object where XXX is the given search type
ISearch* NewSearch(ESearchType search);
