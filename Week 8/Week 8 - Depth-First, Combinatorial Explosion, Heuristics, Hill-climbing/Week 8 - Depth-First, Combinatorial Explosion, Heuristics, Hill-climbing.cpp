// Week 8 - Depth-First, Combinatorial Explosion, Heuristics, Hill-climbing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <iostream>
#include <memory>
#include <deque>

class Vec2D {
public:
	float x;
	float y;
	Vec2D() {
	}
	Vec2D(float arg_x, float arg_y) {
		x = arg_x;
		y = arg_y;
	}
};

int main()
{
	// Greeting
    std::cout << "Implementing Pathfinding: Depth-First, Combinatorial Explosion, Heuristics, Hill-climbing \n";
	std::cout << "\n";
	system("pause");
	system("CLS");

	// Exercise 1
	std::cout << "Exercise 1 \n";
	Vec2D* ptr = new Vec2D(4,7);
	std::cout << "X: " << ptr->x << "\n" << "Y: " << ptr->y << "\n";
	std::cout << "\n";
	system("pause");
	system("CLS");

	// Exercise 2
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

	// Exercise 2 cont
	std::cout << "Exercise 2 cont \n";
	std::deque<std::unique_ptr<Vec2D>> open_list;
	std::unique_ptr <Vec2D> temp(new Vec2D);
	std::cout << "\n";
	system("pause");
	system("CLS");

	// Exercise 3


	// Exercise 4


	// Exercise 5


	// Exercise 6


	// Exercise 7


	// Exercise 8


	// Exercise 9


	// Exercise 10


	// Stall
	system("pause");
}