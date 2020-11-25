#include "pillar.h"
#include "enumandstructs.h"
#include <ncurses.h>


int Pillar::row = PILLAR_ROW;
int Pillar::width = PILLAR_WIDTH;


Pillar::Pillar(int col, int h){
    column = col;
    height = h;
}



int Pillar::getRow(){
    return row;
}



int Pillar::getColumn(){
    return column;
}




int Pillar::getWidth(){
    return width;
}




int Pillar::getHeight(){
    return height;
}



void Pillar::drawPillar(int marioCol,int marioPCol){
    int i, j;


    for(i = 0; i < height; i++)
        for(j = 0; j < width; j++){
            if(i == 0 || j == 0 || j == width - 1){
                attron(COLOR_PAIR(BB));
                    mvprintw(row - (height - i ), marioPCol - ( marioCol - column ) + j, "-" );
                attroff(COLOR_PAIR(BB));
            }

            else{
            attron(COLOR_PAIR(PILLAR_BODY_COLOR));
                  mvprintw(row  - (height - i ), marioPCol - ( marioCol - column ) + j, "-" );
            attroff(COLOR_PAIR(PILLAR_BODY_COLOR));
            }
        }

}


void Pillar::cleanPillar(int marioCol,int marioPCol){
    int i, j;


    for(i = 0; i < height; i++)
        for(j = 0; j < width; j++){
                    mvprintw(row - (height - i ), marioPCol - ( marioCol - column ) + j, " " );
		}
              
}
