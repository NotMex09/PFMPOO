#include "raylib.h"
#include "Game.cpp"

//Level class
class Level {
public:
    int mazeCols;
    int mazeRows;
    int cellSize;
    int difficulty;
    Color wallColor;

    Level(int diff) : difficulty(diff), mazeCols(0), mazeRows(0), cellSize(0), wallColor(GREEN) {
        ConfigureLevel();
    }

    void ConfigureLevel() {
        // Set maze dimensions and color based on difficulty
        switch (difficulty) {
        case 0: // Easy
            mazeCols = 12;
            mazeRows = 8;
            cellSize = 67;
            wallColor = GREEN;
            break;
        case 1: // Medium
            mazeCols = 20;
            mazeRows = 13;
            cellSize = 40;
            wallColor = YELLOW;
            break;
        case 2: // Hard
            mazeCols = 25;
            mazeRows = 17;
            cellSize = 32;
            wallColor = RED;
            break;
        }
    }

    void ApplySettings(Game& game) {
        // Update the game settings with the current level's configuration
        game.UpdateMazeWallColor(wallColor); // Set the maze wall color
        game = Game();                      // Reset the game for the level
        game.UpdateMazeWallColor(wallColor); // Reapply the wall color
    }

    void Run(Game& game) {
        ApplySettings(game);
        game.Run();
    }
};