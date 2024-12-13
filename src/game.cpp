#include "game.hpp"
#include <iostream>

Game::Game(int cellSize, int cellCount, int offset)
{
    this -> cellSize = cellSize;
    this -> cellCount = cellCount;
    this -> offset = offset;
    snake.Initialize(cellSize,offset);
    food.Initialize(cellSize, cellCount,offset);
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
        snake.SetDirection({0, -1});
        running = true;
    }
    else if(IsKeyPressed(KEY_DOWN) && snake.isNotMovingUp())
    {
        snake.SetDirection({0, 1});
        running = true;

    }
    else if(IsKeyPressed(KEY_RIGHT) && snake.isNotMovingLeft())
    {
        snake.SetDirection({1, 0});
        running = true;

    }
    else if(IsKeyPressed(KEY_LEFT) && snake.isNotMovingRight())
    {
        snake.SetDirection({-1, 0});
        running = true;

    }
    else if (IsKeyPressed(KEY_ENTER))
    {
        running = !running;
    }
    
}

void Game::GameOver()
{
    
    PlaySound(wallSound);
    Reset();
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
     if (snake.IsOutOfBounds(cellCount)) {
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
    Vector2 newPosition;
    int attempts = 0;
    do {
        newPosition = food.Spawn();
        attempts++;
        if (attempts > cellCount * cellCount) {
            TraceLog(LOG_WARNING, "Failed to place food after maximum attempts.");
            return;
        }
    } while (ElementInDeque(newPosition, snake.body));
   
}


void Game::Reset()
{
    snake.Reset();
    GenerateNewFoodPosition();
    score = 0;
    running = false;
}