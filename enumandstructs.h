#ifndef ENUMANDSTRUCTS
#define ENUMANDSTRUCTS

#define MAX_ITEM_NUM 50
#define MAX_PILLAR_NUM 5
#define MAX_MUSHROOM_NUMBER 5
#define MAX_TURTLE_NUMBER 5
#define MAX_CLOUD_NUMBER 5
#define GROUND_ROW 56
#define DELAY 20000


//COLOR PAIRS, the first letter is foreground color, the second one is background
// BLACK    B //
// RED      R //
// GREEN    G //
// YELLOW   Y //
// BLUE     X //
// MAGENTA  M //
// CYAN     C //
// WHITE    W //

enum CK{
    BW = 1, RR, YY, XX, GG, BB, WW, MM, CC, WC, WR, MARIO_HAT_COLOR, MARIO_ONE_PIEACE_COLOR, MARIO_SHIRT_COLOR,
    TURTLE_SKIN_COLOR, TURTLE_SHELL_COLOR, PILLAR_BODY_COLOR, MUSHROOM_CAP_COLOR
};




enum direction{
    LEFT, RIGHT, UP, DOWN
};

struct itemCol{
    int Columns[MAX_ITEM_NUM];
};



enum gameStatus{
    WON, CONTINUE, LOST
};


#endif // ENUMANDSTRUCTS

