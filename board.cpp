#include <iostream>
#include <string>
#include <fstream>
#include "board.h"


using namespace std;


void getBoard(Node** board, string filename){
	ifstream infile(filename.c_str());
	if(!infile){
		cout << "Error opening file " << filename << endl;
	}

	string line;
	int j = 0;

	while(getline(infile, line)){
		for(int i = 0; i < line.length(); i++){
			board[i][j].cell_value = line[i];
			board[i][j].x = i;
			board[i][j].y = j;
			board[i][j].cost = costs(line[i]);
		}
		j++;
	}

	infile.close();

}


int costs(char cell_value){
	switch(cell_value){
		case '#':
			return 100000;
		case '.':
			return 1;
		case 'r':
			return 1;
		case 'g':
			return 5;
		case 'f':
			return 10;
		case 'm':
			return 50;
		case 'w':
			return 100;
        default:
            return 0;

	}
}
