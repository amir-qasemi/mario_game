#ifndef TURTLE
#define TURTLE

#include "enumandstructs.h"

#define TURTLE_HEIGHT 13
#define TURTLE_WIDTH 16
#define TURTLE_SHAPE_NUMBER 3

#define TURTLE_ONE 0
#define TURTLE_TWO 1
#define TURTLE_IN_SHELL 2


class Turtle{
public:
    Turtle(int, int);

    void increaseColumn();
    void decreaseColumn();
    void increaseMovementCounter();

    void changeDirection();


    int getRow();
    int getColumn();
    int getHeight();
    int getWidth();
    int getShapeID();
    int getMovementCounter();
    int getBeginningColumn();

    void drawShape(int, int);
    void cleanShape(int, int);
    void changeShapeID(int i);
    void moveOneStep();
    void increaseInShellCounter();
    bool isInShell();
    void SetInShellStatus(bool);
    int getOneOfTurtleShapeChars(int , int);


private:
    void setShape();
    
    int column, row;
    int beginningColumn, endingColumn;
    static int height, width;
    int shapeID;
    unsigned turtleMovementCounter;
    int turtleShape[TURTLE_SHAPE_NUMBER][TURTLE_HEIGHT][TURTLE_WIDTH];
    enum direction turtleDirection;
    bool inShell;
    int inShellCounter;


};


#endif //TURTLE
