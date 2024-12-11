#include "food.hpp"
#include "colors.hpp"

Food::Food(int cellSize, int cellCount)
{
    this-> cellSize = cellSize;
    this-> cellCount = cellCount;
    position = GenerateRandomPosition();
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

Vector2 Food::GenerateRandomPosition()
{
    float x = GetRandomValue(0, cellCount -1);
    float y = GetRandomValue(0, cellCount -1);

    return Vector2{x,y};
}
