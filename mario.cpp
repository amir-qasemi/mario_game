#include "mario.h"
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>






Mario::Mario(int groundRow, int initialColumn){
    shapeID = MARIO_JUMPING;
    marioDirection = RIGHT;
    setMarioShape();
    setRow(groundRow);
    setColumn(initialColumn);
	movingMarioShapeCounter = 0;
	onHigherSurface = true;
    score = 20;
}




void Mario::setRow(int groundRow){
    row = groundRow;
}





void Mario::setColumn(int initColumn){
    column = initColumn;

}





void Mario::setMarioShape(){
    int i, j, z;
    FILE *marioShapefPtr;
    

    if ( (marioShapefPtr = fopen("marioShape.txt", "r")) == NULL){
		endwin();
		perror("couldn't find the file");
		exit(1);
	}
		

    rewind(marioShapefPtr);
    
    for(z = 0; z < MARIO_SHAPE_NUMBER; z++){
        while (fgetc(marioShapefPtr) != 'a' + z);
        fgetc(marioShapefPtr);
        for(i = 0; i < MARIO_HEIGHT; i++){
            for(j = 0; j < MARIO_WIDTH; j++){
                marioShape[z][i][j] = fgetc(marioShapefPtr);
            }
			fgetc(marioShapefPtr);
        }
    }
}




void Mario::increaseRow(){
    row++;
}





void Mario::decreaseRow(){
    row--;
}





void Mario::increseColumn(){
    column++;
}





void Mario::decreaseColoumn(){
    column--;
}


void Mario::increaseScore(){
    score += 5;
}


void Mario::decreaseScore(){
    score -= 10;
}





int Mario::getRow(){
    return row;
}





int Mario::getColumn(){
    return column;
}




int Mario::getMovingMarioShapeCounter(){
	return movingMarioShapeCounter;
}



void Mario::increaseMovingMarioShapeCounter(){
	movingMarioShapeCounter++;
}

void Mario::zeroMovingMarioShapeCounter(){
	movingMarioShapeCounter = 0;
}


void Mario::setShapeID(int id, int pRow, int pColumn){
    if(id < MARIO_SHAPE_NUMBER && id >=0){
        shapeID = id;
        cleanShape(pRow, pColumn);
    }
}



int Mario::getShapID(){
    return shapeID;
}


bool Mario::getOnHigherSurface(){
	return onHigherSurface;
}


int Mario::getScore(){
	return score;
}


void Mario::changeDir(int direction){

    if(direction == RIGHT){
        marioDirection = RIGHT;
    }

    else if(direction == LEFT){
        marioDirection = LEFT;
    }
}







