#include "raylib.h"
#include "Player.cpp"
#include "Globals.cpp"
#include <vector>
#include <algorithm>


// Constants for window size
const int screenWidth = 800;
const int screenHeight = 600;
bool isMultiplayer = false;
Sound buttonSound; // Sounds declaration
Sound winnerSound;
Sound bgSound;
Sound hardSound;
Sound PantherSound;
// Game class
class Game {
public:
    Game() : level(1), gameWon(false), timer(0), winnerSoundPlayed(false),

        player(), player2() {
    }  // Timer starts at 0

    void UpdateMazeWallColor(Color newColor) {
        maze.wallColor = newColor;
    }

    void Run() {
        Reset();
        //InitWindow(screenWidth, screenHeight, "Maze Game");
        SetTargetFPS(60);

        while (!WindowShouldClose() && !exitToMenu) {
            Update();
            Draw();
        }

        CloseWindow();
    }
    void Reset() {
        if (gameWon) {
            scores.push_back(timer); // Save the score
            std::sort(scores.begin(), scores.end());
            PlaySound(bgSound);
        }

        maze.GenerateMaze();
        player = Player();
        player2 = Player(); // Reset player 2
        if (isMultiplayer) {

            player2.SetPosition(0, mazeRows - 1); // Set Player 2 to (0, mazeRows-1)
        }

        gameWon = false;
        winnerSoundPlayed = false; // Reinitialization

        timer = 0;
    }

private:
    std::vector<float> scores; // Store scores
    bool showScores = false;   // Toggle scores table
    bool exitToMenu = false; // Add a flag to indicate "Retour" button click
    bool isMusicPlaying = true; // music running by default

    Maze maze;
    Player player, player2; // Second player for multiplayer

    int level;
    bool gameWon;
    float timer;  // Timer (as seconds)
    bool winnerSoundPlayed;   // To track the playback of the sound

    void Update() {
        if (IsKeyPressed(KEY_R)) Reset();

        if (!gameWon) {
            timer += GetFrameTime();
            player.Update(maze);
            if (isMultiplayer) player2.Update(maze, true); // Update player 2 in multiplayer mode


            if (player.HasReachedGoal() || (isMultiplayer && player2.HasReachedGoal())) {
                gameWon = true;
            }

        }
        UpdateMusicControl();


        if (gameWon && !winnerSoundPlayed) { // Turn on the sound once you win
            PlaySound(winnerSound);
            StopSound(bgSound);
            StopSound(hardSound);
            StopSound(PantherSound);
            winnerSoundPlayed = true;
        }

        // Check for "Scores" button click
        Rectangle scoresButton = { screenWidth - 150, screenHeight - 40, 100, 30 };
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), scoresButton)) {
            PlaySound(buttonSound);

            showScores = !showScores; // Toggle scores table
        }
        // Check for "RESET" button click
        Rectangle resetButton = { screenWidth - 580, screenHeight - 40, 100, 30 };
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), resetButton)) {
            PlaySound(buttonSound);

            Reset();

        }
        // Check for "Retour" button click
        Rectangle retourButton = { screenWidth - 350, screenHeight - 40, 100, 30 };
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), retourButton)) {
            PlaySound(buttonSound);
            StopSound(hardSound);
            PlaySound(bgSound);

            currentState = NOMBRE_SELECTION;
            exitToMenu = true; // Set flag to exit game

            return;
        }

    }

    void Draw() const {
        BeginDrawing();
        ClearBackground(BLACK);

        maze.DrawMaze();
        player.Draw();
        player.DrawGoal();
        if (isMultiplayer) {
            player2.Draw();
            player2.DrawGoal(); // Draw goal for player 2 // Draw goal for both players
        }

        // Display the timer at the bottom of the screen
        DrawText(TextFormat("Time: %.2f", timer), screenWidth / 2 - MeasureText(TextFormat("Time: %.2f", timer), 20) / 2, screenHeight - 30, 20, WHITE);
        // Display the "Scores" button
        Rectangle scoresButton = { screenWidth - 160, screenHeight - 40, 100, 30 };
        DrawRectangleRec(scoresButton, BLUE);

        DrawText("Scores", scoresButton.x + 10, scoresButton.y + 5, 20, WHITE);

        // Display the "RESET" button
        Rectangle resetButton = { screenWidth - 580, screenHeight - 40, 100, 30 };
        DrawRectangleRec(resetButton, BLUE);

        DrawText("Reset", resetButton.x + 10, resetButton.y + 5, 20, WHITE);

        // Display the "RETOUR" button
        Rectangle retourButton = { screenWidth - 300, screenHeight - 40, 100, 30 };
        DrawRectangleRec(retourButton, BLUE);

        DrawText("Back", retourButton.x + 10, retourButton.y + 5, 20, WHITE);

        // Display the scores table if toggled
        if (showScores) {

            DrawRectangle(screenWidth / 4, screenHeight / 4, screenWidth / 2, screenHeight / 2, DARKGRAY);
            DrawText("Scores Table", screenWidth / 2 - 60, screenHeight / 4 + 10, 20, WHITE);

            for (size_t i = 0; i < scores.size(); ++i) {
                DrawText(TextFormat("%d. %.2f", i + 1, scores[i]),
                    screenWidth / 4 + 20,
                    screenHeight / 4 + 50 + i * 20,
                    18,
                    WHITE);
            }
        }
        if (gameWon) {
            if (isMultiplayer) {
                if (player.HasReachedGoal()) {
                    DrawText("Player 1 won!", screenWidth / 2 - 150, screenHeight / 2, 40, GREEN);
                }
                else if (player2.HasReachedGoal()) {

                    DrawText("Player 2 won!", screenWidth / 2 - 150, screenHeight / 2, 40, GREEN);
                }
            }
            else {
                DrawText("You won the game!", screenWidth / 2 - 180, screenHeight / 2, 40, GREEN);
            }
        }
        DrawMusicControl();

        EndDrawing();
    }
    //Update the state of music
    void UpdateMusicControl() {
        Rectangle musicButton = { screenWidth - 760, 560, 145, 30 };
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), musicButton)) {
            if (isMusicPlaying) {
                PauseSound(bgSound);// Temporarily stop music
                PauseSound(PantherSound);
                PauseSound(hardSound);
            }
            else {
                ResumeSound(buttonSound);// Resume 
            }
            isMusicPlaying = !isMusicPlaying; // Reverse the situation
            if (isMusicPlaying) {
                if (!IsSoundPlaying(bgSound)) ResumeSound(bgSound);
                if (!IsSoundPlaying(PantherSound)) ResumeSound(PantherSound);
                if (!IsSoundPlaying(hardSound)) ResumeSound(hardSound);

            }
        }
    }
    //Draw nusic control button

    void DrawMusicControl() const {
        Rectangle musicButton = { screenWidth - 760, 560, 145, 30 };
        DrawRectangleRec(musicButton, BLUE);
        DrawText(isMusicPlaying ? "Music Pause" : "Music Play", musicButton.x + 10, musicButton.y + 5, 20, WHITE);
    }

};