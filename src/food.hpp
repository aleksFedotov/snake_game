#pragma once
#include <raylib.h>


class Food
{
private:
    int cellSize;
    int cellCount;
    Image image;
public:
    Food(int cellSize, int cellCount);
    ~Food();
    Vector2 position;
    Texture2D texture;
    void Draw();
    Vector2 GenerateRandomPosition();
    
};

