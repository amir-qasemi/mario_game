#include "menu.h"
#include <ncurses.h>
#include <string.h>
#include "enumandstructs.h"



int Menu::bringMainMenu(const int i){
	WINDOW *menuWin;
	int currentChoice, counter, counter2;
	const char *menuChoices[CHOICES_NUMBER] = {"Resume", "Restart", "Play" , "Setting", "Quit"};
	int c, maxHeight, maxWidth; 
	
	
	getmaxyx(stdscr, maxHeight, maxWidth);
	if(i == 0){
		menuWin = newwin(maxHeight, maxWidth, 0 , 0);
		wborder(menuWin,'*','*','*','*','*','*','*','*');
	}
	else{
		menuWin = newwin( (int)(maxHeight / 2), (int)(maxWidth / 2), (int)(maxHeight / 4), (int)(maxWidth / 4) - 7);
		getmaxyx(menuWin, maxHeight, maxWidth);
		wborder(menuWin,'$','$','$','$','$','$','$','$');
	}


	keypad(menuWin, TRUE);
	nodelay(menuWin, TRUE);
	
	if(i == 0)
		currentChoice = 2;
	else
		currentChoice = 0;


    while(1){
		c = wgetch(menuWin);
		
		if(i == 0){

			if(c == KEY_UP){
				if(currentChoice == 2)
					currentChoice = 4;
				else
					currentChoice--;
			}

			else if(c == KEY_DOWN){
				if(currentChoice == 4)
					currentChoice = 2;
				else
					currentChoice++;
			}
		}

		else{	
		
			if(c == KEY_UP){
				if(currentChoice == 3)
					currentChoice -= 2;
				else if(currentChoice == 0)
					currentChoice = 4;
				else
					currentChoice--;
			}

			else if(c == KEY_DOWN){
				if(currentChoice == 1)
					currentChoice += 2;
				else if(currentChoice == 4)
					currentChoice = 0;
				else
					currentChoice++;							
			}
		}
			


		if(i == 0){
			for(counter = 2; counter < CHOICES_NUMBER; counter++){
				if(currentChoice == counter){
					wattron(menuWin,COLOR_PAIR(1));
					mvwprintw(menuWin, maxHeight / 2 - 2 + counter, maxWidth / 2 - 5 , "%s", menuChoices[counter]);
					wattroff(menuWin, COLOR_PAIR(1));
				}
				
				else{
					mvwprintw(menuWin , maxHeight / 2 - 2 + counter, maxWidth / 2 - 5 , "%s", menuChoices[counter]);
				}
			}
		}

		
		else{
			counter2 =0;
			for(counter = 0 ; counter < CHOICES_NUMBER; counter++){
				if(counter == 2)
					continue;
				counter2++;				
				if(currentChoice == counter){
					wattron(menuWin,A_REVERSE | A_BLINK);
					mvwprintw(menuWin,maxHeight / 2 - 2 + counter2, maxWidth / 2 - 5 , "%s", menuChoices[counter]);
					wattroff(menuWin,A_REVERSE | A_BLINK);
				}
				
				else{
					mvwprintw(menuWin,maxHeight / 2 - 2 + counter2, maxWidth / 2 - 5 , "%s", menuChoices[counter]);
				}
			}
		}

		wrefresh(menuWin);
		

		if (c == 'q' || c == 'Q'){
			wclear(menuWin);
			delwin(menuWin);
			return 0;
		}		

		//entering the return values of the chosen choice			
		if (c == '\n' && currentChoice != 3){
			wclear(menuWin);
			delwin(menuWin);
			return currentChoice;
		}
		
		else if(c == '\n' && currentChoice == 3){
			bringSettingMenu(i);
            if(i == 0){
                wborder(menuWin,'*','*','*','*','*','*','*','*');
            }
            else{
                wborder(menuWin,'$','$','$','$','$','$','$','$');
            }
		}


	}

}


