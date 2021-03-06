// SearchFactory.cpp
// =================
//
// Factory function implementation to create CSearchXXX objects 
//

#include "SearchNoStar.h" // NoStar search class

/* TODO - include each implemented search class here */


#include "SearchFactory.h" // Factory declarations

// Create new search object of the given type and return a pointer to it.
// Note the returned pointer type is the base class. This is how we implement polymorphism.
ISearch* NewSearch(ESearchType search)
{
  switch (search)
  {
    case NoStar:
      {
         return new CSearchNoStar();
      }

    /* TODO - add a case for each implemented search type here */

  }
}
