#ifndef CLOUD
#define CLOUD

#define CLOUD_HEIGHT 13
#define CLOUD_WIDTH 18

class Cloud{
public:
    Cloud(int, int);

    int getRow();
    int getColumn();
    int getWidth();
    int getHeight();

    void drawShape(int, int);
    void cleanShape(int ,int );




private:
    void setCloudShape();

    int cloudShape[CLOUD_HEIGHT][CLOUD_WIDTH];
    static int height;
    static int width;
    int row;
    int column;
};



#endif //CLOUD
