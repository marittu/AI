#include <list>
#include <stdlib.h>
#include <iostream>

#include "node.h"

using namespace std;


list<Node*> closed;
list<Node*> open;

int algoritm = 0; //0 for astar, 1 for dijkstra, 2 for bfs

Node* solver(Node** board){

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
		if(current_node == goal_node){
			solution = true;
			return current_node;
		}
		closed.push_back(current_node);
		if (current_node->cell_value != 'A' && current_node->cell_value != 'B'){
			current_node->cell_value = 'x';	
		}
		current_node->state = CLOSED;
		find_kids(board, current_node);
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

void find_kids(Node** board, Node*& current_node){

	if(current_node->x+1 < WIDTH){ 
		Node* east = &board[current_node->x+1][current_node->y];
		if(east->cell_value!='#'){
			current_node->kids[0] = east;	
		}
	}
	if(current_node->y-1 >= 0 ){
		Node* north = &board[current_node->x][current_node->y-1];
		if(north->cell_value!='#'){
			current_node->kids[1] = north;
		}
	}
	if (current_node->x-1 >= 0){
		Node* west = &board[current_node->x-1][current_node->y];
		if(west->cell_value!='#'){
			current_node->kids[2] = west;	
		}
	}
	if( current_node->y+1 < HEIGTH){
		Node* south = &board[current_node->x][current_node->y+1];
		if(south->cell_value!='#'){
			current_node->kids[3] = south;
		}
	}
}

void find_successors(Node** board, Node*& current_node, Node*& goal_node){ 
	for(int i = 0; i < 4; i++){
		if(current_node->kids[i]!= NULL){
			Node* successor = current_node->kids[i];

			if (algoritm == 2){

				if(successor->state == UNKNOWN){
					successor->parent = current_node;

					open.push_back(successor);
					if (successor->cell_value != 'A' && successor->cell_value != 'B'){
						successor->cell_value = '*';	
					}
						
					successor->state = OPEN;	
				}
			}
			else{
				if(successor->state == UNKNOWN){
				successor->parent = current_node;
				attatch_and_eval(successor, goal_node);
					if (open.empty()){
						open.push_back(successor);
						if (successor->cell_value != 'A' && successor->cell_value != 'B'){
							successor->cell_value = '*';	
						}
					}
					else{

						for(auto itterator = open.begin(); itterator != open.end(); ++itterator){
							if((algoritm == 0 && successor->f < (*itterator)->f) || (algoritm == 1 && successor->g < (*itterator)->g)){
								open.insert(itterator, successor);
								if (successor->cell_value != 'A' && successor->cell_value != 'B'){
									successor->cell_value = '*';	
								}
								break;
							}
						}
						open.push_back((successor));
						if (successor->cell_value != 'A' && successor->cell_value != 'B'){
							successor->cell_value = '*';	
						}
					}	
					successor->state = OPEN;	
				}
				else if(successor->cost + current_node->g < successor->g){
					successor->parent = current_node;
					attatch_and_eval(successor, goal_node);
					if (successor-> state == CLOSED){
						propagate_path_improvements(successor);				
					}
				}	
			}			
		}
	}	
}

void attatch_and_eval(Node*& successor, Node*& goal_node){
	successor->g = successor->cost + successor->parent->g;
	if (algoritm == 0){
		successor->h = manhatten_distance(successor, goal_node);
		successor->f = successor->g + successor->h;
	}	
}

void propagate_path_improvements(Node*& current_node){
	for(int i = 0; i < 4; i++){
		if(current_node->kids[i]!= NULL){
			if (current_node->g + current_node->kids[i]->cost < current_node->kids[i]->g){
				current_node->kids[i]->parent = current_node;
				current_node->kids[i]->g = current_node->g + current_node->kids[i]->cost;
				if (algoritm == 0){
					current_node->kids[i]->f = current_node->kids[i]->g + current_node->kids[i]->h;	
				}
				propagate_path_improvements(current_node->kids[i]);
			}
		}
	}
}