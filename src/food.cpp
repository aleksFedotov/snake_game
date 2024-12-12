#include "food.hpp"
#include "colors.hpp"

Food::Food()
{
    image = LoadImage("Graphics/food.png");
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
}

Food::~Food()
{
    UnloadTexture(texture);
}

void Food::Draw()
{
    DrawTexture(texture,position.x * cellSize, position.y * cellSize, WHITE);
    
}

void Food::SetCellSize(int cellSize)
{
    this-> cellSize = cellSize;
}

void Food::SetCellCount(int cellCount)
{
    this -> cellCount = cellCount;
}

Vector2 Food::Spawn()
{
    position = GenerateRandomPosition();
    return position;
}

Vector2 Food::GenerateRandomPosition()
{
    float x = GetRandomValue(0, cellCount -1);
    float y = GetRandomValue(0, cellCount -1);

    return Vector2{x,y};
}
