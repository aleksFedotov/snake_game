#include <raylib.h>
#include "colors.hpp"
#include "food.hpp"
#include "snake.hpp"
#include "game.hpp"

// Global variable to track the time of the last update.
double lastUpdateTime = 0;

// Function to determine if an event should be triggered based on the interval.
bool EventTriggered(double interval) 
{
   double currentTime = GetTime();  // Get the current time.
   if(currentTime - lastUpdateTime >= interval)  // Check if the interval has passed.
   {
      lastUpdateTime = currentTime;  // Update the last update time.
      return true;  // Event triggered.
   }
   return false;  // Event not triggered.
}

int main() 
{
    // Constants for game configuration.
    constexpr float UPDATE_INTERVAL = 0.2f; // Interval for game updates.
    constexpr int DEFAULT_CELL_SIZE = 30; // Size of each cell in the grid.
    constexpr int DEFAULT_CELL_COUNT  = 25; // Number of cells in one row/column.
    constexpr int DEFAULT_OFFSET = 75; // Offset for the game grid from the window borders.

    // Calculate the screen dimensions based on grid size and offset.
    const int screenWidth  = 2 * DEFAULT_OFFSET + DEFAULT_CELL_SIZE * DEFAULT_CELL_COUNT;
    const int screenHeight = 2 * DEFAULT_OFFSET + DEFAULT_CELL_SIZE * DEFAULT_CELL_COUNT;
    int fps = 60; // Set the frame rate of the game.

    InitWindow(screenWidth, screenHeight, "Snake Game"); // Initialize the game window.
    SetTargetFPS(fps); // Set the target frames per second.

    // Initialize the game with the specified cell size, count, and offset.
    Game game = Game(DEFAULT_CELL_SIZE, DEFAULT_CELL_COUNT, DEFAULT_OFFSET);

    while(!WindowShouldClose()) // Main game loop, runs until the window should close.
    {   
        BeginDrawing(); // Begin drawing the current frame.

        // Handle player input.
        game.HandleInput();

        // Update the game state at regular intervals.
        if(EventTriggered(UPDATE_INTERVAL))
        {
            game.Update();
        }

        // Clear the background with the green color.
        ClearBackground(green);

        // Draw the game border.
        DrawRectangleLinesEx(
            Rectangle{(float)DEFAULT_OFFSET - 5, (float)DEFAULT_OFFSET - 5, 
                      (float)DEFAULT_CELL_SIZE * DEFAULT_CELL_COUNT + 10, 
                      (float)DEFAULT_CELL_SIZE * DEFAULT_CELL_COUNT + 10},
            5, darkGreen);

        // Display the game title.
        DrawText("Retro Snake", DEFAULT_OFFSET - 5, 20, 40, darkGreen);

        // Display the current score below the game grid.
        DrawText(TextFormat("%i", game.score), 
                 DEFAULT_OFFSET - 5, 
                 DEFAULT_OFFSET + DEFAULT_CELL_SIZE * DEFAULT_CELL_COUNT + 10, 
                 40, darkGreen);

        // Draw the game objects (snake, food, etc.).
        game.Draw();

        EndDrawing(); // End drawing the current frame.
    }

    CloseWindow(); // Close the game window and clean up resources.

}
