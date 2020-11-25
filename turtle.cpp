#include <stdlib.h>
#include <ncurses.h>
#include "turtle.h"
#include "enumandstructs.h"

int Turtle::height = TURTLE_HEIGHT;
int Turtle::width = TURTLE_WIDTH;



Turtle::Turtle(int bColumn, int eColumn){
    beginningColumn = bColumn;
    endingColumn = eColumn;
    setShape();
    column = (bColumn + eColumn) / 2;
    row = GROUND_ROW;
    turtleMovementCounter = 0;
    if(rand() % 2 == 1)
        turtleDirection = LEFT;
    else
        turtleDirection = RIGHT;
    shapeID = TURTLE_ONE;
    inShell = false;
    inShellCounter = 0;

}

void Turtle::increaseColumn(){
    column++;
}

void Turtle::decreaseColumn(){
    column--;
}

void Turtle::changeDirection(){
    if(turtleDirection == LEFT)
        turtleDirection = RIGHT;
    else if(turtleDirection == RIGHT)
        turtleDirection = LEFT;
}

int Turtle::getRow(){
    return row;
}

int Turtle::getColumn(){
    return column;
}

int Turtle::getHeight(){
return height;
}

int Turtle::getWidth(){
    return width;
}

int Turtle::getShapeID(){
    return shapeID;
}

void Turtle::drawShape(int marioCol, int marioPCol){
    int i, j;

    if(turtleDirection == RIGHT){

        for(i = 0; i < TURTLE_HEIGHT; i++){

            for(j = 0; j < TURTLE_WIDTH; j++){

                switch (turtleShape[shapeID][i][TURTLE_WIDTH - 1 - j]){
                    case 'x':
                        attron(COLOR_PAIR(TURTLE_SHELL_COLOR));
                        mvprintw(row - (height - i ), marioPCol - ( marioCol - column ) + j, "%c", turtleShape[shapeID][i][TURTLE_WIDTH - 1 - j]);
                        attroff(COLOR_PAIR(TURTLE_SHELL_COLOR));
                        break;
                    case 'b':
                        attron(COLOR_PAIR(BB));
                        mvprintw(row - (height - i ), marioPCol - ( marioCol - column ) + j, "%c", turtleShape[shapeID][i][TURTLE_WIDTH - 1 - j]);
                        attroff(COLOR_PAIR(BB) );
                        break;
                    case 'l':
                        attron(COLOR_PAIR(TURTLE_SKIN_COLOR));
                        mvprintw(row - (height - i ), marioPCol - ( marioCol - column ) + j, "%c",turtleShape[shapeID][i][TURTLE_WIDTH - 1 - j]);
                        attroff(COLOR_PAIR(TURTLE_SKIN_COLOR));
                        break;
                    case 'w':
                        attron(COLOR_PAIR(MM));
                        mvprintw(row - (height - i ), marioPCol - ( marioCol - column ) + j, "%c", turtleShape[shapeID][i][TURTLE_WIDTH - 1 - j]);
                        attroff(COLOR_PAIR(MM));
                        break;

                }
            }
        }

    }


    else{ //if(turtleDirection == LEFT){
        for(i = 0; i < TURTLE_HEIGHT; i++){
            for(j = 0; j < TURTLE_WIDTH; j++){
                switch (turtleShape[shapeID][i][j]){
                case 'x':
                    attron(COLOR_PAIR(TURTLE_SHELL_COLOR));
                    mvprintw(row - (height - i ), marioPCol - ( marioCol - column ) + j, "%c", turtleShape[shapeID][i][j]);
                    attroff(COLOR_PAIR(TURTLE_SHELL_COLOR));
                    break;
                case 'b':
                    attron(COLOR_PAIR(BB));
                    mvprintw(row - (height - i ), marioPCol - ( marioCol - column ) + j, "%c", turtleShape[shapeID][i][j]);
                    attroff(COLOR_PAIR(BB) );
                    break;
                case 'l':
                    attron(COLOR_PAIR(TURTLE_SKIN_COLOR));
                    mvprintw(row - (height - i ), marioPCol - ( marioCol - column ) + j, "%c",turtleShape[shapeID][i][j]);
                    attroff(COLOR_PAIR(TURTLE_SKIN_COLOR) );
                    break;
                case 'w':
                    attron(COLOR_PAIR(MM));
                    mvprintw(row - (height - i ), marioPCol - ( marioCol - column ) + j, "%c", turtleShape[shapeID][i][j]);
                    attroff(COLOR_PAIR(MM));
                    break;
                }
            }
        }
    }


}



void Turtle::cleanShape(int marioCol, int marioPCol){
    int i, j;
    for(i = 0; i < height; i++)
        for(j = 0; j < width; j++){
                    mvprintw(row - (height - i ), marioPCol - ( marioCol - column ) + j, " " );
                }
}



void Turtle::changeShapeID(int i){
    if(i >= 0 && i < 3)
        shapeID = i;
}

void Turtle::moveOneStep(){

    if(turtleDirection == LEFT)
        column--;

    else if(turtleDirection == RIGHT)
        column++;


    if(column == endingColumn || column == beginningColumn)
        changeDirection();


    if(shapeID == TURTLE_ONE)
        shapeID = TURTLE_TWO;
    else if(shapeID == TURTLE_TWO)
        shapeID = TURTLE_ONE;


}

void Turtle::increaseInShellCounter(){
    if(inShellCounter == 200){
        inShell = false;
        inShellCounter = 0;
        changeShapeID(TURTLE_ONE);
    }
    else{
        inShellCounter++;
    }

}

bool Turtle::isInShell(){
    return inShell;
}

void Turtle::SetInShellStatus(bool inShellStatus){
    if(inShellStatus == true){
        inShell = true;
        shapeID = TURTLE_IN_SHELL;
    }
    else
        inShell = false;
}

int Turtle::getOneOfTurtleShapeChars(int i , int j){
    return turtleShape[shapeID][i][j];
}



void Turtle::setShape(){
    int i, j, z;
    FILE *turtleShapefPtr;
    

    if ( (turtleShapefPtr = fopen("turtleShape.txt", "r")) == NULL){
		endwin();
		perror("couldn't find the file");
		exit(1);
	}

        //mvprintw(3, 0, "drawing");refresh();


    rewind(turtleShapefPtr);
    
    for(z = 0; z < TURTLE_SHAPE_NUMBER; z++){
        while (fgetc(turtleShapefPtr) != 'a' + z);
        fgetc(turtleShapefPtr);
        for(i = 0; i < TURTLE_HEIGHT; i++){
            for(j = 0; j < TURTLE_WIDTH; j++){
                turtleShape[z][i][j] = fgetc(turtleShapefPtr);
            }
			fgetc(turtleShapefPtr);
        }
    }
}



void Turtle::increaseMovementCounter(){
    turtleMovementCounter++;
}


int Turtle::getMovementCounter(){
    return turtleMovementCounter;
}

int Turtle::getBeginningColumn(){
    return beginningColumn;
}





