// DEMONSTRATE HOW TO DRAW AN 'X' IN FLTK
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Window.H>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Widget.H>
#include <iostream>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include "Block.h"
#include "player.h"
#include "functions.h"
#include <limits>
using namespace std;
#include <vector>
#include <string>
#include <algorithm>

//global variables

const int len=21;
Block* maze[len][len];
int stepcount=0;

int main() {
	//no need to use clean maze everytime
	//cleanMaze("C:\\uni\\c++\\maze_layout(notclean)-Copy.txt", "C:\\uni\\c++\\maze_cleaned.txt");
    ifstream maze_array("C:\\uni\\c++\\maze_cleaned.txt");
    if (!maze_array) {
        cout << "Failed to load maze file" << endl;
        return 1;
    }

// goes through double for loop through y then x to add each value to maze array
    for (int y = 0; y < len; ++y) {
        for (int x = 0; x < len; ++x) {
            int type;
            if (!(maze_array >> type)) {
                cout << "Error reading from the maze file" << endl;
                return 1;
            }
            //block size is 30 pixels and type is number from text file
            maze[y][x] = new Block(x*30, y*30, type);
            //cout << maze[y][x]->gettype()<< " ";
        }
        cout << endl;
    }
// makes window from fltk to display graphically
    Fl_Window *window = new Fl_Window(400, 100, 630, 630, "The Maze");
// adds each block on window
    for (int y = 0; y < len; ++y) {
        for (int x = 0; x < len; ++x) {
            window->add(maze[y][x]);
        }
    }
    //player stuff here
    // Initialize player box
    Player player;
    // Move
    window->add(player);
    window->show();
    // constant move in functions.h
    constantmove(&player);
    return Fl::run();
}





