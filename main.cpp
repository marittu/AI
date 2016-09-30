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
	Node* backtrackingNode;

	getBoard(board, "boards/board-1-4.txt");
	
	


	for(int y = 0; y < HEIGTH; y++){
		for(int x = 0; x < WIDTH; x++){
			cout << board[x][y].cell_value;
		}
		cout << endl;
	}


	astar(board);

	return 0;
}

