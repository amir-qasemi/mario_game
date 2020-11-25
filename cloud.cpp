#include "cloud.h"
#include "enumandstructs.h"
#include <ncurses.h>
#include <stdlib.h>


int Cloud::height = CLOUD_HEIGHT;
int Cloud::width = CLOUD_WIDTH;


Cloud::Cloud(int col, int r){
    column = col;
    row = r;
    setCloudShape();
}

void Cloud::setCloudShape(){
    int i, j;
    FILE *cloudShapefPtr;


    if ( (cloudShapefPtr = fopen("cloudShape.txt", "r")) == NULL){
        endwin();
        perror("couldn't find the file");
        exit(1);
    }


    rewind(cloudShapefPtr);


    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            cloudShape[i][j] = fgetc(cloudShapefPtr);
        }
        fgetc(cloudShapefPtr);
    }

    fclose(cloudShapefPtr);
}


int Cloud::getRow(){
    return row;
}



int Cloud::getColumn(){
    return column;
}




int Cloud::getWidth(){
    return width;
}




int Cloud::getHeight(){
    return height;
}



void Cloud::drawShape(int marioCol,int marioPCol){
    int i, j;


    for(i = 0; i < height; i++)
        for(j = 0; j < width; j++){

            switch(cloudShape[i][j]){
                case 'w':
                    attron(COLOR_PAIR(WW));
                    mvprintw(row - (height - i ), marioPCol - ( marioCol - column ) + j, "%c", cloudShape[i][j]);
                    attroff(COLOR_PAIR(WW));
                    break;
                case 'b':
                    attron(COLOR_PAIR(BB));
                    mvprintw(row - (height - i ), marioPCol - ( marioCol - column ) + j, "%c", cloudShape[i][j]);
                    attroff(COLOR_PAIR(BB));
                    break;
                case 'x':
                    attron(COLOR_PAIR(XX));
                    mvprintw(row - (height - i ), marioPCol - ( marioCol - column ) + j, "%c", cloudShape[i][j]);
                    attroff(COLOR_PAIR(XX));
                    break;
            }




    }

}


void Cloud::cleanShape(int marioCol,int marioPCol){
    int i, j;


    for(i = 0; i < height; i++)
        for(j = 0; j < width; j++){
                    mvprintw(row - (height - i ), marioPCol - ( marioCol - column ) + j, " " );
        }

}
