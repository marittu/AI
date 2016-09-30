#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <vector>

#define WIDTH 20
#define HEIGTH 7

enum States{UNKNOWN, OPEN, CLOSED};

struct Node{
	int x;
	int y;
	int f;
	int g;
	int h;
	int cost;
	char cell_value;
	Node* parent;
	States state;

	Node() : x(0), y(0), f(0), g(0), h(0), cost(0), cell_value(0), parent(NULL), state(UNKNOWN){}

};




Node* astar(Node** board);
void findStart(Node** board, Node*& current_node, Node*& goal_node);
int manhatten_distance(int x1, int x2, int y1, int y2);

#endif