void Mario::drawShape(int pRow, int pColumn){
    int i, j, z;
    int r, c;

    r = pRow - MARIO_HEIGHT;
    c = pColumn;


    if(marioDirection == LEFT){

        for(i = 0; i < MARIO_HEIGHT; i++){

            for(j = 0, z = MARIO_WIDTH - 1 ; j < MARIO_WIDTH; j++, z--){

                switch (marioShape[shapeID][i][z]){
                    case 'x':
                        attron(COLOR_PAIR(MARIO_HAT_COLOR));
                        mvprintw(r + i, c + j, "%c", marioShape[shapeID][i][z]);
                        attroff(COLOR_PAIR(MARIO_HAT_COLOR) );
                        break;
                    case 'l':
                        attron(COLOR_PAIR(BB));
                        mvprintw(r + i, c + j, "%c", marioShape[shapeID][i][z]);
                        attroff(COLOR_PAIR(BB) );
                        break;
                    case 'g':
                        attron(COLOR_PAIR(YY));
                        mvprintw(r + i, c + j, "%c", marioShape[shapeID][i][z]);
                        attroff(COLOR_PAIR(YY));
                        break;
                    case 'b':
                        attron(COLOR_PAIR(MARIO_ONE_PIEACE_COLOR));
                        mvprintw(r + i, c + j, "%c", marioShape[shapeID][i][z]);
                        attroff(COLOR_PAIR(MARIO_ONE_PIEACE_COLOR) );
                        break;
                    case 'y':
                        attron(COLOR_PAIR(GG));
                        mvprintw(r + i, c + j, "%c", marioShape[shapeID][i][z]);
                        attroff(COLOR_PAIR(GG) );
                        break;
                    case 'm':
                        attron(COLOR_PAIR(BB));
                        mvprintw(r + i, c + j, "%c", marioShape[shapeID][i][z]);
                        attroff(COLOR_PAIR(BB) );
                        break;
                    case 't':
                        attron(COLOR_PAIR(MARIO_SHIRT_COLOR));
                        mvprintw(r + i, c + j, "%c", marioShape[shapeID][i][z]);
                        attroff(COLOR_PAIR(MARIO_SHIRT_COLOR));
                        break;

                }
            }
        }

    }


    else{ //if(marioDirection == RIGHT){
        for(i = 0; i < MARIO_HEIGHT; i++){
            for(j = 0; j < MARIO_WIDTH; j++){
                switch (marioShape[shapeID][i][j]){
                    case 'x':
                        attron(COLOR_PAIR(MARIO_HAT_COLOR));
                        mvprintw(r + i, c + j, "%c", marioShape[shapeID][i][j]);
                        attroff(COLOR_PAIR(MARIO_HAT_COLOR) );
                        break;
                    case 'l':
                        attron(COLOR_PAIR(BB));
                        mvprintw(r + i, c + j, "%c", marioShape[shapeID][i][j]);
                        attroff(COLOR_PAIR(BB) );
                        break;
                    case 'g':
                        attron(COLOR_PAIR(YY));
                        mvprintw(r + i, c + j, "%c", marioShape[shapeID][i][j]);
                        attroff(COLOR_PAIR(YY) );
                        break;
                    case 'b':
                        attron(COLOR_PAIR(MARIO_ONE_PIEACE_COLOR));
                        mvprintw(r + i, c + j, "%c", marioShape[shapeID][i][j]);
                        attroff(COLOR_PAIR(MARIO_ONE_PIEACE_COLOR) );
                        break;
                    case 'y':
                        attron(COLOR_PAIR(GG));
                        mvprintw(r + i, c + j, "%c", marioShape[shapeID][i][j]);
                        attroff(COLOR_PAIR(GG) );
                        break;
                    case 'm':
                        attron(COLOR_PAIR(BB));
                        mvprintw(r + i, c + j, "%c", marioShape[shapeID][i][j]);
                        attroff(COLOR_PAIR(BB) );
                        break;
                    case 't':
                        attron(COLOR_PAIR(MARIO_SHIRT_COLOR));
                        mvprintw(r + i, c + j, "%c", marioShape[shapeID][i][j]);
                        attroff(COLOR_PAIR(MARIO_SHIRT_COLOR) );
                        break;

                }
            }
        }
    }


}

void Mario::cleanShape(int pRow, int pColumn){
    int i, j;   
    int r, c;

    r = pRow - MARIO_HEIGHT;
    c = pColumn;
    
    for(i = 0; i < MARIO_HEIGHT; i++){
        for(j = 0; j < MARIO_WIDTH; j++){
            mvprintw(r + i, c + j, " ");
        }
    }
    
}




