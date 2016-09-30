#include <list>
#include <stdlib.h>
#include <iostream>

#include "node.h"

using namespace std;


Node* astar(Node** board){

	list<Node*> closed;
	list<Node*> open;

	Node* current_node;
	Node* goal_node;
	Node* child;


	findStart(board, current_node, goal_node);
	current_node->h = manhatten_distance(current_node->x, current_node->y, goal_node->x, goal_node->y);
	current_node->f = current_node->g + current_node->h;
	current_node->state = OPEN;
	open.push_back(current_node);

	bool solution = false;

	while(!solution){
		if(open.empty()){
			cout << "No path found..." << endl;
			return NULL;
		}

		current_node = *(open.begin());
		open.remove(current_node);
		closed.push_back(current_node);
		current_node->state = CLOSED;

		if(current_node == goal_node){
			solution = true;
			return current_node;
		}

	}

}


int manhatten_distance(int x1, int y1, int x2, int y2){
	
	return abs(y2 - y1) + abs(x2 - x1);
	
}

void findStart(Node** board, Node*& current_node, Node*& goal_node){
	//current_node = new Node*;
	//goal_node = new Node*;
	for(int y = 0; y < HEIGTH; y++){
		for(int x = 0; x < WIDTH; x++){
			if (board[x][y].cell_value == 'A'){
				current_node = &board[x][y];
			
				cout << "Position current: " << current_node->x << ", " << current_node->y << endl;
			}
			if(board[x][y].cell_value == 'B'){
				goal_node = &board[x][y];
				
				cout << "Position goal_node: " << goal_node->x << ", " << goal_node->y << endl;
			}

		}
	}
}

