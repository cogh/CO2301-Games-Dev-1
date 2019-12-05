#pragma once

class Node
{
public:
	int x;
	int y;
	int score;
	Node* parent;
	Node();
	Node(int arg_x, int arg_y);
	Node(int arg_x, int arg_y, int arg_score);
	Node(Node* arg_parent);
};

