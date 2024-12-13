#pragma once
#include <deque>
#include <raylib.h>
#include "snake.hpp"
#include "food.hpp"


class Game
{
public:
    Game(int cellSize, int cellCount,int offset);
    ~Game();
    bool running;
    int score;
    void Draw();
    void Update();
    void HandleInput();
    void GameOver();
    Sound eatSound;
    Sound wallSound;
   
    
private:
    int cellSize;
    int cellCount;
    int offset;
    Snake snake = Snake();
    Food food = Food();
    void CheckCollisionWithFood();
    void CheckCollisionsWithEdges();
    void CheckCollisionsWithTail();
    bool ElementInDeque(Vector2 foodPosition, std::deque<Vector2> snakeBody);
    void GenerateNewFoodPosition();
    void Reset();

   
};

