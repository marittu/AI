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
	


	findStart(board, current_node, goal_node);
	current_node->h = manhatten_distance(current_node, goal_node);
	current_node->f = current_node->g + current_node->h;
	current_node->state = OPEN;
	open.push_front(current_node);

	bool solution = false;
	
	while(!solution){
		if(open.empty()){
			cout << "No path found..." << endl;
			return NULL;
		}
		current_node = *(open.begin());
		open.remove(current_node);
		closed.push_front(current_node);
		current_node->state = CLOSED;

		if(current_node == goal_node){
			solution = true;
			return current_node;
		}
		find_successors(board, current_node, goal_node);
	}
}


int manhatten_distance(Node*& current_node, Node*& goal_node){
	
	return abs(goal_node->y - current_node->y) + abs(goal_node->x - current_node->x);
	
}

void findStart(Node** board, Node*& current_node, Node*& goal_node){
	for(int y = 0; y < HEIGTH; y++){
		for(int x = 0; x < WIDTH; x++){
			if (board[x][y].cell_value == 'A'){
				current_node = &board[x][y];
			}
			if(board[x][y].cell_value == 'B'){
				goal_node = &board[x][y];
			}
		}
	}
}

void find_successors(Node** board, Node*& current_node, Node*& goal_node){ 
	Node* successor;
	successor = &board[current_node->x+1][current_node->y];
	if (successor->cell_value!='#'){
		if(successor->state == UNKNOWN){
			successor->parent = current_node;
			attatch_and_eval(successor, goal_node);	
			if (open.empty()){
				open.push_front(successor);
			}
			else{
				for(auto itterator = open.begin(); itterator != open.end(); ++itterator){
							if(successor->f < (*itterator)->f ){
								open.insert(itterator, successor);
								break;
							}
						}
						open.push_back(successor);
			}		
		}
		else if(successor->cost + parent->g < child->g){
			successor->parent = current_node;
			attatch_and_eval(successor, goal_node);
			for(auto itterator = closed.begin(); itterator != closed.end(); ++itterator){
				if(successor == *(itterator)){
					propagate_path_improvements(successor)
				}
			}
		}
	}
}

void attatch_and_eval(Node*& successor, Node*& goal_node){
	successor->h = manhatten_distance(successor, goal_node);
	successor->g = successor->cost + successor->parent->g;
	successor->f = successor->g + successor->h;

}