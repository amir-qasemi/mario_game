#ifndef CASTLE
#define CASTLE

#define CASTLE_HEIGHT 23
#define CASTLE_WIDTH 26
#define GROUND_ROW 56

class Castle{
public:
    Castle(int);
    void draw(int, int);
    int getColumn();
    int getWidth();
    void clean(int, int);

private:
    void setShape();

    int shape[CASTLE_HEIGHT][CASTLE_WIDTH];
    int column, row, height, width;
};


#endif // CASTLE

