#pragma once

class Node
{
public:
	float x;
	float y;
	Node* parent;
	Node();
	Node(float arg_x, float arg_y);
	Node(Node* arg_parent);
};

