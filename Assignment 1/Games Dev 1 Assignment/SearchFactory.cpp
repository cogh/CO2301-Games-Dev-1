/*** AARON ARMSTRONG***/

// SearchFactory.cpp
// =================
//
// Factory function implementation to create CSearchXXX objects 
//

#include "SearchNoStar.h" // NoStar search class
#include "SearchBreadth.h"
#include "SearchAStar.h"

/* TODO - include each implemented search class here */


#include "SearchFactory.h" // Factory declarations

// Create new search object of the given type and return a pointer to it.
// Note the returned pointer type is the base class. This is how we implement polymorphism.
ISearch* NewSearch(ESearchType search)
{
  switch (search)
  {
      case NoStar:
          return new CSearchNoStar();
          break;
      case BreadthFirst:
          return new CSearchBreadth();
          break;
      case AStar:
          return new CSearchAStar();
          break;
    /* TODO - add a case for each implemented search type here */

  }
}
