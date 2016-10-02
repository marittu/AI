#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <vector>
#include <list>
#include <stdlib.h>
#include <iostream>

#define WIDTH 40
#define HEIGTH 10

enum States{UNKNOWN, OPEN, CLOSED};

struct Node{
	int x;
	int y;
	int f;
	int g;
	int h;	
	int cost;
	char cell_value;
	Node* kids[4];
	Node* parent;
	States state;

	Node() : x(0), y(0), f(0), g(0), h(0), cost(0), cell_value(0), kids({NULL, NULL, NULL, NULL}), parent(NULL), state(UNKNOWN){}

};




Node* solver(Node** board);
void findStart(Node** board, Node*& current_node, Node*& goal_node);
int manhatten_distance(Node*& current_node, Node*& goal_node);
void find_successors(Node** board, Node*& current_node, Node*& goal_node);
void find_kids(Node** board, Node*& current_node);
void attatch_and_eval(Node*& successor, Node*& goal_node);
void propagate_path_improvements(Node*& current_node);
#endif