bool Mario::authorizeMovement(enum direction movementDirection, class Pillar *myPillar[MAX_PILLAR_NUM]){
    int i;
    

    
    
    if(movementDirection == RIGHT){
        for(i = 0; i < MAX_PILLAR_NUM; i++){
            if(myPillar[i] != NULL){
                if(column + MARIO_WIDTH >= myPillar[i]->getColumn() && column  <= myPillar[i]->getColumn() + myPillar[i]->getWidth() / 2 && row > myPillar[i]->getRow() - myPillar[i]->getHeight())
					return false;
            }
        }
    }

	else if(movementDirection == LEFT){
    	if(column <= 0)
			return false;

		for(i = 0; i < MAX_PILLAR_NUM; i++){
            if(myPillar[i] != NULL){
                if(column  <= myPillar[i]->getColumn() + myPillar[i]->getWidth() && column + MARIO_WIDTH / 2 >= myPillar[i]->getColumn() && row > myPillar[i]->getRow() - myPillar[i]->getHeight())
					return false;
            }
        }
	}

	else if(movementDirection == DOWN){
		for(i = 0; i < MAX_PILLAR_NUM; i++){
			if(myPillar[i] != NULL){
                if(column  >= myPillar[i]->getColumn() && column  <= myPillar[i]->getColumn() + myPillar[i]->getWidth() && row == myPillar[i]->getRow() - myPillar[i]->getHeight())
					return false;
			}
		}

	}


	return true;

        

}

void Mario::changeOnHigherSurfaceStatus(){
	
	if(onHigherSurface == true)
		onHigherSurface = false;

	if(onHigherSurface == false)
		onHigherSurface = true;

}




void Mario::checkOnHigherSurface(class Pillar *myPillar[MAX_PILLAR_NUM], int groundRow){
	int i;


	for(i = 0; i < MAX_PILLAR_NUM; i++){
		if(myPillar[i] != NULL){
			if(column + MARIO_WIDTH / 2 + 5 >= myPillar[i]->getColumn() && column + 2 <= myPillar[i]->getColumn() + myPillar[i]->getWidth() && row == myPillar[i]->getRow() - myPillar[i]->getHeight() ){
					onHigherSurface = true;
					return;
				
			}

		}	

	}
	if(row == groundRow){
		onHigherSurface = true;
		return;
	}
	onHigherSurface = false;

}



void Mario::pushMario(class Pillar *myPillar[MAX_PILLAR_NUM]){
	int i;

	for(i = 0; i < MAX_PILLAR_NUM; i++){
		if(myPillar[i] != NULL){
			if(marioDirection == LEFT){
				if(column  == myPillar[i]->getColumn() + myPillar[i]->getWidth() && row  + 1== myPillar[i]->getRow() - myPillar[i]->getHeight()){
					column -= 7;
				}	
			}
		
			if(marioDirection == RIGHT){
				if(column + MARIO_WIDTH  == myPillar[i]->getColumn() && row + 1 == myPillar[i]->getRow() - myPillar[i]->getHeight() ){
					column += 6;
				}
				
			}

		}
	}

	if(marioDirection == LEFT){
		if(column + MARIO_WIDTH / 2 == myPillar[i]->getColumn()  && row + 1 == myPillar[i]->getRow() - myPillar[i]->getHeight()){
			column -= 7;
		}	
	}



}




