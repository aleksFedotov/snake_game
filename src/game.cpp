#include "game.hpp"
#include <iostream>

Game::Game(int cellSize, int cellCount, int offset)
{
    this -> cellSize = cellSize;
    this -> cellCount = cellCount;
    this -> offset = offset;
    snake.setCellSize(cellSize);
    snake.setOffset(offset);
    food.SetCellSize(cellSize);
    food.SetCellCount(cellCount);
    food.SetOffset(offset);
    food.Spawn();
    running = true;
    score = 0;
    InitAudioDevice();
    eatSound = LoadSound("Sounds/eat.mp3");
    wallSound = LoadSound("Sounds/wall.mp3");
   
}

Game::~Game()
{
    UnloadSound(eatSound);
    UnloadSound(wallSound);
}

void Game::Draw()
{
    snake.Draw();
    food.Draw();
}

void Game::Update()
{
    if(running)
    {
        snake.Update();
        CheckCollisionWithFood();
        CheckCollisionsWithEdges();
        CheckCollisionsWithTail();

    }
}

void Game::HandleInput()
{
    if(IsKeyPressed(KEY_UP) && snake.isNotMovingDown()) 
    {
        snake.MoveUp();
        running = true;
    }
    else if(IsKeyPressed(KEY_DOWN) && snake.isNotMovingUp())
    {
        snake.MoveDown();
        running = true;

    }
    else if(IsKeyPressed(KEY_RIGHT) && snake.isNotMovingLeft())
    {
        snake.MoveRight();
        running = true;

    }
    else if(IsKeyPressed(KEY_LEFT) && snake.isNotMovingRight())
    {
        snake.MoveLeft();
        running = true;

    }
    else if (IsKeyPressed(KEY_ENTER))
    {
        running = !running;
    }
    
}

void Game::GameOver()
{
    snake.Reset();
    GenerateNewFoodPosition();
    running = false;
    score = 0;
    PlaySound(wallSound);
}



void Game::CheckCollisionWithFood()
{
    if(Vector2Equals(snake.body[0], food.position))
    {   
        GenerateNewFoodPosition();
        snake.addSegment = true;
        PlaySound(eatSound);
        score++;
    }
}

void Game::CheckCollisionsWithEdges()
{
    if(snake.head.x == cellCount || snake.head.x == -1)
    {
        GameOver();
        
    }
    if(snake.head.y == cellCount || snake.head.y == -1)
    {
        GameOver();
        

    }
}

void Game::CheckCollisionsWithTail()
{
    std::deque<Vector2> headlessBody = snake.body;
    headlessBody.pop_front();
    if(ElementInDeque(snake.head, headlessBody))
    {
        GameOver();
    }
}

bool Game::ElementInDeque(Vector2 element, std::deque<Vector2> deque)
{
    for (unsigned int i = 0; i < deque.size(); i++)
    {
        if(Vector2Equals(element, deque[i]))
        {
            return true;
        }
    }
    
    return false;
}

void Game::GenerateNewFoodPosition()
{   
    Vector2 newPosition = food.Spawn();
        while (ElementInDeque(newPosition, snake.body))
        {
            newPosition = food.Spawn();
        }
       
   
}
