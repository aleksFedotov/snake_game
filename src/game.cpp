#include "game.hpp"
#include <iostream>

Game::Game(int cellSize, int cellCount)
{
    this -> cellSize = cellSize;
    this -> cellCount = cellCount;
    snake.setCellSize(cellSize);
    food.SetCellSize(cellSize);
    food.SetCellCount(cellCount);
    food.Spawn();
   
}

void Game::Draw()
{
    snake.Draw();
    food.Draw();
}

void Game::Update()
{

    snake.Update();
    CheckCollisionWithFood();
}

void Game::HandleInput()
{
    if(IsKeyPressed(KEY_UP) && snake.isNotMovingDown()) 
    {
        snake.MoveUp();
    }
    else if(IsKeyPressed(KEY_DOWN) && snake.isNotMovingUp())
    {
        snake.MoveDown();
    }
    else if(IsKeyPressed(KEY_RIGHT) && snake.isNotMovingLeft())
    {
        snake.MoveRight();
    }
    else if(IsKeyPressed(KEY_LEFT) && snake.isNotMovingRight())
    {
        snake.MoveLeft();
    }
}

void Game::CheckCollisionWithFood()
{
    if(Vector2Equals(snake.body[0], food.position))
    {   
        Vector2 newPosition = food.Spawn();
        while (IsFoodInSnake(newPosition, snake.body))
        {
            newPosition = food.Spawn();
        }
        snake.addSegment = true;
        
         
         
    }
}

bool Game::IsFoodInSnake(Vector2 foodPosition, std::deque<Vector2> snakeBody)
{
    for (unsigned int i = 0; i < snakeBody.size(); i++)
    {
        if(Vector2Equals(foodPosition, snakeBody[i]))
        {
            return true;
        }
    }
    
    return false;
}
