// Week 8 - Depth-First, Combinatorial Explosion, Heuristics, Hill-climbing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <iostream>
#include <memory>
#include <deque>
#include "Node.h"
#include <algorithm>

bool compare_nodes(std::unique_ptr<Node>& node_1, std::unique_ptr<Node>& node_2) {
	return (node_1->score < node_2->score);
}

void display_open_list(std::deque<std::unique_ptr<Node>>& arg_list) {
	std::deque<std::unique_ptr<Node>>::iterator it;
	int i = 0;
	for (auto it = arg_list.begin(); it != arg_list.end(); it++, i++) {
		std::cout << "Open list entry " << i << ": x is " << (*it)->x << ", y is " << (*it)->y << ", score is " << (*it)->score << "\n";
	}
}

bool open_list_contains(std::deque<std::unique_ptr<Node>>& arg_list, std::unique_ptr<Node>& arg_target) {
	std::deque<std::unique_ptr<Node>>::iterator it;
	int i = 0;
	for (auto it = arg_list.begin(); it != arg_list.end(); it++, i++) {
		if ((*it)->x == arg_target->x && (*it)->y == arg_target->y) {
			std::cout << "AAAAAAAAAAA";
			return true;
		}
	}
	return false;
}

void exercise_1() {
	std::cout << "Exercise 1 \n";
	Node* ptr = new Node(4, 7);
	std::cout << "X: " << ptr->x << "\n" << "Y: " << ptr->y << "\n";
	std::cout << "\n";
	system("pause");
	system("CLS");
}

void exercise_2() {
	std::cout << "Exercise 2 \n";
	std::unique_ptr<Node> ptr_1(new Node(3, 9));
	std::unique_ptr<Node> ptr_2(new Node(9, 3));
	std::cout << "Pointer 1: " << ptr_1->x << ", " << ptr_1->y << "\n";
	std::cout << "Pointer 2: " << ptr_2->x << ", " << ptr_2->y << "\n";
	std::cout << "Moving pointer \n";
	ptr_2 = std::move(ptr_1);
	std::cout << "Pointer 2: " << ptr_2->x << ", " << ptr_2->y << "\n";
	std::cout << "\n";
	system("pause");
	system("CLS");

	std::cout << "Exercise 2 cont \n";
	std::deque<std::unique_ptr<Node>> test_list;
	std::unique_ptr <Node> unique_vector_pointer(new Node(4, 4));
	test_list.push_back(move(unique_vector_pointer));
	unique_vector_pointer = move(test_list.front());
	test_list.pop_front();
	std::cout << "\n";
	system("pause");
	system("CLS");
}

void exercise_3() {
	std::cout << "Exercise 3 \n";
	std::deque<std::unique_ptr<Node>> open_list;
	std::unique_ptr<Node> current_node(new Node(5, 7));
	open_list.push_back(move(current_node));
	std::cout << "List created" << "\n";
	std::cout << "First entry x: " << open_list.front()->x << "\n";
	std::cout << "First entry y: " << open_list.front()->y << "\n";
	std::unique_ptr<Node> temp_node;
	temp_node = move(open_list.front());
	std::cout << "Temp node x: " << temp_node->x << "\n";
	std::cout << "Temp node y: " << temp_node->y << "\n";
	std::cout << "\n";
	system("pause");
	system("CLS");
}

void exercise_4() {
	std::cout << "Exercise 4 \n";
	std::deque<std::unique_ptr<Node>> open_list;
	std::unique_ptr<Node> current_node;
	for (int i = 0; i < 10; i++) {
		current_node.reset(new Node(i, i * 2));
		open_list.push_back(move(current_node));
	}
	display_open_list(open_list);
	current_node.reset(new Node(0, 0));
	std::cout << "Open list contains(0,0): " << open_list_contains(open_list, current_node) << "\n";
	current_node.reset(new Node(3, 6));
	std::cout << "Open list contains(3,6): " << open_list_contains(open_list, current_node) << "\n";
	current_node.reset(new Node(9, 18));
	std::cout << "Open list contains(9,18): " << open_list_contains(open_list, current_node) << "\n";
	current_node.reset(new Node(5, 5));
	std::cout << "Open list contains(5,5): " << open_list_contains(open_list, current_node) << "\n";
	std::cout << "\n";
	system("pause");
	system("CLS");
}

