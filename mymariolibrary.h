#ifndef MYMARIOLIBRARY
#define MYMARIOLIBRARY

#include <string.h>
#include <ncurses.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include "enumandstructs.h"
#include "cloud.h"
#include "mario.h"
#include "pillar.h"
#include "mushroom.h"
#include "turtle.h"





enum CK myCK;


void myModifiedBubbleSort(struct itemCol *myItemCol, int size){
    int i, j, checker = 1, temp1;

    for(i = 0; i < size && checker == 1; i++){
        checker = 0;
        for(j = 0; j <  2 * size - 1; j++){
            if(myItemCol->Columns[j] > myItemCol->Columns[j + 1] && myItemCol->Columns[j + 1] != -1){
                temp1 = myItemCol->Columns[j];
                myItemCol->Columns[j] = myItemCol->Columns[j + 1];
                myItemCol->Columns[j + 1] = temp1;
                checker = 1;
            }
        }
    }
}


void checkTerminalSize(){
    int maxHeight, maxWidth;


    getmaxyx(stdscr, maxHeight, maxWidth);

    if(maxHeight < 56 || maxWidth < 206){
        endwin();
        printf("Make your terminal full-screen in order to run the game.");
        exit(1);
    }
}


int initNCursesTerminal(void){
    initscr();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(FALSE);
    noecho();


    checkTerminalSize();


    if(has_colors() == TRUE)
        start_color();
    else{
        endwin();
        printf("Your Terminal does not suppurt colors");
        exit(1);
    }

    init_color(COLOR_YELLOW, 967, 890, 808);
	
    init_pair(BW, COLOR_BLACK, COLOR_WHITE);
    init_pair(RR , COLOR_RED, COLOR_RED);
    init_pair(BB, COLOR_BLACK, COLOR_BLACK);
    init_pair(YY, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(XX, COLOR_BLUE, COLOR_BLUE);
    init_pair(GG, COLOR_GREEN, COLOR_GREEN);
    init_pair(WW, COLOR_WHITE, COLOR_WHITE);
    init_pair(MM, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(CC, COLOR_CYAN, COLOR_CYAN);
    init_pair(WC, COLOR_WHITE, COLOR_CYAN);
    init_pair(WR, COLOR_WHITE, COLOR_RED);
    init_pair(MARIO_HAT_COLOR, COLOR_RED, COLOR_RED);
    init_pair(MARIO_ONE_PIEACE_COLOR, COLOR_BLUE, COLOR_BLUE);
    init_pair(MARIO_SHIRT_COLOR, COLOR_RED, COLOR_RED);
    init_pair(TURTLE_SKIN_COLOR, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(TURTLE_SHELL_COLOR, COLOR_GREEN, COLOR_GREEN);
    init_pair(PILLAR_BODY_COLOR, COLOR_GREEN, COLOR_GREEN);
    init_pair(MUSHROOM_CAP_COLOR, COLOR_RED, COLOR_RED);



    wbkgd(stdscr, COLOR_PAIR(WC));

    return 0;
}


void paintTheGround(){\
    int i, j;
    int maxRow, maxColumn;

    getmaxyx(stdscr, maxRow, maxColumn);

    for(i = maxRow - 2; i < maxRow; i++){
        for(j = 0; j < maxColumn; j++){
            attron(COLOR_PAIR(GG));
            mvprintw(i, j, " ");
            attroff(COLOR_PAIR(GG));
        }
    }
}



void loadItemCols(struct itemCol *myPillsrCol, struct itemCol *myMushroomsCol, struct itemCol *myTurtleCol, struct itemCol *myCloudCol, FILE *scenario){
    int i ,temp1, temp2, size = 0, size2 = 0, size3 = 0, size4 = 0;
    char itemName[7];

    //initilizing all the elements of myItemCol->Columns to -1 which means no item.
    for(i = 0; i < MAX_ITEM_NUM; i++){
        myPillsrCol->Columns[i] = -1;
        myMushroomsCol->Columns[i] = -1;
        myTurtleCol->Columns[i] = -1;
        myCloudCol->Columns[i] = -1;
    }

    rewind(scenario);

    while( !feof(scenario) ){
        fscanf(scenario, "%s%d%d", itemName, &temp1, &temp2);
        fgetc(scenario);
        if(strcmp(itemName, "pillar") == 0){
            myPillsrCol->Columns[size] = temp1;
            size++;
        }
        else if(strcmp(itemName, "mushroom") == 0){
            myMushroomsCol->Columns[size2] = temp1;
            size2++;
        }

        else if(strcmp(itemName, "turtle") == 0){
            myTurtleCol->Columns[size3] = temp1;
            size3++;
        }

        else if(strcmp(itemName, "cloud") == 0){
            myCloudCol->Columns[size4] = temp1;
            size4++;
        }
    }


    myModifiedBubbleSort(myPillsrCol, size);
    myModifiedBubbleSort(myMushroomsCol, size2);
    myModifiedBubbleSort(myTurtleCol, size3);
    myModifiedBubbleSort(myCloudCol, size4);

}

int searchForNewPillar(Pillar *myPillar[MAX_PILLAR_NUM],int center, int radios, struct itemCol *pillarCol){

    int i, j;
    bool alreadyExists;

    for(i = 0; i < MAX_ITEM_NUM; i++){
        alreadyExists = false;
        if(fabs(center - pillarCol->Columns[i])  < radios){
            for(j = 0; j < MAX_PILLAR_NUM; j++){
                if(myPillar[j] != NULL)
                    if(myPillar[j]->getColumn() == pillarCol->Columns[i])
                        alreadyExists = true;
            }
            if(!alreadyExists){
                return pillarCol->Columns[i];
            }
        }
    }

    return -1;
}


int searchForNewMushroom(Mushroom *myMushroom[MAX_MUSHROOM_NUMBER],int center, int radios, struct itemCol *mushroomCol){
    int i, j;
    bool alreadyExists;

    for(i = 0; i < MAX_ITEM_NUM; i++){
        alreadyExists = false;
        if(fabs(center - mushroomCol->Columns[i])  < radios){
            for(j = 0; j < MAX_MUSHROOM_NUMBER; j++){
                if(myMushroom[j] != NULL)
                    if(myMushroom[j]->getColumn() == mushroomCol->Columns[i])
                        alreadyExists = true;
            }
            if(!alreadyExists){
                return mushroomCol->Columns[i];
            }
        }
    }

    return -1;
}



int searchForNewTurtle(Turtle *myTurtle[MAX_TURTLE_NUMBER], int center, int radios, struct itemCol *turtleCol){
    int i, j;
    bool alreadyExists;

    for(i = 0; i < MAX_ITEM_NUM; i++){
        alreadyExists = false;
        if(fabs(center - turtleCol->Columns[i])  < radios){
            for(j = 0; j < MAX_TURTLE_NUMBER; j++){
                if(myTurtle[j] != NULL)
                    if(myTurtle[j]->getBeginningColumn() == turtleCol->Columns[i])
                        alreadyExists = true;
            }
            if(!alreadyExists){
                return turtleCol->Columns[i];
            }
        }
    }

    return -1;
}


int searchForNewCloud(Cloud *myCloud[MAX_CLOUD_NUMBER],int center, int radios, struct itemCol *cloudCol){

    int i , j;
    bool alreadyExist;

    for(i = 0; i < MAX_ITEM_NUM; i++){
        alreadyExist = false;
        if(fabs(center - cloudCol->Columns[i])  < radios){
            for(j = 0; j < MAX_CLOUD_NUMBER; j++){
                if(myCloud[j] != NULL)
                    if(myCloud[j]->getColumn() == cloudCol->Columns[i])
                        alreadyExist = true;
            }
            if(!alreadyExist){
                return cloudCol->Columns[i];
            }
        }
    }


    return -1;
}


int findTheCastleColumn(FILE *scenariofPtr){
    int temp1, temp2;
    char itemName[7];


    rewind(scenariofPtr);

    while( !feof(scenariofPtr) ){
        fscanf(scenariofPtr, "%s%d%d", itemName, &temp1, &temp2);
        fgetc(scenariofPtr);
        if(strcmp(itemName, "castle") == 0){
            return temp1;
        }
    }

    return 1000;
}



int findTheSecondElement(int TempCol,FILE *scenariofPtr,const char *name){
    int temp1, temp2;
    char itemName[7];

    rewind(scenariofPtr);

    while( !feof(scenariofPtr) ){
        fscanf(scenariofPtr, "%s%d%d", itemName, &temp1, &temp2);
        fgetc(scenariofPtr);
        if(strcmp(itemName, name) == 0 && temp1 == TempCol){
            return temp2;
        }

    }

    return 0;

}

inline int checkForDeletingItem(int marioColumn, int itemColumn, int radios){
    if(fabs(marioColumn - itemColumn) > radios)
        return 1;
    else
        return 0;
}


void outPutExtraInfo(int score){
    attron(A_BOLD);
    mvprintw(1, 0, "Press Q To Bring Menu");
    mvprintw(2, 0, "SCORE: %5d", score);
    attroff(A_BOLD);
}



void endGame(){
    printf("No Scenario File Was found\n");
    exit(1);
}




void restart(class Cloud *myCloud[MAX_CLOUD_NUMBER], class Mushroom *myMushroom[MAX_MUSHROOM_NUMBER], class Turtle *myTurtle[MAX_TURTLE_NUMBER], class Pillar *myPillar[MAX_PILLAR_NUM]){
	int i;



	for(i = 0; i < MAX_TURTLE_NUMBER; i++){
		delete myTurtle[i];
		myTurtle[i] = 0;
	}

	for(i = 0; i < MAX_MUSHROOM_NUMBER; i++){
		delete myMushroom[i];
		myMushroom[i] = 0;
	}

	for(i = 0; i < MAX_CLOUD_NUMBER; i++){
		delete myCloud[i];
		myCloud[i] = 0;
	}

	for(i = 0; i < MAX_PILLAR_NUM; i++){
		delete myPillar[i];
		myPillar[i] = 0;
	}


}



void cleanHeap(class Cloud *myCloud[MAX_CLOUD_NUMBER], class Mushroom *myMushroom[MAX_MUSHROOM_NUMBER], class Turtle *myTurtle[MAX_TURTLE_NUMBER], class Pillar *myPillar[MAX_PILLAR_NUM], FILE *scenariofPtr){


	int i;



	for(i = 0; i < MAX_TURTLE_NUMBER; i++){
		delete myTurtle[i];
	}

	for(i = 0; i < MAX_MUSHROOM_NUMBER; i++){
		delete myMushroom[i];
	}

	for(i = 0; i < MAX_CLOUD_NUMBER; i++){
		delete myCloud[i];
	}

	for(i = 0; i < MAX_PILLAR_NUM; i++){
		delete myPillar[i];
	}

	fclose(scenariofPtr);


}


void showVictoriousMessage(int score){
    int maxHeight, maxWidth;
    WINDOW *VMWin;

    getmaxyx(stdscr, maxHeight, maxWidth);
    VMWin = newwin(maxHeight, maxWidth, 0 , 0);
    wborder(VMWin,'*','*','*','*','*','*','*','*');
    wbkgd(VMWin, COLOR_PAIR(BW));


    mvwprintw(VMWin,maxHeight / 2, maxWidth / 2 - 30, "Congratulatios, but the princes is in another castle blah blah blah...");
    wattron(VMWin, A_BOLD);
    mvwprintw(VMWin, maxHeight / 2 + 2, maxWidth / 2 - 30, "Your score is: %d", score);
    wattroff(VMWin, A_BOLD);
    mvwprintw(VMWin, maxHeight / 2 + 4, maxWidth / 2 - 15, "Press any key to continue..." );
    wrefresh(VMWin);

    nodelay(VMWin, FALSE);
    sleep(2);
    wgetch(VMWin);
    sleep(1);
    wclear(VMWin);
    wrefresh(VMWin);
    delwin(VMWin);

}

void showGameOverMessage(){
    int maxHeight, maxWidth;
    WINDOW *GOWin;

    getmaxyx(stdscr, maxHeight, maxWidth);
    GOWin = newwin(maxHeight, maxWidth, 0 , 0);
    wborder(GOWin,'#','#','#','#','#','#','#','#');
    wbkgd(GOWin, COLOR_PAIR(WR));

    wattron(GOWin, A_BOLD);
    mvwprintw(GOWin,maxHeight / 2, maxWidth / 2 - 7, "GAME OVER");
    wattroff(GOWin, A_BOLD);
    mvwprintw(GOWin, maxHeight / 2 + 2, maxWidth / 2 - 15, "Press any key to continue..." );
    wrefresh(GOWin);

    nodelay(GOWin, FALSE);
    sleep(2);
    wgetch(GOWin);
    sleep(1);
    wclear(GOWin);
    wrefresh(GOWin);
    delwin(GOWin);
}

#endif // MYMARIOLIBRARY

