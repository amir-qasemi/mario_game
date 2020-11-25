#include "castle.h"
#include <ncurses.h>
#include <stdlib.h>
#include "enumandstructs.h"


Castle::Castle(int c){
    column = c;
    height = CASTLE_HEIGHT;
    width = CASTLE_WIDTH;
    row = GROUND_ROW;
    setShape();
}

void Castle::draw(int marioCol, int marioPCol){
    int i, j;


    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            switch(shape[i][j]){
                case 'b':
                    attron(COLOR_PAIR(BB));
                    mvprintw(row - (height - i ), marioPCol - ( marioCol - column ) + j, "%c", shape[i][j]);
                    attroff(COLOR_PAIR(BB) );
                    break;
                case 'r':
                    attron(COLOR_PAIR(MM));
                    mvprintw(row - (height - i ), marioPCol - ( marioCol - column ) + j, "%c", shape[i][j] );
                    attroff(COLOR_PAIR(MM) );
                    break;
            }
        }
    }
}

int Castle::getColumn(){
    return column;
}

int Castle::getWidth(){
    return width;
}

void Castle::clean(int marioCol, int marioPCol){
    int i, j;

    for(i = 0; i < height; i++)
        for(j = 0; j < width; j++){
                    mvprintw(row - (height - i ), marioPCol - ( marioCol - column ) + j, " " );
                }
}

void Castle::setShape(){
    int i, j;
    FILE *castleShapefPtr;


    if ( (castleShapefPtr = fopen("castleShape.txt", "r")) == NULL){
        endwin();
        perror("couldn't find the file");
        exit(1);
    }


    rewind(castleShapefPtr);


    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            shape[i][j] = fgetc(castleShapefPtr);
        }
        fgetc(castleShapefPtr);
    }

    fclose(castleShapefPtr);
}




