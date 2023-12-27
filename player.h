/*
 * player.h
 *
 *  Created on: 9 Nov 2023
 *      Author: boody
 */

#ifndef PLAYER_H_
#define PLAYER_H_
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

// are made in different files so need to be used in here as well maze from maze.cpp and visited from functions.h
extern Block* maze[21][21];
extern int visited[21][21];

// player class inherits from block and has additional variable needed from movements and powerups
class Player : public Block {
private:
    int speed = 1;
    int vision = 1;
    int orientation=1;
    int movecount=0;

public:
    Player();  // Constructor for Player
    void setvision(int v){
    	vision=v;
    }
    // getter for orientation
    int getori() {
         return orientation;
    }
    //setter for orientation
    void setori(int ori) {
        // makes the orientation in range (0, 1, 2, 3)
        this->orientation = ori % 4;
    }
    //getter for speed
    int getspeed() {
         return speed;
    }
    // setter for speed
    void setspeed(int s) {
        speed=s;
    }
    //basic move function
    void move(int newX, int newY){
    	// checks if will go over limits of maze
    	if (newX < 0 || newX > 600 || newY < 0 || newY > 600) {
    			setori(orientation + 1);
    	        return;  // Exit the function if coordinates are out of range
    	    }
        // hide the block
        this->hide();
        // set the new coordinates
        setx(newX);
        sety( newY);
        this->position(newX, newY);
        // show the block
        this->show();
        }
    // all following move functions use basic move() to do specfic movement by adding or decreasing x or y
    void moveup() {
    	int currentX = getx();
    	int currentY = gety();
    	int newX = currentX;
    	int newY = currentY-30;
        move(newX,newY);
    }

    // Move one block down
    void movedown() {
    	int currentX = getx();
    	int currentY = gety();
    	int newX = currentX;
    	int newY = currentY+30;
        move(newX,newY);
    }

    // Move one block left
    void moveleft() {
    	int currentX = getx();
    	int currentY = gety();
    	int newX = currentX-30;
    	int newY = currentY;
    	move(newX,newY);
    }

    // Move one block right
    void moveright() {
    	int currentX = getx();
    	int currentY = gety();
    	int newX = currentX+30;
    	int newY = currentY;
    	move(newX,newY);
    }
// getter for number of moves done
    int getmovecount() {
         return movecount;
    }
    //incerements move count and is used in constant move()
    void addtomovecount() {
        movecount++;
    }
    // check if on end block
    int checkifend(){
  	   int x = getx() / 30;
  	   int y = gety() / 30;
  	   bool end=false;
  	   int currentblock=0;
  	   currentblock = maze[y][x]->gettype();
  	   if (currentblock==3){
  		   end=true;
  	   }
    	return end;
    }
// gets blocks one above below left and right , only one if vision one or 2 due to potion
  vector<int> getvisionlist(){
	   vector<int> visionlist(8, 0);
	   std::fill(visionlist.begin(), visionlist.end(), 1);
	   int x = getx() / 30;
	   int y = gety() / 30;
    	if (vision==1){
    		if (y!=0){
    			visionlist[0] = maze[y - 1][x]->gettype();
    		}
    		if (x!=20){
    			visionlist[1] = maze[y][x + 1]->gettype();
    		}
    		if (y!=20){
    			visionlist[2] = maze[y + 1][x]->gettype();
    		}
    		if (x != 0) {
        		visionlist[3] = maze[y][x - 1]->gettype();
    		}


    		}
    	else if (vision==2){
    		if (y!=0){
    			visionlist[0] = maze[y - 1][x]->gettype();
    		}
    		if (x!=20){
    			visionlist[1] = maze[y][x + 1]->gettype();
    		}
    		if (y!=20){
    			visionlist[2] = maze[y + 1][x]->gettype();
    		}
    		if (x != 0) {
        		visionlist[3] = maze[y][x - 1]->gettype();
    		}
    		if (y>=2){
    			visionlist[4] = maze[y - 2][x]->gettype();
    		}
    		if (x<=18){
    			visionlist[5] = maze[y][x + 2]->gettype();
    		}
    		if (y<=18){
    			visionlist[6] = maze[y + 2][x]->gettype();
    		}
    		if (x >= 2) {
        		visionlist[7] = maze[y][x - 2]->gettype();
    		}
    	}
    	return visionlist;
    }