/* At first look, Some parts of this function may seem blendable with other parts in order to make it shorter. But this
 * lenghty nature of the function is made on purpose to make it easier for latter changes and modifications. if it was shorter,
 * for changing a small part the whole function should be changed
*/
void Menu::bringSettingMenu(const int i){
	WINDOW *settingMenuWin;
    int currentChoice, subMenuCurrentChoice = 0, colorSubMenuCurrentChoice = 0, j, z, k, temp = 0, mainChoicesStartingRow, mainChoicesStartingColumn, subChoicesStartingColumn;
    int subColorMenuRow;

    bool isSubMenuActive = false;
    int activeSubMenuNumber = -1;

    bool isColorSubMenuActive = false;
    int activeColorSubMenuNumber = -1;


    const char *settingMenuChoices[SETTING_CHOICES_NUMBER] = {"Mario's Cloth Color", "Turtle Color" , "Pillar Color", "Mushroom Color"};

    const char *marioSubMenuChoices[MARIO_SUB_CHOICES_NUMBER] = {"Mario's Cap Color", "Mario's Shirt Color", "Mario's One-piece Jean Color"};
	const char *turtleSubMenuChoices[TURTLE_SUB_CHOICES_NUMBER] = {"Turtle's Skin Color", "Turtle's Shell Color"};
	const char *pillarSubMenuChoices[PILLAR_SUB_CHOICES_NUMBER] = {"Pillar's Body Color"};
	const char *mushroomSubMenuChoices[MUSHROOM_SUB_CHOICES_NUMBER] = {"Mushroom's Umberella Color"};


    const char *marioCapColorSubMenu[MARIO_CAP_COLOR_NUM] = {"Red", "Green"};
    const char *marioShirtColorSubMenu[MARIO_SHIRT_COLOR_NUM] = {"Blue", "White"};
    const char *marioOPColorSubMenu[MARIO_OP_COLOR_NUM] = {"Blue", "Yellow"};

    const char *turtleSkinColorSubMenu[TURTLE_SKIN_COLOR_NUM] = {"White", "Yellow"};
    const char *turtleShellColorSubMenu[TURTLE_SHELL_COLOR_NUM] = {"Green", "Blue"};

    const char *pillarBodyColorSubMenu[PILLAR_BODY_COLOR_NUM] = {"Green", "Blue"};

    const char *mushroomCapColorSubMenu[MUSHROOM_CAP_COLOR_NUM] = {"Green", "Red"};



	int c, maxHeight, maxWidth; 
	
	
	getmaxyx(stdscr, maxHeight, maxWidth);
	if(i == 0){
		settingMenuWin = newwin(maxHeight, maxWidth, 0 , 0);
		wborder(settingMenuWin,'*','*','*','*','*','*','*','*');
	}
	else{
		settingMenuWin = newwin( (int)(maxHeight / 2), (int)(maxWidth / 2), (int)(maxHeight / 4), (int)(maxWidth / 4) - 7);
		getmaxyx(settingMenuWin, maxHeight, maxWidth);
		wborder(settingMenuWin,'$','$','$','$','$','$','$','$');
	}

    mainChoicesStartingRow = maxHeight / 2 - 3;
    mainChoicesStartingColumn = maxWidth / 2 - 7;
    subChoicesStartingColumn = maxWidth / 2;


	keypad(settingMenuWin, TRUE);
	nodelay(settingMenuWin, TRUE);
	
	currentChoice = 0;


	while(1){
		c = wgetch(settingMenuWin);

        //the part which handles the movement of the active choice using arrow keys
		if(!isSubMenuActive){
		
			if(c == KEY_UP){
                if(currentChoice == 0)
                    currentChoice = SETTING_CHOICES_NUMBER - 1;
				else
                    currentChoice--;
			}
	
			else if(c == KEY_DOWN){
                if(currentChoice == SETTING_CHOICES_NUMBER - 1)
                    currentChoice = 0;
				else
                    currentChoice++;
			}
		}
	
		
        else if(isSubMenuActive && !isColorSubMenuActive){
			switch(activeSubMenuNumber){
                case 0:
                    if(c == KEY_UP){
                        if(subMenuCurrentChoice  == 0)
                            subMenuCurrentChoice = MARIO_SUB_CHOICES_NUMBER - 1;
                        else
                            subMenuCurrentChoice--;
                    }

                    else if(c == KEY_DOWN){
                        if(subMenuCurrentChoice == MARIO_SUB_CHOICES_NUMBER - 1)
                            subMenuCurrentChoice = 0;
                        else
                            subMenuCurrentChoice++;
                    }

                    break;

                case 1:
                    if(c == KEY_UP){
                        if(subMenuCurrentChoice  == 0)
                            subMenuCurrentChoice = TURTLE_SUB_CHOICES_NUMBER - 1;
                        else
                            subMenuCurrentChoice--;
                    }

                    else if(c == KEY_DOWN){
                        if(subMenuCurrentChoice == TURTLE_SUB_CHOICES_NUMBER - 1)
                            subMenuCurrentChoice = 0;
                        else
                            subMenuCurrentChoice++;
                    }

                    break;

                case 2:

                    if(c == KEY_UP){
                        if(subMenuCurrentChoice  == 0)
                            subMenuCurrentChoice = PILLAR_SUB_CHOICES_NUMBER - 1;
                        else
                            subMenuCurrentChoice--;
                    }

                    else if(c == KEY_DOWN){
                        if(subMenuCurrentChoice == PILLAR_SUB_CHOICES_NUMBER - 1)
                            subMenuCurrentChoice = 0;
                        else
                            subMenuCurrentChoice++;
                    }

                    break;


                case 3:
                    if(c == KEY_UP){
                        if(subMenuCurrentChoice  == 0)
                            subMenuCurrentChoice = MUSHROOM_SUB_CHOICES_NUMBER - 1;
                        else
                            subMenuCurrentChoice--;
                    }

                    else if(c == KEY_DOWN){
                        if(subMenuCurrentChoice == MUSHROOM_SUB_CHOICES_NUMBER - 1)
                            subMenuCurrentChoice = 0;
                        else
                            subMenuCurrentChoice++;
                    }

                    break;

            }//end switch
        }//end else if

        else if(isSubMenuActive && isColorSubMenuActive){
            switch(activeColorSubMenuNumber){
                case 0:
                    if(c == KEY_LEFT){
                        if(colorSubMenuCurrentChoice  == 0)
                            colorSubMenuCurrentChoice = MARIO_CAP_COLOR_NUM - 1;
                        else
                            colorSubMenuCurrentChoice--;
                    }

                    else if(c == KEY_RIGHT){
                        if(colorSubMenuCurrentChoice == MARIO_CAP_COLOR_NUM - 1)
                            colorSubMenuCurrentChoice = 0;
                        else
                            colorSubMenuCurrentChoice++;
                    }

                    break;

                case 1:
                    if(c == KEY_LEFT){
                        if(colorSubMenuCurrentChoice  == 0)
                            colorSubMenuCurrentChoice = MARIO_SHIRT_COLOR_NUM - 1;
                        else
                            colorSubMenuCurrentChoice--;
                    }

                    else if(c == KEY_RIGHT){
                        if(colorSubMenuCurrentChoice == MARIO_SHIRT_COLOR_NUM - 1)
                            colorSubMenuCurrentChoice = 0;
                        else
                            colorSubMenuCurrentChoice++;
                    }

                    break;

                case 2:

                    if(c == KEY_LEFT){
                        if(colorSubMenuCurrentChoice  == 0)
                            colorSubMenuCurrentChoice = MARIO_OP_COLOR_NUM - 1;
                        else
                            colorSubMenuCurrentChoice--;
                    }

                    else if(c == KEY_RIGHT){
                        if(colorSubMenuCurrentChoice == MARIO_OP_COLOR_NUM - 1)
                            colorSubMenuCurrentChoice = 0;
                        else
                            colorSubMenuCurrentChoice++;
                    }

                    break;


                case 3:
                    if(c == KEY_LEFT){
                        if(colorSubMenuCurrentChoice  == 0)
                            colorSubMenuCurrentChoice = TURTLE_SKIN_COLOR_NUM - 1;
                        else
                            colorSubMenuCurrentChoice--;
                    }

                    else if(c == KEY_RIGHT){
                        if(colorSubMenuCurrentChoice == TURTLE_SKIN_COLOR_NUM - 1)
                            colorSubMenuCurrentChoice = 0;
                        else
                            colorSubMenuCurrentChoice++;
                    }

                    break;

            case 4:
                if(c == KEY_LEFT){
                    if(colorSubMenuCurrentChoice  == 0)
                        colorSubMenuCurrentChoice = TURTLE_SHELL_COLOR_NUM - 1;
                    else
                        colorSubMenuCurrentChoice--;
                }

                else if(c == KEY_RIGHT){
                    if(colorSubMenuCurrentChoice == TURTLE_SHELL_COLOR_NUM - 1)
                        colorSubMenuCurrentChoice = 0;
                    else
                        colorSubMenuCurrentChoice++;
                }

                break;

            case 5:
                if(c == KEY_LEFT){
                    if(colorSubMenuCurrentChoice  == 0)
                        colorSubMenuCurrentChoice = PILLAR_BODY_COLOR_NUM - 1;
                    else
                        colorSubMenuCurrentChoice--;
                }

                else if(c == KEY_RIGHT){
                    if(colorSubMenuCurrentChoice == PILLAR_BODY_COLOR_NUM - 1)
                        colorSubMenuCurrentChoice = 0;
                    else
                        colorSubMenuCurrentChoice++;
                }

                break;

            case 6:
                if(c == KEY_LEFT){
                    if(colorSubMenuCurrentChoice  == 0)
                        colorSubMenuCurrentChoice = MUSHROOM_CAP_COLOR_NUM - 1;
                    else
                        colorSubMenuCurrentChoice--;
                }

                else if(c == KEY_RIGHT){
                    if(colorSubMenuCurrentChoice == MUSHROOM_CAP_COLOR_NUM - 1)
                        colorSubMenuCurrentChoice = 0;
                    else
                        colorSubMenuCurrentChoice++;
                }

                break;


            }//end switch
        }// end else if(isSubMenuActive && isColorSubMenuActive)



        //printing setting menu and it's sub menus
        mvwprintw(settingMenuWin, 2, 2, "Press B to Go Back");
        temp = 0;
        for(j = 0; j < SETTING_CHOICES_NUMBER; j++){
            if(j == currentChoice && !isSubMenuActive){
                wattron(settingMenuWin, COLOR_PAIR(1));
                mvwprintw(settingMenuWin, mainChoicesStartingRow + j + (j <= activeSubMenuNumber ? 0 : temp), mainChoicesStartingColumn, "%s", settingMenuChoices[j]);
                wattroff(settingMenuWin, COLOR_PAIR(1));
            }
            else{
                 mvwprintw(settingMenuWin, mainChoicesStartingRow + j + (j <= activeSubMenuNumber ? 0 : temp), mainChoicesStartingColumn, "%s", settingMenuChoices[j]);
            }
            if(isSubMenuActive && j == activeSubMenuNumber){
                switch(activeSubMenuNumber){
                    case 0:
                        for(z = 0; z < MARIO_SUB_CHOICES_NUMBER; z++){
                            if(subMenuCurrentChoice == z){
                                if(!isColorSubMenuActive)
                                    wattron(settingMenuWin, COLOR_PAIR(1));
                                mvwprintw(settingMenuWin, mainChoicesStartingRow + j + z + 1, subChoicesStartingColumn, "%s", marioSubMenuChoices[z]);
                                subColorMenuRow = mainChoicesStartingRow + j + z + 1;
                                if(!isColorSubMenuActive)
                                    wattroff(settingMenuWin, COLOR_PAIR(1));

                            }
                            else{
                                mvwprintw(settingMenuWin, mainChoicesStartingRow + j + z + 1, subChoicesStartingColumn, "%s", marioSubMenuChoices[z]);
                            }
                        }
                        temp = MARIO_SUB_CHOICES_NUMBER;
                        break;

                    case 1:
                        for(z = 0; z < TURTLE_SUB_CHOICES_NUMBER; z++){
                            if(subMenuCurrentChoice == z){
                                if(!isColorSubMenuActive)
                                    wattron(settingMenuWin, COLOR_PAIR(1));
                                mvwprintw(settingMenuWin, mainChoicesStartingRow + j + z + 1, subChoicesStartingColumn, "%s", turtleSubMenuChoices[z]);
                                subColorMenuRow = mainChoicesStartingRow + j + z + 1;
                                if(!isColorSubMenuActive)
                                    wattroff(settingMenuWin, COLOR_PAIR(1));
                            }
                            else{
                                mvwprintw(settingMenuWin, mainChoicesStartingRow + j + z + 1, subChoicesStartingColumn, "%s", turtleSubMenuChoices[z]);
                            }
                        }
                        temp = TURTLE_SUB_CHOICES_NUMBER;
                        break;

                    case 2:
                        for(z = 0; z < PILLAR_SUB_CHOICES_NUMBER; z++){
                            if(subMenuCurrentChoice == z){
                                if(!isColorSubMenuActive)
                                    wattron(settingMenuWin, COLOR_PAIR(1));
                                mvwprintw(settingMenuWin, mainChoicesStartingRow + j + z + 1, subChoicesStartingColumn, "%s", pillarSubMenuChoices[z]);
                                subColorMenuRow = mainChoicesStartingRow + j + z + 1;
                                if(!isColorSubMenuActive)
                                    wattroff(settingMenuWin, COLOR_PAIR(1));
                            }
                            else{
                                mvwprintw(settingMenuWin, mainChoicesStartingRow + j + z + 1, subChoicesStartingColumn, "%s", pillarSubMenuChoices[z]);
                            }
                        }
                        temp = PILLAR_SUB_CHOICES_NUMBER;
                        break;


                    case 3:
                        for(z = 0; z < MUSHROOM_SUB_CHOICES_NUMBER; z++){
                            if(subMenuCurrentChoice == z){
                                if(!isColorSubMenuActive)
                                    wattron(settingMenuWin, COLOR_PAIR(1));
                                mvwprintw(settingMenuWin, mainChoicesStartingRow + j + z + 1, subChoicesStartingColumn, "%s", mushroomSubMenuChoices[z]);
                                subColorMenuRow = mainChoicesStartingRow + j + z + 1;
                                if(!isColorSubMenuActive)
                                    wattroff(settingMenuWin, COLOR_PAIR(1));
                            }
                            else{
                                mvwprintw(settingMenuWin, mainChoicesStartingRow + j + z + 1, subChoicesStartingColumn, "%s", mushroomSubMenuChoices[z]);
                            }
                        }
                        temp = MUSHROOM_SUB_CHOICES_NUMBER;
                        break;
                }//end swith
            }//end if(!isSubMenuActive)


            if(isColorSubMenuActive && j == activeSubMenuNumber){
                switch(activeColorSubMenuNumber){
                    case 0:
                        for(k = 0; k < MARIO_CAP_COLOR_NUM; k++){
                           if(colorSubMenuCurrentChoice == k){
                                wattron(settingMenuWin, COLOR_PAIR(1));
                                mvwprintw(settingMenuWin, subColorMenuRow , subChoicesStartingColumn + 31 + k * 7, "%s", marioCapColorSubMenu[k]);
                                wattroff(settingMenuWin, COLOR_PAIR(1));
                           }

                           else{
                               mvwprintw(settingMenuWin, subColorMenuRow , subChoicesStartingColumn + 31 + k * 7, "%s", marioCapColorSubMenu[k]);
                           }
                        }


                        break;

                    case 1:
                        for(k = 0; k < MARIO_SHIRT_COLOR_NUM; k++){
                            if(colorSubMenuCurrentChoice == k){
                                wattron(settingMenuWin, COLOR_PAIR(1));
                                mvwprintw(settingMenuWin, subColorMenuRow  , subChoicesStartingColumn + 31 + k * 7, "%s", marioShirtColorSubMenu[k]);
                                wattroff(settingMenuWin, COLOR_PAIR(1));
                            }

                            else{
                                mvwprintw(settingMenuWin, subColorMenuRow, subChoicesStartingColumn + 31 + k * 7, "%s", marioShirtColorSubMenu[k]);
                            }
                        }

                        break;

                    case 2:
                        for(k = 0; k < MARIO_OP_COLOR_NUM; k++){
                            if(colorSubMenuCurrentChoice == k){
                                wattron(settingMenuWin, COLOR_PAIR(1));
                                mvwprintw(settingMenuWin, subColorMenuRow , subChoicesStartingColumn + 31 + k * 7, "%s", marioOPColorSubMenu[k]);
                                wattroff(settingMenuWin, COLOR_PAIR(1));
                            }

                            else{
                                mvwprintw(settingMenuWin, subColorMenuRow , subChoicesStartingColumn + 31 + k * 7, "%s", marioOPColorSubMenu[k]);
                            }
                        }

                        break;


                    case 3:
                        for(k = 0; k < TURTLE_SKIN_COLOR_NUM; k++){
                            if(colorSubMenuCurrentChoice == k){
                                wattron(settingMenuWin, COLOR_PAIR(1));
                                mvwprintw(settingMenuWin, subColorMenuRow , subChoicesStartingColumn + 31 + k * 7, "%s", turtleSkinColorSubMenu[k]);
                                wattroff(settingMenuWin, COLOR_PAIR(1));

                            }

                            else{
                                mvwprintw(settingMenuWin, subColorMenuRow , subChoicesStartingColumn + 31 + k * 7, "%s",turtleSkinColorSubMenu[k]);
                            }
                        }

                        break;

                    case 4:
                        for(k = 0; k < TURTLE_SHELL_COLOR_NUM; k++){
                            if(colorSubMenuCurrentChoice == k){
                                wattron(settingMenuWin, COLOR_PAIR(1));
                                mvwprintw(settingMenuWin, subColorMenuRow , subChoicesStartingColumn + 31 + k * 7, "%s", turtleShellColorSubMenu[k]);
                                wattroff(settingMenuWin, COLOR_PAIR(1));
                            }

                            else{
                                mvwprintw(settingMenuWin, subColorMenuRow , subChoicesStartingColumn + 31 + k * 7, "%s",turtleShellColorSubMenu[k]);
                            }
                        }

                        break;

                    case 5:
                        for(k = 0; k < PILLAR_BODY_COLOR_NUM; k++){
                            if(colorSubMenuCurrentChoice == k){
                                wattron(settingMenuWin, COLOR_PAIR(1));
                                mvwprintw(settingMenuWin, subColorMenuRow , subChoicesStartingColumn + 31 + k * 7, "%s", pillarBodyColorSubMenu[k]);
                                wattroff(settingMenuWin, COLOR_PAIR(1));
                            }

                            else{
                                mvwprintw(settingMenuWin, subColorMenuRow , subChoicesStartingColumn + 31 + k * 7, "%s",pillarBodyColorSubMenu[k]);
                            }
                        }

                        break;

                    case 6:
                        for(k = 0; k < MUSHROOM_CAP_COLOR_NUM; k++){
                            if(colorSubMenuCurrentChoice == k){
                                wattron(settingMenuWin, COLOR_PAIR(1));
                                mvwprintw(settingMenuWin, subColorMenuRow , subChoicesStartingColumn + 31 + k * 7, "%s", mushroomCapColorSubMenu[k]);
                                wattroff(settingMenuWin, COLOR_PAIR(1));
                            }

                            else{
                                mvwprintw(settingMenuWin, subColorMenuRow , subChoicesStartingColumn + 31 + k * 7, "%s",mushroomCapColorSubMenu[k]);
                            }
                        }
                        break;

                }

            }

        }//end outer for(j = 0...)


		wrefresh(settingMenuWin);
		

        if ((c == 'b' || c == 'B' ) && !isSubMenuActive && !isColorSubMenuActive){
			wclear(settingMenuWin);
            wrefresh(settingMenuWin);
			delwin(settingMenuWin);
            return;
		}		

        else if((c == 'b' || c == 'B' ) && isSubMenuActive && !isColorSubMenuActive){
            wclear(settingMenuWin);
            isSubMenuActive = false;
            activeSubMenuNumber = -1;
            subMenuCurrentChoice = 0;
            if(i == 0){
                wborder(settingMenuWin,'*','*','*','*','*','*','*','*');
            }
            else{
                wborder(settingMenuWin,'$','$','$','$','$','$','$','$');
            }
        }

        else if((c == 'b' || c == 'B' )&& isSubMenuActive && isColorSubMenuActive){
            wclear(settingMenuWin);
            isColorSubMenuActive = false;
            activeColorSubMenuNumber = -1;
            colorSubMenuCurrentChoice = 0;
            if(i == 0){
                wborder(settingMenuWin,'*','*','*','*','*','*','*','*');
            }
            else{
                wborder(settingMenuWin,'$','$','$','$','$','$','$','$');
            }

        }

        if(c == '\n' && !isSubMenuActive && !isColorSubMenuActive){
            wclear(settingMenuWin);
            isSubMenuActive = true;
            activeSubMenuNumber = currentChoice;
            if(i == 0){
                wborder(settingMenuWin,'*','*','*','*','*','*','*','*');
            }
            else{
                wborder(settingMenuWin,'$','$','$','$','$','$','$','$');
            }
        }

        else if(c == '\n' && isSubMenuActive && !isColorSubMenuActive){
            wclear(settingMenuWin);
            isColorSubMenuActive = true;
            activeColorSubMenuNumber = subMenuCurrentChoice + (currentChoice >= 1 ? MARIO_SUB_CHOICES_NUMBER : 0) + (currentChoice >=2 ? TURTLE_SUB_CHOICES_NUMBER : 0) + (currentChoice >= 3 ? PILLAR_SUB_CHOICES_NUMBER : 0) ;
            if(i == 0){
                wborder(settingMenuWin,'*','*','*','*','*','*','*','*');
            }
            else{
                wborder(settingMenuWin,'$','$','$','$','$','$','$','$');
            }
        }


        else if(c == '\n' && isSubMenuActive && isColorSubMenuActive){
            switch(activeColorSubMenuNumber){
                case 0:
                    if(colorSubMenuCurrentChoice == 0){
                        init_pair(MARIO_HAT_COLOR, COLOR_RED, COLOR_RED);
                    }

                    else if(colorSubMenuCurrentChoice == 1){
                        init_pair(MARIO_HAT_COLOR, COLOR_GREEN, COLOR_GREEN);
                    }

                    break;

                case 1:
                    if(colorSubMenuCurrentChoice == 0){
                        init_pair(MARIO_SHIRT_COLOR, COLOR_BLUE, COLOR_BLUE);
                    }

                    else if(colorSubMenuCurrentChoice == 1){
                        init_pair(MARIO_SHIRT_COLOR, COLOR_WHITE, COLOR_WHITE);
                    }

                    break;

                case 2:
                    if(colorSubMenuCurrentChoice == 0){
                        init_pair(MARIO_ONE_PIEACE_COLOR, COLOR_BLUE, COLOR_BLUE);
                    }

                    else if(colorSubMenuCurrentChoice == 1){
                        init_pair(MARIO_ONE_PIEACE_COLOR, COLOR_YELLOW, COLOR_YELLOW);
                    }
                    break;


                case 3:
                    if(colorSubMenuCurrentChoice == 0){
                        init_pair(TURTLE_SKIN_COLOR, COLOR_WHITE, COLOR_WHITE);
                    }

                    else if(colorSubMenuCurrentChoice == 1){
                        init_pair(TURTLE_SKIN_COLOR, COLOR_YELLOW, COLOR_YELLOW);
                    }

                    break;

                case 4:
                    if(colorSubMenuCurrentChoice == 0){
                        init_pair(TURTLE_SHELL_COLOR, COLOR_GREEN, COLOR_GREEN);
                    }

                    else if(colorSubMenuCurrentChoice == 1){
                        init_pair(TURTLE_SHELL_COLOR, COLOR_BLUE, COLOR_BLUE);
                    }

                    break;

                case 5:
                    if(colorSubMenuCurrentChoice == 0){
                        init_pair(PILLAR_BODY_COLOR, COLOR_GREEN, COLOR_GREEN);
                    }

                    else if(colorSubMenuCurrentChoice == 1){
                        init_pair(PILLAR_BODY_COLOR, COLOR_BLUE, COLOR_BLUE);
                    }

                    break;

                case 6:
                    if(colorSubMenuCurrentChoice == 0){
                        init_pair(MUSHROOM_CAP_COLOR, COLOR_GREEN, COLOR_GREEN);
                    }

                    else if(colorSubMenuCurrentChoice == 1){
                        init_pair(MUSHROOM_CAP_COLOR, COLOR_RED, COLOR_RED);
                    }

                    break;
            }

        }
    }

}


