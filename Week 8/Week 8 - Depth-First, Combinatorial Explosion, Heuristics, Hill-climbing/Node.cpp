#include "Node.h"

Node::Node()
{
	x = 0;
	y = 0;
}

Node::Node(int arg_x, int arg_y)
{
	x = arg_x;
	y = arg_y;
}

Node::Node(int arg_x, int arg_y, int arg_score)
{
	x = arg_x;
	y = arg_y;
	score = arg_score;
}

Node::Node(Node* arg_parent)
{
	x = arg_parent->x;
	y = arg_parent->y;
}

