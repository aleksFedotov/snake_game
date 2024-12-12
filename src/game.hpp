#pragma once
#include <deque>
#include <raylib.h>
#include "snake.hpp"
#include "food.hpp"


class Game
{
public:
    Game(int cellSize, int cellCount);
    void Draw();
    void Update();
    void HandleInput();
    
private:
    int cellSize;
    int cellCount;
    Snake snake = Snake();
    Food food = Food();
    void CheckCollisionWithFood();
    bool IsFoodInSnake(Vector2 foodPosition, std::deque<Vector2> snakeBody);

   
};

