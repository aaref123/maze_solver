/*
 * functions.h
 *
 *  Created on: 16 Nov 2023
 *      Author: boody
 */
using namespace std;
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Window.H>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <iostream>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include "Block.h"
#include "player.h"
#include <limits>

using namespace std;

#include <iostream>
#include <fstream>
#include <vector>

#include <fstream>
#include <iostream>
#include <vector>

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

// function that cleans maze and returns new file that is cleaned
void cleanMaze(const string& inputFileName, const string& outputFileName) {
    ifstream inputFile(inputFileName);
    // if there is issue with file
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the input file." << endl;
        return;
    }

    ofstream outputFile(outputFileName);

    if (!outputFile.is_open()) {
        cerr << "Error: Could not open the output file." << endl;
        inputFile.close();
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        if (line.empty()) {
            continue;
        }

        // removes other characters
        line.erase(remove_if(line.begin(), line.end(),
            [](char c) { return c == '[' || c == ']' || c == ','; }),
            line.end());

        // Write the cleaned line to the output file
        outputFile << line << endl;
    }

    inputFile.close();
    outputFile.close();

    cout << "Maze cleaned and saved to '" << outputFileName << "'" << endl;
}

// will use to check if blocks have been visited before so try new ones
int visited[21][21]={0};

static void constantmove(void* playadd) {
    Player* player = static_cast<Player*>(playadd);
    int stepsintick=player->getspeed();
    // gets speed so if higher than one does more than one movement in one tick
    for (int i = 1; i <= stepsintick; ++i) {
    // when getting x and y we dividve by 30 which is size of block so can use with index from maze
    int x = player->getx() / 30;
    int y = player->gety() / 30;
    int ori = player->getori();
    vector<int> visionlist = player->getvisionlist();
    player->addtomovecount();
    if (player->checkifend()==true){
    	cout << "Congrats you beat the maze ! the final step count: "<<player->getmovecount();
    	exit(0);
    }
    // checks each orientation the corresponding next block depending on orientation
    	if (ori == 0) {
    		// if checks if not at border and if not wall
    	            if (y - 1 >= 0 && visionlist[0] != 1) {
    	            	ori=player->check_options_move_according(ori,visionlist);
    	            	player->setori(ori);
    	            	// after checking possible options then moves depending on orientation
    	            	if (ori == 0){
    	            		player->moveup();
    	            	}
    	            	else if (ori == 1){
    	            		player->moveright();
    	            	}
    	            	else if (ori == 3){
    	            		player->moveleft();
    	            	}
    	            } else {
    	                ori = (ori + 1) % 4;
    	                player->setori(ori);
    	            }
    	     }else if (ori == 1) {
    	        if (x + 1 < 21 && visionlist[1] != 1) {
    	        	ori=player->check_options_move_according(ori,visionlist);
    	        	player->setori(ori);
    	        	if (ori == 0){
    	        		player->moveup();
    	        	}
    	        	else if (ori == 1){
    	        		player->moveright();
    	        	}
    	        	else if (ori == 2){
    	        		player->movedown();
    	        	}

    	        } else {
    	            ori = (ori + 1) % 4;
    	            player->setori(ori);
    	        }
    	    } else if (ori == 2) {
    	        if (y + 1 < 21 && visionlist[2] != 1) {
    	        	ori=player->check_options_move_according(ori,visionlist);
    	        	player->setori(ori);

    	        	if (ori == 1){
    	        		player->moveright();
    	        	}
    	        	else if (ori == 2){
    	        		player->movedown();
    	        	}
    	        	else if (ori == 3){
    	        		player->moveleft();
    	        	}
    	        } else {
    	            ori = (ori + 1) % 4;
    	            player->setori(ori);
    	        }
    	    } else if (ori == 3) {
    	        if (x - 1 >= 0 && visionlist[3] != 1) {
    	        	ori=player->check_options_move_according(ori,visionlist);
    	            player->setori(ori);
    	            if (ori == 0){
    	                player->moveup();
    	            }
    	            else if (ori == 2){
    	                player->movedown();
    	            }
    	            else if (ori == 3){
    	                player->moveleft();
    	            }
    	        } else {
    	            ori = (ori + 1) % 4;
    	            player->setori(ori);
    	        }
    	    }
    	// adds current block to visited
    	visited[y][x]=1;
    	// checks current block for powers
    	player->checkblockpowers();
    }

    Fl::repeat_timeout(0.099, constantmove, playadd); // Repeat the timer
}



#endif /* FUNCTIONS_H_ */
