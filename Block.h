/*
 * Block.h
 *
 *  Created on: 9 Nov 2023
 *      Author: boody
 */


#ifndef BLOCK_H_
#define BLOCK_H_
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

class Block : public Fl_Box {
	//block has x , y position and type which is the number from the text file,
private:
    int x;
    int y;
    int type;
    bool canwalk=true;

public:

    Block(int x, int y, int type);
    int getx();
    int gety();
    int gettype();
    void setx(int x);
    void sety(int y);
    void settype(int type);
    void printInfo();

};
// it uses fltk box function with length and width 30
Block::Block(int x, int y, int type) : Fl_Box(x, y, 30, 30), x(x), y(y), type(type) {
    this->box(FL_FLAT_BOX);
    // Set color based on the type
        switch (type) {
            case 0: // Empty space
                this->color(FL_WHITE);
                break;
            case 1: // Wall
                this->color(FL_GRAY);
                this->canwalk=false;
                break;
            case 2: // Starting point
                this->color(FL_GREEN);
                break;
            case 3: // Goal
                this->color(FL_RED);
                break;
            case 4: // Googles
                this->color(FL_BLUE);
                break;
            case 5: // speed potion
            	this->color(FL_YELLOW);
            	break;
            case 6: // fog
            	this->color(FL_BLACK);
            	break;
            case 7: // slowpoke potion
            	this->color(FL_MAGENTA);
            	break;
            case 8: // player
                this->box(FL_OVAL_BOX);
            	this->color(FL_CYAN);

            	break;
        }
}
// set and get for all variables
int Block::getx() {
     return x;
}

int Block::gety() {
      return y;
}

int Block::gettype() {
    return type;
}

void Block::setx(int x) {
     this->x=x;
}

void Block::sety(int y) {
      this->y=y;
}
void Block::settype(int type) {
	this->type=type;
}

//prints basic info
void Block::printInfo() {
    cout << "Block with position (" << this->x << ", " << this->y << ") and type " << this->type << endl;
}



#endif /* BLOCK_H_ */
