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
    constexpr float UPDATE_INTERVAL = 0.2f;
    constexpr int DEFAULT_CELL_SIZE = 30;
    constexpr int DEFAULT_CELL_COUNT  = 25;
    constexpr int DEFAULT_OFFSET = 75;

    const int screenWidth  = 2*DEFAULT_OFFSET + DEFAULT_CELL_SIZE * DEFAULT_CELL_COUNT;
    const int screenHeight = 2*DEFAULT_OFFSET + DEFAULT_CELL_SIZE * DEFAULT_CELL_COUNT;
    int fps = 60;

    InitWindow(screenWidth,screenHeight, "Snake Game");
    SetTargetFPS(fps);


    Game game = Game(DEFAULT_CELL_SIZE,DEFAULT_CELL_COUNT,DEFAULT_OFFSET);
;
    while(!WindowShouldClose())
    {   
        BeginDrawing();
        game.HandleInput();
        if(EventTriggered(UPDATE_INTERVAL))
        {
            game.Update();
        }

    
        ClearBackground(green);
        DrawRectangleLinesEx(Rectangle{(float)DEFAULT_OFFSET-5, (float)DEFAULT_OFFSET - 5, (float)DEFAULT_CELL_SIZE*DEFAULT_CELL_COUNT +10,(float)DEFAULT_CELL_SIZE*DEFAULT_CELL_COUNT +10}, 5, darkGreen);
        DrawText("Retro Snake", DEFAULT_OFFSET - 5, 20, 40, darkGreen);
        DrawText(TextFormat("%i", game.score), DEFAULT_OFFSET - 5, DEFAULT_OFFSET + DEFAULT_CELL_SIZE * DEFAULT_CELL_COUNT + 10, 40, darkGreen);
        game.Draw();
     

        EndDrawing();
    }

    CloseWindow();

}