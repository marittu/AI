#include <iostream>
#include <fstream>
#include "board.h"
#include "node.h"


using namespace std;

int main(){
	Node** board = new Node*[WIDTH];
	for (int i = 0; i < WIDTH; i++){

		board[i] = new Node[HEIGTH];
	}

	getBoard(board, "boards/board-2-4.txt");

	cout << "Initial board" << endl;
	for(int y = 0; y < HEIGTH; y++){
		for(int x = 0; x < WIDTH; x++){
			cout << board[x][y].cell_value;
		}
		cout << endl;
	}

	Node* path;

	path = bfs(board)->parent;

	while(path->parent != NULL){
		path->cell_value = 'o';
		path = path->parent;
	}
	
	cout << "Solution board" << endl;

	for(int y = 0; y < HEIGTH; y++){
		for(int x = 0; x < WIDTH; x++){
			cout << board[x][y].cell_value;
		}
		cout << endl;
	}


	
	return 0;
}

