#pragma once
#include <raylib.h>


class Food
{
private:
    int cellSize;
    int cellCount;
    int offset;
    Image image;
public:
    Food();
    ~Food();
    Vector2 position;
    Texture2D texture;
    void Draw();
    void SetCellSize(int cellSize);
    void SetCellCount(int cellCount);
    void SetOffset(int offset);
    void Initialize(int cellSize, int cellCount, int offset);
    Vector2 Spawn();
    Vector2 GenerateRandomPosition();
    
};