void exercise_5() {
	std::cout << "Exercise 5 \n";
	std::deque<std::unique_ptr<Node>> test_list;
	std::unique_ptr<Node> current_node;
	current_node.reset(new Node(5,7));
	test_list.push_back(move(current_node));
	std::cout << "Front X: " << test_list.front()->x << "\n";
	std::cout << "Front Y: " << test_list.front()->y << "\n";
	std::cout << "Back X: " << test_list.back()->x << "\n";
	std::cout << "Back Y: " << test_list.back()->y << "\n";
	test_list.pop_front();
	std::cout << "Pop." << "\n";
	//std::cout << "Front X: " << test_list.front()->x << "\n";
	//std::cout << "Front Y: " << test_list.front()->y << "\n";
	//std::cout << "Back X: " << test_list.back()->x << "\n";
	//std::cout << "Back Y: " << test_list.back()->y << "\n";
	std::deque<std::unique_ptr<Node>> open_list;
	std::deque<std::unique_ptr<Node>> closed_list;
	std::cout << "Created open and closed list" << "\n";
	for (int i = 0; i < 10; i++) {
		current_node.reset(new Node(i, i * 2));
		open_list.push_back(move(current_node));
	}
	std::cout << "Open list populated" << "\n";
	display_open_list(open_list);
	for (auto& element : open_list) {
		closed_list.push_back(move(element));
	}
	std::cout << "Open list entries transferred to closed list" << "\n";
	//display_open_list(closed_list);
	//display_open_list(open_list);
	std::cout << "\n";
	system("pause");
	system("CLS");
}

void exercise_6() {
	
}

void exercise_7() {
	
}

void exercise_8() {
	std::cout << "Exercise 8 \n";
	std::deque<std::unique_ptr<Node>> open_list;
	Node* prior;
	std::unique_ptr<Node> tmp(new Node(0, 0));
	tmp->parent = 0;
	prior = tmp.get();
	open_list.push_back(move(tmp));
	for (int i = 0; i < 10; i++) {
		tmp.reset(new Node(i, i * 2));
		tmp->parent = prior;
		prior = tmp.get();
		open_list.push_back(move(tmp));
	}
	Node* path = open_list.at(10).get();
	while (path != 0) {
		std::cout << "X: " << path->x << "\n" << "Y: " << path->y << "\n";
		path = path->parent;
	}
	std::cout << "\n";
	system("pause");
	system("CLS");
}

void exercise_9() {
	std::cout << "Exercise 9 \n";
	std::deque<std::unique_ptr<Node>> open_list;
	std::unique_ptr<Node> temp_node(new Node());
	temp_node.reset(new Node(0, 0, 7));
	open_list.push_back(move(temp_node));
	temp_node.reset(new Node(0, 0, 32));
	open_list.push_back(move(temp_node));
	temp_node.reset(new Node(0, 0, 4));
	open_list.push_back(move(temp_node));
	temp_node.reset(new Node(0, 0, 25));
	open_list.push_back(move(temp_node));
	temp_node.reset(new Node(0, 0, 13));
	open_list.push_back(move(temp_node));
	std::sort(open_list.begin(), open_list.end(), compare_nodes);
	display_open_list(open_list);
	std::cout << "\n";
	system("pause");
	system("CLS");
}

void exercise_10() {

}



int main()
{
	// Greeting
	std::cout << "Implementing Pathfinding: Depth-First, Combinatorial Explosion, Heuristics, Hill-climbing \n";
	std::cout << "\n";
	system("pause");
	system("CLS");

	// Exercise 1
	exercise_1();

	// Exercise 2
	exercise_2();

	// Exercise 3
	exercise_3();

	// Exercise 4
	exercise_4();

	// Exercise 5
	exercise_5();

	// Exercise 6
	exercise_6();

	// Exercise 7
	exercise_7();

	// Exercise 8
	exercise_8();

	// Exercise 9
	exercise_9();

	// Exercise 10
	exercise_10();

	// Stall
	system("pause");
}