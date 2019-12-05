#include "Vec2D.h"

Node::Node()
{
	x = 0;
	y = 0;
}

Node::Node(float arg_x, float arg_y)
{
	x = arg_x;
	y = arg_y;
}

Node::Node(Node* arg_parent)
{
	x = arg_parent->x;
	y = arg_parent->y;
}

