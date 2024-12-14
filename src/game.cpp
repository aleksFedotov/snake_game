#include "game.hpp"
#include <iostream>

// Constructor for initializing the game with cell size, count, and offset.
Game::Game(int cellSize, int cellCount, int offset)
{
    // Set the properties for the game grid
    this->cellSize = cellSize;
    this->cellCount = cellCount;
    this->offset = offset;

    // Initialize snake and food objects
    snake.Initialize(cellSize, offset);
    food.Initialize(cellSize, cellCount, offset);
    
    // Spawn food at the beginning of the game
    food.Spawn();
    
    // Set the game to be running and score to 0
    running = true;
    score = 0;

    // Initialize audio device and load sound files
    InitAudioDevice();
    eatSound = LoadSound("Sounds/eat.mp3");
    wallSound = LoadSound("Sounds/wall.mp3");
}

// Destructor to unload the sound resources when the game ends
Game::~Game()
{
    UnloadSound(eatSound);
    UnloadSound(wallSound);
}

// Method to draw the snake and food on the screen
void Game::Draw()
{
    snake.Draw();  // Draw the snake
    food.Draw();   // Draw the food
}

// Update the game logic, including snake movement and collision checks
void Game::Update()
{
    if(running)
    {
        // Update the snake's position
        snake.Update();
        
        // Check for collisions with food, edges, and the snake's tail
        CheckCollisionWithFood();
        CheckCollisionsWithEdges();
        CheckCollisionsWithTail();
    }
}

// Handle user input for controlling the snake
void Game::HandleInput()
{
    // Change snake's direction based on arrow key input
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
    // Toggle the running state when the Enter key is pressed
    else if (IsKeyPressed(KEY_ENTER))
    {
        running = !running;
    }
}

// Handle the game-over state when the snake hits a wall or itself
void Game::GameOver()
{
    // Play the wall hit sound
    PlaySound(wallSound);
    
    // Reset the game state
    Reset();
}

// Check if the snake's head collides with food and handle the collision
void Game::CheckCollisionWithFood()
{
    // If the snake's head is at the same position as the food
    if(Vector2Equals(snake.body[0], food.position))
    {   
        // Generate a new food position and grow the snake
        GenerateNewFoodPosition();
        snake.Grow();
        
        // Play the eating sound and increment score
        PlaySound(eatSound);
        score++;
    }
}

// Check if the snake collides with the edges of the game grid
void Game::CheckCollisionsWithEdges()
{
    // If the snake is out of bounds, game over
    if (snake.IsOutOfBounds(cellCount)) {
        GameOver();
    }
}

// Check if the snake's head collides with its own body (self-collision)
void Game::CheckCollisionsWithTail()
{
    // Create a copy of the snake's body (excluding the head)
    std::deque<Vector2> headlessBody = snake.body;
    headlessBody.pop_front();  // Remove the head from the body
    
    // If the snake's head is in its own body, game over
    if(ElementInDeque(snake.head, headlessBody))
    {
        GameOver();
    }
}

// Helper function to check if a specific element exists in a deque (used for collision checks)
bool Game::ElementInDeque(Vector2 element, std::deque<Vector2> deque)
{
    for (unsigned int i = 0; i < deque.size(); i++)
    {
        // If the element matches any element in the deque, return true
        if(Vector2Equals(element, deque[i]))
        {
            return true;
        }
    }
    
    // Return false if no match is found
    return false;
}

// Generate a new random position for the food, ensuring it doesn't overlap with the snake
void Game::GenerateNewFoodPosition()
{   
    Vector2 newPosition;
    int attempts = 0;
    
    // Try generating a new food position, ensuring it doesn't overlap with the snake
    do {
        newPosition = food.Spawn();
        attempts++;
        
        // If we can't place the food after a certain number of attempts, log a warning
        if (attempts > cellCount * cellCount) {
            TraceLog(LOG_WARNING, "Failed to place food after maximum attempts.");
            return;
        }
    } while (ElementInDeque(newPosition, snake.body));  // Ensure no collision with snake body
}

// Reset the game to its initial state
void Game::Reset()
{
    // Reset snake and food position, and set score to 0
    snake.Reset();
    GenerateNewFoodPosition();
    score = 0;
    
    // Set the game to paused state
    running = false;
}
