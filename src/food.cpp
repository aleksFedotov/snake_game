#include "food.hpp"
#include "colors.hpp"

// Constructor to load the food texture image
Food::Food()
{
    // Load the food image and convert it to a texture
    image = LoadImage("Graphics/food.png");
    texture = LoadTextureFromImage(image);
    
    // Unload the image as it's no longer needed after being converted to a texture
    UnloadImage(image);
}

// Destructor to unload the texture when the food object is destroyed
Food::~Food()
{
    UnloadTexture(texture);
}

// Method to draw the food at its current position on the screen
void Food::Draw()
{
    // Calculate the position to draw the food, applying the offset and scaling by cell size
    int xPos = offset + position.x * cellSize;
    int yPos = offset + position.y * cellSize;
    
    // Draw the texture at the calculated position, with a white tint
    DrawTexture(texture, xPos, yPos, WHITE);
}

// Initialize the food object with cell size, cell count, and offset values
void Food::Initialize(int cellSize, int cellCount, int offset)
{
    this->cellSize = cellSize;   // Set the size of each grid cell
    this->cellCount = cellCount; // Set the number of cells along each dimension
    this->offset = offset;       // Set the offset for positioning on the screen
}

// Method to spawn food at a random position on the grid
Vector2 Food::Spawn()
{
    // Generate a new random position for the food
    position = GenerateRandomPosition();
    
    // Return the generated position
    return position;
}

// Generate a random position within the bounds of the grid
Vector2 Food::GenerateRandomPosition()
{
    // Randomly select x and y coordinates within the grid limits
    float x = GetRandomValue(0, cellCount - 1);
    float y = GetRandomValue(0, cellCount - 1);

    // Return the random position as a Vector2
    return Vector2{x, y};
}