void Mario::checkColliding(class Mushroom *myMushroom[MAX_MUSHROOM_NUMBER], struct itemCol *mushroomCol, int marioPColumn, class Turtle *myTurtle[MAX_TURTLE_NUMBER], unsigned & airTimeCounter){
    int i, j, z, k, m;


    //if()



	//checks to see if mario's has collided with any mushroomm or not
    //if(column >= myMushroom[i]->getColumn() && column <= myMushroom[i]->getColumn() + myMushroom[i]->getWidth() && row <= myMushroom[i]->getRow() && row >= myMushroom[i]->getRow() - myMushroom[i]->getHeight())



    for(i = 0; i < MAX_MUSHROOM_NUMBER; i++){
        if(myMushroom[i] != NULL){
            for(j = 0; j < MARIO_WIDTH; j++){
                for(z = 0; z < MARIO_HEIGHT; z++){
                    if(marioShape[shapeID][j][z] != '-'){
                        for(k = 0; k < myMushroom[i]->getHeight(); k++){
                            for(m = 0; m < myMushroom[i]->getWidth(); m++){
                                if(myMushroom[i] != NULL){
                                    if(myMushroom[i]->getOneOfMushroomShapeChars(k, m) != '-'){


                                        if(row - j == myMushroom[i]->getRow() + k && column + z == myMushroom[i]->getColumn() + m){
                                            increaseScore();
                                            deleteColOfStruct(mushroomCol, myMushroom[i]->getColumn());
                                            myMushroom[i]->cleanShape(column, marioPColumn);
                                            delete myMushroom[i];
                                            myMushroom[i] = 0;
                                            break;

                                        }
                                    }
                                }
                            }
                        }
                    }
                }

            }
        }



    }

    //Three parts of the turtle is checked(downmost left of the mario, downmost middle and downmost right) to ensure that the collisons get handled properly
    for(i = 0 ; i < MAX_TURTLE_NUMBER; i++){
        if(myTurtle[i] != NULL){
            if(!myTurtle[i]->isInShell()){
                if( column >= myTurtle[i]->getColumn() && column <= myTurtle[i]->getColumn() + myTurtle[i]->getWidth() && row <= myTurtle[i]->getRow() && row >= myTurtle[i]->getRow() - myTurtle[i]->getHeight() / 2 ){
                    myTurtle[i]->SetInShellStatus(true);
                    decreaseScore();
                }

                else if(column + MARIO_WIDTH >= myTurtle[i]->getColumn() && column + MARIO_WIDTH <= myTurtle[i]->getColumn() + myTurtle[i]->getWidth() && row <= myTurtle[i]->getRow() && row >= myTurtle[i]->getRow() - myTurtle[i]->getHeight() / 2 ){
                    myTurtle[i]->SetInShellStatus(true);
                    decreaseScore();
                }

                else if( column + MARIO_WIDTH / 2 >= myTurtle[i]->getColumn() && column + MARIO_WIDTH / 2 <= myTurtle[i]->getColumn() + myTurtle[i]->getWidth() && row <= myTurtle[i]->getRow() && row >= myTurtle[i]->getRow() - myTurtle[i]->getHeight() / 2 ){
                    myTurtle[i]->SetInShellStatus(true);
                    decreaseScore();
                }

                else if( column >= myTurtle[i]->getColumn() && column <= myTurtle[i]->getColumn() + myTurtle[i]->getWidth() && row <= myTurtle[i]->getRow() - myTurtle[i]->getHeight() / 2 && row >= myTurtle[i]->getRow() - myTurtle[i]->getHeight() ){
                    myTurtle[i]->SetInShellStatus(true);
                    airTimeCounter = 15;
                }

                else if(column + MARIO_WIDTH >= myTurtle[i]->getColumn() && column + MARIO_WIDTH <= myTurtle[i]->getColumn() + myTurtle[i]->getWidth() && row <= myTurtle[i]->getRow() - myTurtle[i]->getHeight() / 2 && row >= myTurtle[i]->getRow() - myTurtle[i]->getHeight() ){
                    myTurtle[i]->SetInShellStatus(true);
                    airTimeCounter = 15;
                }

                else if(column + MARIO_WIDTH / 2 >= myTurtle[i]->getColumn() && column + MARIO_WIDTH / 2 <= myTurtle[i]->getColumn() + myTurtle[i]->getWidth() && row <= myTurtle[i]->getRow() - myTurtle[i]->getHeight() / 2 && row >= myTurtle[i]->getRow() - myTurtle[i]->getHeight()){
                    myTurtle[i]->SetInShellStatus(true);
                    airTimeCounter = 15;
                }
            }
        }
    }

}


void Mario::deleteColOfStruct(struct itemCol *mushroomCol, int deletingCol){
	for(int i = 0; i < MAX_ITEM_NUM; i++){
		if(mushroomCol->Columns[i] == deletingCol)
			mushroomCol->Columns[i] = -1;
	}	
}
