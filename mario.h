#ifndef MARIO
#define MARIO

#include "enumandstructs.h"
#include "pillar.h"
#include "mushroom.h"
#include "turtle.h"
//#include "mymariolibrary.h"


#define MARIO_SHAPE_NUMBER 4
#define MARIO_HEIGHT 16
#define MARIO_WIDTH 13

#define MARIO_STANDING 0
#define MARIO_RUNNING_ONE 1
#define MARIO_RUNNING_TWO 2
#define MARIO_JUMPING 3


class Mario{
public:
    Mario(int, int);

    void increseColumn();
    void decreaseColoumn();
    void increaseRow();
    void decreaseRow();
	void increaseScore();
	void decreaseScore();

    int getRow();
    int getColumn();
    int getShapID();
	int getMovingMarioShapeCounter();
	int getScore();
	bool getOnHigherSurface();


    void setShapeID(int, int , int );
	void increaseMovingMarioShapeCounter();
	void zeroMovingMarioShapeCounter();

    void changeDir(int);
	void changeOnHigherSurfaceStatus();


    void drawShape(int, int);
    void cleanShape(int, int);


	bool authorizeMovement(enum direction, class Pillar *myPillar[MAX_PILLAR_NUM]);
	void checkOnHigherSurface(class Pillar *myPillar[MAX_PILLAR_NUM], int groundRow);
	void pushMario(class Pillar *myPillar[MAX_PILLAR_NUM]);
    void checkColliding(class Mushroom *myMushroom[MAX_MUSHROOM_NUMBER], struct itemCol *, int, Turtle *myTurtle[], unsigned &);

private:
    //utility functions
    void setRow(int);
    void setColumn(int);
    void setMarioShape(void);
	void deleteColOfStruct(struct itemCol *mushroomCol, int deletingCol);

    //variables
    int row;
    int column;
    int marioShape[MARIO_SHAPE_NUMBER][MARIO_HEIGHT][MARIO_WIDTH];
    int shapeID;
	int movingMarioShapeCounter;
	unsigned score;
	bool onHigherSurface;
    enum direction marioDirection;


};



#endif // MARIO

