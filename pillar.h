#ifndef PILLAR
#define PILLAR

#define PILLAR_ROW 56
#define PILLAR_WIDTH 15

class Pillar{
public:
    Pillar(int, int);

    int getRow();
    int getColumn();
    int getWidth();
    int getHeight();

    void drawPillar(int, int);
	void cleanPillar(int ,int );

    
    
    
private:
    static int row;
    static int width;
    int column;
    int height;
};

#endif // PILLAR

