#include "mushroom.h"
#include "enumandstructs.h"
#include <ncurses.h>
#include <stdlib.h>

int Mushroom::row = MUSHROOM_GROUND_ROW;
int Mushroom::width = MUSHROOM_WIDTH;
int Mushroom::height = MUSHROOM_HEIGHT;

Mushroom::Mushroom(int col){
    column = col;
    setMushroomShape();
}


void Mushroom::setMushroomShape(){
    int i, j;
    FILE *mushroomShapefPtr;


    if ( (mushroomShapefPtr = fopen("mushroomShape.txt", "r")) == NULL){
        endwin();
        perror("couldn't find the file");
        exit(1);
    }


    rewind(mushroomShapefPtr);


    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            mushroomShape[i][j] = fgetc(mushroomShapefPtr);
        }
        fgetc(mushroomShapefPtr);
    }
	
	fclose(mushroomShapefPtr);
}



int Mushroom::getRow(){
    return row;
}



int Mushroom::getColumn(){
    return column;
}




int Mushroom::getWidth(){
    return width;
}




int Mushroom::getHeight(){
    return height;
}

int Mushroom::getOneOfMushroomShapeChars(int i, int j){
    return mushroomShape[i][j];
}



void Mushroom::drawMushroom(int marioCol,int marioPCol){
    int i, j;


    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            switch (mushroomShape[i][j]){
                case 'l':
                    attron(COLOR_PAIR(BB));
                    mvprintw(row - (height - i ), marioPCol - ( marioCol - column ) + j, "%c", mushroomShape[i][j]);
                    attroff(COLOR_PAIR(BB) );
                    break;
                case 'y':
                    attron(COLOR_PAIR(MUSHROOM_CAP_COLOR));
                    mvprintw(row - (height - i ), marioPCol - ( marioCol - column ) + j, "%c", mushroomShape[i][j] );
                    attroff(COLOR_PAIR(MUSHROOM_CAP_COLOR));
                    break;
                case 'w':
                    attron(COLOR_PAIR(WW));
                    mvprintw(row - (height - i ), marioPCol - ( marioCol - column ) + j, "%c",mushroomShape[i][j]);
                    attroff(COLOR_PAIR(WW) );
                    break;
            }
        }
    }
}


void Mushroom::cleanShape(int marioCol,int marioPCol){
    int i, j;


    for(i = 0; i < height; i++)
        for(j = 0; j < width; j++){
                    mvprintw(row - (height - i ), marioPCol - ( marioCol - column ) + j, " " );
                }


}
