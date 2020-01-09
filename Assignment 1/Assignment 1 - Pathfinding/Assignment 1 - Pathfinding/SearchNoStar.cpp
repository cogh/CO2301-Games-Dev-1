// SearchNoStar.cpp
// ======^^^^^^====
//
// Implementation of Search class for NoStar algorithm
//

//  NOTE - There is no such thing as the NoStar search algorithm
//         I have implemented it as a pattern for you to follow

#include "SearchNoStar.h" // Declaration of this class

/* TODO - Replace this class with classes to implement real search algorithms*/


// This function takes ownership of the start and goal pointers that are passed in from the calling code.
// Ownership is not returned at the end, so the start and goal nodes are consumed.
// The Path is returned through the reference parameter.

bool CSearchNoStar::FindPath(TerrainMap& terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList& path)
{
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