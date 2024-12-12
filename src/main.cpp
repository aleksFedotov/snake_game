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
    int cellSize = 30;
    int cellCount = 25;

    const int screenWidth  = cellSize * cellCount;
    const int screenHeight = cellSize * cellCount;
    int fps = 60;

    InitWindow(screenWidth,screenHeight, "Snake Game");
    SetTargetFPS(fps);


    Game game = Game(cellSize,cellCount);
;
    while(!WindowShouldClose())
    {   
        BeginDrawing();
        game.HandleInput();
        if(EventTriggered(0.2))
        {
            game.Update();
        }

    
        ClearBackground(green);
        game.Draw();
     

        EndDrawing();
    }

    CloseWindow();

}