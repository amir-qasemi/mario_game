#ifndef MENU
#define MENU


#define CHOICES_NUMBER 5
#define SETTING_CHOICES_NUMBER 4
#define MARIO_SUB_CHOICES_NUMBER 3
#define TURTLE_SUB_CHOICES_NUMBER 2
#define PILLAR_SUB_CHOICES_NUMBER 1
#define MUSHROOM_SUB_CHOICES_NUMBER 1
#define MARIO_CAP_COLOR_NUM 2
#define MARIO_SHIRT_COLOR_NUM 2
#define MARIO_OP_COLOR_NUM 2
#define TURTLE_SKIN_COLOR_NUM 2
#define TURTLE_SHELL_COLOR_NUM 2
#define PILLAR_BODY_COLOR_NUM 2
#define MUSHROOM_CAP_COLOR_NUM 2
 


class Menu{
public:
	int bringMainMenu(const int);
private:
    void bringSettingMenu(const int);

};





#endif //MENU
