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
    int xPos = offset + position.x * cellSize;
    int yPos = offset + position.y * cellSize;
    DrawTexture(texture, xPos, yPos, WHITE);
    
}

void Food::Initialize(int cellSize, int cellCount, int offset)
{
    this->cellSize = cellSize;
    this->cellCount = cellCount;
    this->offset = offset;
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
