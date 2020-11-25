/*
 ============================================================================
 Name        : Simple Mario
 Author      : AmirHossein Qasemi
 Version     : 1.0.0
 Copyleft    : @ ALL WRONGS RESERVED
 ============================================================================
 */



#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include "mario.h"
#include "mymariolibrary.h"
#include "pillar.h"
#include "mushroom.h"
#include "turtle.h"
#include "cloud.h"
#include "menu.h"
#include "castle.h"
#include "enumandstructs.h"

using namespace std;

int main(){
    int inputChar, i, j;
    int maxRow, maxColumn, marioPRow, marioPColumn, pillarTempCol, mushroomTempCol, turtleTempBCol, cloudTempCol; //Mario Printing Row/Column
    unsigned prevMove = 0, airHPrevMove = 0, airTimeCounter = 21, airHMovementCounter = 0, noInputCounter;//H stands for horizental
    enum gameStatus myGameStatus = CONTINUE;

    struct itemCol myPillarCol;
    class Pillar *myPillar[MAX_PILLAR_NUM] = {0, 0, 0, 0, 0};/*There is a maximum of MAX_PILLAR_NUM Pillars in the scene where mario is.
                                    in order to reserve memory space if mario scene comes close to one of
                                    the pillars, an object of pillar class is insantiated.
                                    and when it is not in the vicinity of the scene it gets deleted*/

    struct itemCol mushroomCol;
    class Mushroom *myMushroom[MAX_MUSHROOM_NUMBER] = {0, 0, 0 ,0, 0};//the latter comment is also true about mushrooms



    struct itemCol turtleCol;
    class Turtle *myTurtle[MAX_TURTLE_NUMBER] = {0,0,0,0,0};//the former comment is also true about tutrles

    struct itemCol cloudCol;
    class Cloud *myCloud[MAX_CLOUD_NUMBER] = {0, 0, 0, 0, 0};//the same...




    FILE *scenariofPtr;
     if ( ( scenariofPtr = fopen("scenario.txt", "r") )== NULL)
         endGame();


    Castle *myCastle = new Castle(findTheCastleColumn(scenariofPtr));
    Menu *myMenu = new Menu();


    loadItemCols(&myPillarCol, &mushroomCol, &turtleCol, &cloudCol, scenariofPtr);


    initNCursesTerminal();
    getmaxyx(stdscr, maxRow, maxColumn);

    switch( myMenu->bringMainMenu(0)){
        case 2:
            wbkgd(stdscr, COLOR_PAIR(WC));
            break;
        case 4:
            endwin();
            return 0;
	}

	

    marioPRow = maxRow - 2;
    marioPColumn = maxColumn / 2;



    Mario *myMario = new Mario(maxRow - 10, marioPColumn);
	


    while(1){

        checkTerminalSize();
        paintTheGround();
        outPutExtraInfo(myMario->getScore());



        inputChar = getch();


	
		if(inputChar == 'q'){
            switch( myMenu->bringMainMenu(1) ){
			case 0:	
		    	wbkgd(stdscr, COLOR_PAIR(WC));			
				break;
			case 1:
				restart(myCloud, myMushroom, myTurtle, myPillar);
                loadItemCols(&myPillarCol, &mushroomCol, &turtleCol, &cloudCol, scenariofPtr);
				delete myMario;
				clear();
                myMario = new Mario(maxRow - 10, marioPColumn);
				break;

			case 4:
				endwin();
                cleanHeap(myCloud, myMushroom, myTurtle, myPillar, scenariofPtr);
				return 0;
				break;
			}
		}


		if(inputChar == ERR)
			noInputCounter++;

		if(inputChar != ERR)
			noInputCounter = 0;


		myMario->checkOnHigherSurface(myPillar, maxRow - 2);
        myMario->checkColliding(myMushroom, &mushroomCol, marioPColumn,myTurtle, airTimeCounter);

		if( noInputCounter >= 5 && (airTimeCounter == 0 || myMario->getOnHigherSurface() == true)){
			myMario->setShapeID(MARIO_STANDING, marioPRow, marioPColumn);
			myMario->zeroMovingMarioShapeCounter();
		}



		for(i = 0; i < MAX_PILLAR_NUM; i++){
			if(myPillar[i] != NULL)
				myPillar[i]->cleanPillar(myMario->getColumn(), marioPColumn);	
		
		}
		

		for(i = 0; i < MAX_MUSHROOM_NUMBER; i++){
			if(myMushroom[i] != NULL)
				myMushroom[i]->cleanShape(myMario->getColumn(), marioPColumn);	
		
		}

        for(i = 0; i < MAX_CLOUD_NUMBER; i++){
            if(myCloud[i] != NULL)
                myCloud[i]->cleanShape(myMario->getColumn(), marioPColumn);

        }

        if(fabs(myMario->getColumn() - myCastle->getColumn() ) < maxColumn / 2 + myCastle->getWidth())
            myCastle->clean(myMario->getColumn(), marioPColumn);
		


        for(i = 0; i < MAX_TURTLE_NUMBER; i++){
            if(myTurtle[i] != NULL){
                myTurtle[i]->cleanShape(myMario->getColumn(), marioPColumn);
                if(myTurtle[i]->getMovementCounter() % 10 == 0 && !(myTurtle[i]->isInShell()) )
                    myTurtle[i]->moveOneStep();
                if(!(myTurtle[i]->isInShell()))
                    myTurtle[i]->increaseMovementCounter();
                else{
                    myTurtle[i]->increaseInShellCounter();
                }
            }

        }





		
        if(inputChar == KEY_LEFT && (airTimeCounter == 0 || myMario->getOnHigherSurface() == true ) && myMario->authorizeMovement(LEFT, myPillar) ){
			myMario->increaseMovingMarioShapeCounter();
			if(myMario->getMovingMarioShapeCounter() > 0 && myMario->getMovingMarioShapeCounter() < 6)
				myMario->setShapeID(MARIO_RUNNING_ONE, marioPRow, marioPColumn);
			else if(myMario->getMovingMarioShapeCounter() > 10  && myMario->getMovingMarioShapeCounter() < 16)
				myMario->setShapeID(MARIO_RUNNING_TWO, marioPRow, marioPColumn);
			else if(myMario->getMovingMarioShapeCounter() == 0 || (myMario->getMovingMarioShapeCounter() > 5 && myMario->getMovingMarioShapeCounter() < 11) || (myMario->getMovingMarioShapeCounter() >= 16 && myMario->getMovingMarioShapeCounter() < 21)){
				myMario->setShapeID(MARIO_STANDING, marioPRow, marioPColumn);
				if(myMario->getMovingMarioShapeCounter() == 20)
					myMario->zeroMovingMarioShapeCounter();
			}
				 
            myMario->decreaseColoumn();
			myMario->changeDir(LEFT);
            if(prevMove == KEY_RIGHT || prevMove == KEY_LEFT)
                airHMovementCounter = 0;
        }
        if(inputChar == KEY_RIGHT && (airTimeCounter == 0 || myMario->getOnHigherSurface() == true ) && myMario->authorizeMovement(RIGHT, myPillar) )  {
			myMario->increaseMovingMarioShapeCounter();
			if(myMario->getMovingMarioShapeCounter() > 0 && myMario->getMovingMarioShapeCounter() < 6)
				myMario->setShapeID(MARIO_RUNNING_ONE, marioPRow, marioPColumn);
			else if(myMario->getMovingMarioShapeCounter() > 10  && myMario->getMovingMarioShapeCounter() < 16)
				myMario->setShapeID(MARIO_RUNNING_TWO, marioPRow, marioPColumn);
			else if(myMario->getMovingMarioShapeCounter() == 0 || (myMario->getMovingMarioShapeCounter() > 5 && myMario->getMovingMarioShapeCounter() < 11) || (myMario->getMovingMarioShapeCounter() >= 16 && myMario->getMovingMarioShapeCounter() < 21)){
				myMario->setShapeID(MARIO_STANDING, marioPRow, marioPColumn);
				if(myMario->getMovingMarioShapeCounter() == 20)
					myMario->zeroMovingMarioShapeCounter();
				}
            myMario->increseColumn();
			myMario->changeDir(RIGHT);
            if(prevMove == KEY_RIGHT || prevMove == KEY_LEFT)
                airHMovementCounter = 0;
        }


        if(inputChar == KEY_UP && (airTimeCounter == 0 || myMario->getOnHigherSurface() == true)){
            airTimeCounter = 1;
			myMario->setShapeID(MARIO_JUMPING, marioPRow, marioPColumn);
            if(prevMove == KEY_LEFT || prevMove == KEY_RIGHT){
                airHMovementCounter++;
                airHPrevMove = prevMove;
            }
        }

        if (airTimeCounter > 0 && airTimeCounter < 26){
            if(airTimeCounter % 2 == 0){
				marioPRow = myMario->getRow();
                myMario->cleanShape(marioPRow, marioPColumn);
				myMario->pushMario(myPillar);
                myMario->decreaseRow();
                prevMove = KEY_UP;
            }
            airTimeCounter++;
            if (airHMovementCounter != 0){
                if(airHPrevMove == KEY_RIGHT && (airHMovementCounter % 2 == 0) && myMario->authorizeMovement(RIGHT, myPillar) )
                    myMario->increseColumn();
                if( airHPrevMove == KEY_LEFT && (airHMovementCounter % 2 == 0) && myMario->authorizeMovement(LEFT, myPillar) )
                    myMario->decreaseColoumn();
                airHMovementCounter++;
            }
        }

        else if(airTimeCounter > 25){
			
            if( myMario->getOnHigherSurface() == false){
				if(airTimeCounter % 2 == 0){				
					marioPRow = myMario->getRow();
                	myMario->cleanShape(marioPRow, marioPColumn);
					myMario->pushMario(myPillar);
                	myMario->increaseRow();
                	prevMove = KEY_DOWN;
					
				}
				airTimeCounter++;	
            }

			else{
				airHMovementCounter = 0;			
			}
            
            if (airHMovementCounter != 0 ){
                if( airHPrevMove == KEY_RIGHT && (airHMovementCounter % 2 == 0) && myMario->authorizeMovement(RIGHT, myPillar) )
                    myMario->increseColumn();
                if( airHPrevMove == KEY_LEFT && (airHMovementCounter % 2 == 0) && myMario->authorizeMovement(LEFT, myPillar))
                    myMario->decreaseColoumn();
                airHMovementCounter++;
            }
        }

        else if( myMario->getOnHigherSurface() == true ){
        	airTimeCounter = 0;
			myMario->setShapeID(MARIO_STANDING, marioPRow, marioPColumn);
		}



        if(airTimeCounter == 0 )
            airHMovementCounter = 0;
			

		marioPRow = myMario->getRow();



        /*The following 4 'for's can be made into one for due to the equality of their maxium number of objects
         * available in one scene; notwithstanding, it is sepreated into 4 fors to facilitate later modifications
         * and changes
        */

        for(i = 0; i < MAX_PILLAR_NUM; i++){

            //check to see if there is a new pillar in the vicinity of mario to insantiate a new object of Pillar
            if(myPillar[i] == NULL){
                pillarTempCol = searchForNewPillar(myPillar,myMario->getColumn(), maxColumn / 2 + PILLAR_WIDTH + 1, &myPillarCol);


                if(pillarTempCol != -1){
                    myPillar[i] = new Pillar(pillarTempCol, findTheSecondElement(pillarTempCol, scenariofPtr, "pillar"));
                }
            }

            //check to see if the object is needed anymore, if it is it gets printed and if not it is deleted
            if(myPillar[i] != NULL){
                if( checkForDeletingItem(myMario->getColumn(), myPillar[i]->getColumn() , maxColumn / 2 + PILLAR_WIDTH + 1) == 1 ){
                    delete myPillar[i];
                    myPillar[i] = 0;
                }

                else{
                    myPillar[i]->drawPillar(myMario->getColumn(), marioPColumn);
                }
            }

        }



        for(i = 0; i < MAX_MUSHROOM_NUMBER; i++){

            //check to see if there is a new mushroom in the vicinity of mario to insantiate a new object of Mushroom class
            if(myMushroom[i] == NULL){
                mushroomTempCol = searchForNewMushroom(myMushroom, myMario->getColumn(), maxColumn / 2 + MUSHROOM_WIDTH + 1, &mushroomCol);

                if(mushroomTempCol != -1){
                    myMushroom[i] = new Mushroom(mushroomTempCol);
                }
            }

            //check to see if the object is needed anymore, if it is it gets printed and if not it is deleted
            if(myMushroom[i] != NULL){
                if( checkForDeletingItem(myMario->getColumn(), myMushroom[i]->getColumn() , maxColumn / 2 + MUSHROOM_WIDTH + 1) == 1 ){
                    delete myMushroom[i];
                    myMushroom[i] = 0;
                }

                else{
                    myMushroom[i]->drawMushroom(myMario->getColumn(), marioPColumn);
                }
            }

        }




        for(i = 0; i < MAX_TURTLE_NUMBER; i++){

            //check to see if there is a new Turtle in the vicinity of mario to insantiate a new object of Turtle
            if(myTurtle[i] == NULL){
                turtleTempBCol = searchForNewTurtle(myTurtle, myMario->getColumn(), maxColumn  + TURTLE_WIDTH + 1, &turtleCol);



                if(turtleTempBCol != -1){
                    myTurtle[i] = new Turtle(turtleTempBCol, findTheSecondElement(turtleTempBCol, scenariofPtr, "turtle"));
                }
            }

            //check to see if the object is needed anymore, if it is it gets printed and if not it is deleted
            if(myTurtle[i] != NULL){
                if( checkForDeletingItem(myMario->getColumn(), myTurtle[i]->getBeginningColumn() , maxColumn  + TURTLE_WIDTH + 1) == 1 ){
                    delete myTurtle[i];
                    myTurtle[i] = 0;
                }

                else{
                    myTurtle[i]->drawShape(myMario->getColumn(), marioPColumn);
                }
            }

        }


        for(i = 0; i < MAX_CLOUD_NUMBER; i++){

            //check to see if there is a new cloud in the vicinity of mario to insantiate a new object of Cloud class
            if(myCloud[i] == NULL){
                cloudTempCol = searchForNewCloud(myCloud, myMario->getColumn(), maxColumn / 2 + CLOUD_WIDTH + 1, &cloudCol);


                if(cloudTempCol != -1){
                    myCloud[i] = new Cloud(cloudTempCol, findTheSecondElement(cloudTempCol, scenariofPtr, "cloud"));
                }
            }

            //check to see if the object is needed anymore, if it is it gets printed and if not it is deleted
            if(myCloud[i] != NULL){
                if( checkForDeletingItem(myMario->getColumn(), myCloud[i]->getColumn() , maxColumn / 2 + CLOUD_WIDTH + 1) == 1 ){
                    delete myCloud[i];
                    myCloud[i] = 0;
                }

                else{
                    myCloud[i]->drawShape(myMario->getColumn(), marioPColumn);
                }
            }

        }

        if(fabs(myMario->getColumn() - myCastle->getColumn() ) < maxColumn / 2 + myCastle->getWidth())
            myCastle->draw(myMario->getColumn(), marioPColumn);

        myMario->drawShape(marioPRow, marioPColumn);
        usleep(DELAY);
        refresh();
        prevMove = inputChar;
        if(myMario->getColumn() == myCastle->getColumn() + myCastle->getWidth() / 2 - 3){
            myGameStatus = WON;
            showVictoriousMessage(myMario->getScore());
            switch( myMenu->bringMainMenu(0)){
                case 2:
                    restart(myCloud, myMushroom, myTurtle, myPillar);
                    loadItemCols(&myPillarCol, &mushroomCol, &turtleCol, &cloudCol, scenariofPtr);
                    delete myMario;
                    clear();
                    myMario = new Mario(maxRow - 10, marioPColumn);
                    myGameStatus = CONTINUE;
                    break;

                case 4:
                    endwin();
                    cleanHeap(myCloud, myMushroom, myTurtle, myPillar, scenariofPtr);
                    return 0;
                    break;
            }
        }

        else if(myMario->getScore() < 0){
            myGameStatus = LOST;
            showGameOverMessage();
            switch( myMenu->bringMainMenu(0)){
                case 2:
                    restart(myCloud, myMushroom, myTurtle, myPillar);
                    loadItemCols(&myPillarCol, &mushroomCol, &turtleCol, &cloudCol, scenariofPtr);
                    delete myMario;
                    clear();
                    myMario = new Mario(maxRow - 10, marioPColumn);
                    myGameStatus = CONTINUE;
                    break;

                case 4:
                    endwin();
                    cleanHeap(myCloud, myMushroom, myTurtle, myPillar, scenariofPtr);
                    return 0;
                    break;
            }
        }




    }


    endwin();



    cleanHeap(myCloud, myMushroom, myTurtle, myPillar, scenariofPtr);

    return 0;

}

