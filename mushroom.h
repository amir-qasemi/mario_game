#ifndef MUSHROOM
#define MUSHROOM

#define MUSHROOM_GROUND_ROW 56
#define MUSHROOM_WIDTH 9
#define MUSHROOM_HEIGHT 8


class Mushroom{
public:
    Mushroom(int);

    int getRow();
    int getColumn();
    int getWidth();
    int getHeight();
    int getOneOfMushroomShapeChars(int i, int j);

    void drawMushroom(int, int);
    void cleanShape(int ,int );

private:
    void setMushroomShape();

    int mushroomShape[MUSHROOM_HEIGHT][MUSHROOM_WIDTH];
    static int row;
    static int width;
    int column;
    static int height;
};

#endif // MUSHROOM