    //checks other blocks in vision if possible to move there dependent on orientation and randomly picks one
    int check_options_move_according(int ori, vector<int> visionlist) {
        vector<int> options(5, -1);
        vector<int> notvisitoptions(3,-1);
        int x=getx()/30;
        int y=gety()/30;

        switch (ori) {
            case 0:
                options[0] = 0;
                if (visited[y-1][x]!=1){
                	notvisitoptions[0]=0;


                }
                if (visionlist[1] != 1) {
                    options[1] = 1;
                    //added so to make twice as likely to go in desired direction which is bottom right()
                    // done for all of following
                    options[3]=1;
                    //checks if block has been visited before and if not then added to not visited list
                    // done for all following
                    if (visited[y][x+1]!=1){
                    	notvisitoptions[1]=1;

                    }
                }
                if (visionlist[3] != 1) {
                    options[2] = 3;
                    if (visited[y][x-1]!=1){
                    	notvisitoptions[2]=3;

                    }
                }
                break;
            case 1:
                options[0] = 1;

                options[3]=1;
                if (visited[y][x+1]!=1){
                	notvisitoptions[1]=1;

                }
                if (visionlist[0] != 1) {
                    options[1] = 0;
                    if (visited[y-1][x]!=1){
                    	notvisitoptions[0]=0;

                    }
                }
                if (visionlist[2] != 1) {
                    options[2] = 2;

                    options[4]=2;
                    if (visited[y+1][x]!=1){
                    	notvisitoptions[2]=2;

                    }



                }
                break;
            case 2:
                options[0] = 2;

                options[3]=2;
                if (visited[y+1][x]!=1){
                	notvisitoptions[2]=2;
                }
                if (visionlist[1] != 1) {
                    options[1] = 1;

                    options[4]=1;
                    if (visited[y][x+1]!=1){
                    	notvisitoptions[1]=1;
                    }
                }
                if (visionlist[3] != 1) {
                    options[2] = 3;
                    if (visited[y][x-1]!=1){
                    	notvisitoptions[0]=3;

                    }
                }
                break;
            case 3:
                options[0] = 3;
                if (visited[y][x-1]!=1){
                	notvisitoptions[0]=3;

                }
                if (visionlist[2] != 1) {
                    options[2] = 2;

                    options[3]=2;
                    if (visited[y+1][x]!=1){
                    	notvisitoptions[1]=2;
                    }
                }
                if (visionlist[0] != 1) {
                    options[1] = 0;
                    if (visited[y-1][x]!=1){
                    	notvisitoptions[2]=0;

                    }
                }
                break;
        }

        int newori = -1;
        bool found=false;
        // to check if a nonvisited path was found , only need to check for one rest wil be done random
        for (int i = 0; i < 3; ++i) {
            if (notvisitoptions[i] !=-1) {
                 found = true;
                break;
            }
        }
        if (found ==true){
            while (newori == -1) {
            	// value in notvisitoptions will be new orientation
                newori = notvisitoptions[rand() % 3];
            }

            // just in case something wrong happens
            if (newori != -1) {
                ori = newori;
            }

        }
        else {
            while (newori == -1) {
            	// value in options will be new orientation
                newori = options[rand() % 5];
            }

            // just in case something wrong happens
            if (newori != -1) {
                ori = newori;
            }

        }

        return ori;
    }
    // checks current block to see if any powers need to be applied to player
    void checkblockpowers(){
   	   int x = getx() / 30;
   	   int y = gety() / 30;
   	   int currentblock=0;
   	   // maze is global variable that is used to look at index player is on and get type
   	   currentblock = maze[y][x]->gettype();
   	   switch(currentblock){
 	//googles
   	   case 4:
   		   // increase vision
   		   setvision(2);
   		   break;

   		//speed potion
   	   case 5:
   		   //increase speeds but up to 3
   		   if (getspeed()<3){
   		   setspeed(getspeed()+1);
   		   }
   		   break;

   		   //fog
   	   case 6:

   		setvision(1);
   		   break;
   		   //slowpoke potion
   	   case 7:
   		setspeed(1);
   		   break;

   	   }
    }

};
//makes the instance of the player at position 0,0 and moves to their so is shown and uses case 8 from block constructor
Player::Player() : Block(0, 0, 8) {
	move(0,0);
}






#endif /* PLAYER_H_ */
