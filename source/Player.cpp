#include "raylib.h"
#include "Maze.cpp"

Texture2D PLAYERIMAGE;
Texture2D goalTexture;
// Player class
class Player {
public:
    Player() : posX(0), posY(0) {}
    Texture2D PLAYERIMAGE = LoadTexture("assets/PLAYER.png");
    Texture2D goalTexture = LoadTexture("assets/CHEESE_IM.png");
    void SetPosition(int x, int y) {
        posX = x;
        posY = y;
    }

    void Update(const Maze& maze, bool isPlayer2 = false, float deltaTime = 0.016f) {
        static float moveCooldown = 0.1f; // Minimum time (in seconds) between moves
        static float timeSinceLastMove = 0.0f;

        // Update the time since the last move
        timeSinceLastMove += deltaTime;

        // If not enough time has passed, do nothing
        if (timeSinceLastMove < moveCooldown) {
            return;
        }
        int newX = posX;
        int newY = posY;

        if (isPlayer2) { // Controls for player 2
            PLAYERIMAGE = LoadTexture("assets/oo_PLAYER.png");
            if (IsKeyDown(KEY_W) && !maze.IsWall(posX, posY, 0)) newY--;
            if (IsKeyDown(KEY_D) && !maze.IsWall(posX, posY, 1)) newX++;
            if (IsKeyDown(KEY_S) && !maze.IsWall(posX, posY, 2)) newY++;
            if (IsKeyDown(KEY_A) && !maze.IsWall(posX, posY, 3)) newX--;
        }
        else { // Default controls
            if (IsKeyDown(KEY_UP) && !maze.IsWall(posX, posY, 0)) newY--;
            if (IsKeyDown(KEY_RIGHT) && !maze.IsWall(posX, posY, 1)) newX++;
            if (IsKeyDown(KEY_DOWN) && !maze.IsWall(posX, posY, 2)) newY++;
            if (IsKeyDown(KEY_LEFT) && !maze.IsWall(posX, posY, 3)) newX--;
        }

        if (newX >= 0 && newX < mazeCols && newY >= 0 && newY < mazeRows) {
            posX = newX;
            posY = newY;
            timeSinceLastMove = 0.0f;
        }
    }

    void Draw() const {
        DrawTexture(PLAYERIMAGE, posX * cellSize, posY * cellSize, WHITE);
    }

    void DrawGoal() const {
        int goalX = (mazeCols - 1) * cellSize + cellSize / 2;
        int goalY = (mazeRows - 1) * cellSize + cellSize / 2;
        DrawTexture(goalTexture, goalX - goalTexture.width / 2, goalY - goalTexture.height / 2, WHITE);

    }

    bool HasReachedGoal() const {
        return posX == mazeCols - 1 && posY == mazeRows - 1;
    }

private:
    int posX, posY;

};