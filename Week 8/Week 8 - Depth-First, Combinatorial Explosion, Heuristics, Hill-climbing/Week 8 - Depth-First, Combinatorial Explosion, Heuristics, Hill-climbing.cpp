// Week 8 - Depth-First, Combinatorial Explosion, Heuristics, Hill-climbing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <iostream>
#include <memory>
#include <deque>
#include "Vec2D.h"

void display_open_list(std::deque<std::unique_ptr<Vec2D>>& arg_list) {
	std::deque<std::unique_ptr<Vec2D>>::iterator it;
	int i = 0;
	for (auto it = arg_list.begin(); it != arg_list.end(); it++, i++) {
		std::cout << "Open list entry " << i << ": x is " << (*it)->x << ", y is " << (*it)->y << "\n";
	}
}

bool open_list_contains(std::deque<std::unique_ptr<Vec2D>>& arg_list, Vec2D arg_target) {
	std::deque<std::unique_ptr<Vec2D>>::iterator it;
	int i = 0;
	for (auto it = arg_list.begin(); it != arg_list.end(); it++, i++) {
		if ((*it)->x == arg_target.x && (*it)->y == arg_target.y) {
			return true;
		}
	}
	return false;
}

void exercise_1() {
	std::cout << "Exercise 1 \n";
	Vec2D* ptr = new Vec2D(4, 7);
	std::cout << "X: " << ptr->x << "\n" << "Y: " << ptr->y << "\n";
	std::cout << "\n";
	system("pause");
	system("CLS");
}

void exercise_2() {
	std::cout << "Exercise 2 \n";
	std::unique_ptr<Vec2D> ptr_1(new Vec2D(3, 9));
	std::unique_ptr<Vec2D> ptr_2(new Vec2D(9, 3));
	std::cout << "Pointer 1: " << ptr_1->x << ", " << ptr_1->y << "\n";
	std::cout << "Pointer 2: " << ptr_2->x << ", " << ptr_2->y << "\n";
	std::cout << "Moving pointer \n";
	ptr_2 = std::move(ptr_1);
	std::cout << "Pointer 2: " << ptr_2->x << ", " << ptr_2->y << "\n";
	std::cout << "\n";
	system("pause");
	system("CLS");

	std::cout << "Exercise 2 cont \n";
	std::deque<std::unique_ptr<Vec2D>> test_list;
	std::unique_ptr <Vec2D> unique_vector_pointer(new Vec2D(4, 4));
	test_list.push_back(move(unique_vector_pointer));
	unique_vector_pointer = move(test_list.front());
	test_list.pop_front();
	std::cout << "\n";
	system("pause");
	system("CLS");
}

void exercise_3() {
	std::cout << "Exercise 3 \n";
	std::deque<std::unique_ptr<Vec2D>> open_list;
	std::unique_ptr<Vec2D> current_node(new Vec2D(5, 7));
	open_list.push_back(move(current_node));
	std::cout << "List created" << "\n";
	std::cout << "First entry x: " << open_list.front()->x << "\n";
	std::cout << "First entry y: " << open_list.front()->y << "\n";
	std::unique_ptr<Vec2D> temp_node;
	temp_node = move(open_list.front());
	std::cout << "Temp node x: " << temp_node->x << "\n";
	std::cout << "Temp node y: " << temp_node->y << "\n";
	std::cout << "\n";
	system("pause");
	system("CLS");
}

void exercise_4() {
	std::cout << "Exercise 3 \n";
	std::deque<std::unique_ptr<Vec2D>> open_list;
	std::unique_ptr<Vec2D> current_node;
	for (int i = 0; i < 10; i++) {
		current_node.reset(new Vec2D((i * 2 ) + 1, (i * 2) + 2));
		open_list.push_back(move(current_node));
	}
	display_open_list(open_list);
	std::cout << "\n";
	system("pause");
	system("CLS");
}

void exercise_5() {

}

void exercise_6() {

}

void exercise_7() {

}

void exercise_8() {

}

void exercise_9() {

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