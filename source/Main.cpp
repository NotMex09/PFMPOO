#include "raylib.h"
#include "Maze.cpp"
#include "Player.cpp"
#include "Level.cpp"
#include "Game.cpp"
#include "Globals.cpp"
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <algorithm>


// Main function with difficulty selection
int main() {
    InitWindow(screenWidth, screenHeight, "Maze Game");
    InitAudioDevice(); // Configure the audio system here

    // Loading the game icon
    Image icon = LoadImage("assets/LOGO1.png");
    SetWindowIcon(icon);
    UnloadImage(icon);

    // Loading  textures
    Texture2D background = LoadTexture("assets/HOMEPAGE.png");

    Texture2D background2 = LoadTexture("assets/BG3.png");
    Texture2D mazeName = LoadTexture("assets/MAZE_GAME.png");
    Texture2D CHOOSE = LoadTexture("assets/CHOOSE.png");

    Texture2D CHOOSE_M = LoadTexture("assets/CHOOSE_M.png");
    Texture2D MULTI = LoadTexture("assets/MULTI.png");
    Texture2D SINGLE = LoadTexture("assets/SINGLE.png");

    // Load the button texture
    normalbut = LoadTexture("assets/medumbut.png");
    startbut = LoadTexture("assets/Start_Game.png");

    HelpBut = LoadTexture("assets/HELP.png");
    ExitBut = LoadTexture("assets/EXIT.png");
    DevsBut = LoadTexture("assets/DEVS.png");
    BackBut = LoadTexture("assets/BACK.png");


    hardbut = LoadTexture("assets/hardbut.png");
    easybut = LoadTexture("assets/easybut.png");
    restart = LoadTexture("assets/easybut.png");
    scorebut = LoadTexture("assets/SCORES_BUTTON.png");

    // Loading the sound effects
    buttonSound = LoadSound("assets/buttib_click.mp3");
    bgSound = LoadSound("assets/game-music.mp3");
    winnerSound = LoadSound("assets/winner.mp3");
    hardSound = LoadSound("assets/hard.mp3");
    PantherSound = LoadSound("assets/Pink_Panther.mp3");
    PlaySound(bgSound);
    bool isGameRunning = false;
    int difficulty = 0; // 0 = easy

    Game game; // Game object

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (currentState == MENU) {
            // If we are in the menu list
            BeginDrawing();
            DrawTexture(background, 0, 0, RAYWHITE);
            DrawTexture(mazeName, screenWidth / 2 - mazeName.width / 2, 120, WHITE);

            //Drawing play button
            Rectangle playButton = { screenWidth / 2.0f - 140, screenHeight / 2.0f - 45, 344, 74 };
            DrawTexture(startbut, playButton.x, playButton.y, WHITE);
            DrawText("", playButton.x + 35, playButton.y + 10, 50, WHITE);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), playButton)) {
                PlaySound(buttonSound);
                currentState = NOMBRE_SELECTION;
            }
            //Help button
            Rectangle helpButton = { screenWidth / 2.0f - 100, screenHeight / 2.0f + 50, 200, 50 };
            DrawTexture(HelpBut, helpButton.x, helpButton.y, WHITE);
            DrawText("", helpButton.x + 50, helpButton.y + 10, 30, RAYWHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), helpButton)) {
                PlaySound(buttonSound);
                currentState = HELP;
            }
            //Devs Button
            Rectangle devsButton = { screenWidth / 2.0f - 100, screenHeight / 2.0f + 125, 200, 50 }; // Adjust position and size as needed
            DrawTexture(DevsBut, devsButton.x, devsButton.y, WHITE);
            DrawText("", devsButton.x + 50, devsButton.y + 10, 30, RAYWHITE);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), devsButton)) {
                currentState = DEVS;
            }
            // Exit button
            Rectangle exitButton = { screenWidth / 2.0f - 100, screenHeight / 2.0f + 200, 200, 50 };
            DrawTexture(ExitBut, exitButton.x, exitButton.y, WHITE);

            DrawText("", exitButton.x + 50, exitButton.y + 10, 30, RAYWHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), exitButton)) {
                PlaySound(buttonSound);
                CloseWindow(); // Exit the game
                break;
            }

            EndDrawing();
        }
        else if (currentState == HELP) {
            BeginDrawing();
            DrawTexture(background, 0, 0, RAYWHITE);

            ClearBackground(RAYWHITE);

            DrawText("HOW TO PLAY", screenWidth / 2 - MeasureText("HOW TO PLAY", 50) / 2, 70, 60, RED);

            // Instructions
            DrawText("-Use arrow keys to move the player.", 30, 140, 40, WHITE);
            DrawText("-Reach the red circle to win.", 30, 200, 40, WHITE);
            DrawText("-Press 'R' to reset the game.", 30, 260, 40, WHITE);
            DrawText("-Click 'Scores' to view your best", 30, 320, 40, WHITE);
            DrawText(" times", 30, 380, 40, WHITE);
            DrawText("-In multiplayer mode, Player 2 uses", 30, 440, 40, WHITE);
            DrawText(" W/A/S/D keys.", 30, 500, 40, WHITE);

            // Back Button
            Rectangle backButton = { screenWidth / 2.0f - 100, screenHeight - 50, 200, 50 };
            DrawTexture(BackBut, backButton.x, backButton.y, WHITE);
            DrawText("", backButton.x + 20, backButton.y + 10, 20, RAYWHITE);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), backButton)) {
                PlaySound(buttonSound);
                StopSound(PantherSound);
                currentState = MENU;
            }

            EndDrawing();
        }
        else if (currentState == DEVS) {
            BeginDrawing();

            DrawTexture(background, 0, 0, RAYWHITE);
            ClearBackground(RAYWHITE);

            DrawText("DEVELOPERS", 200, 150, 60, RED); // Title
            DrawText("El Kajdouhi Mohamed Ayman", 100, 200, 40, WHITE);
            DrawText("Akdi Fouad", 100, 250, 40, WHITE);
            DrawText("Afazaz Ilyas", 100, 300, 40, WHITE);
            DrawText("Rabih Senhaji Anas", 100, 350, 40, WHITE);
            // Back button
            Rectangle backButton = { screenWidth / 2.0f - 100, screenHeight - 100, 200, 50 };
            DrawTexture(BackBut, backButton.x, backButton.y, WHITE);
            DrawText("", backButton.x + 20, backButton.y + 10, 20, RAYWHITE);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), backButton)) {
                currentState = MENU;
            }
            EndDrawing();
        }
        else if (currentState == NOMBRE_SELECTION) {
            BeginDrawing();

            DrawTexture(background, 0, 0, RAYWHITE);

            DrawTexture(CHOOSE_M, screenWidth / 2 - CHOOSE_M.width / 2, 125, RAYWHITE);
            // Clearing the background
            ClearBackground(RED);
            Rectangle backButton = { screenWidth / 2.0f - 100, screenHeight / 2.0f + 125, 200, 50 };
            DrawTexture(BackBut, backButton.x, backButton.y, WHITE);
            DrawText("", backButton.x + 40, backButton.y + 10, 30, RAYWHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), backButton)) {
                currentState = MENU;
            }
            // Single button 
            Rectangle SINGLEButton = { screenWidth / 2.0f - 100, screenHeight / 2.0f - 25, 200, 50 };
            // Change "PLAY" to "SINGLE PLAYER"
            DrawTexture(SINGLE, SINGLEButton.x, SINGLEButton.y, WHITE);
            Rectangle multiplayerButton = { screenWidth / 2.0f - 100, screenHeight / 2.0f + 50, 200, 50 };
            DrawTexture(MULTI, multiplayerButton.x, multiplayerButton.y, WHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), multiplayerButton)) {
                PlaySound(buttonSound);
                isMultiplayer = true; // Flag for multiplayer mode
                //game.Reset();
                currentState = DIFFICULTY_SELECTION;
            }



            else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), SINGLEButton)) {
                PlaySound(buttonSound);
                isMultiplayer = false;
                game.Reset();
                currentState = DIFFICULTY_SELECTION;
            }

            EndDrawing();

        }
        else if (currentState == DIFFICULTY_SELECTION) {
            //  choosing the level of difficulty
            BeginDrawing();
            DrawTexture(background, 0, 0, RAYWHITE);
            DrawTexture(CHOOSE, screenWidth / 2 - CHOOSE.width / 2, 85, RAYWHITE);

            // Clearing background
            ClearBackground(RED);
            StopSound(PantherSound);
            Rectangle backButton = { screenWidth / 2.0f - 100, screenHeight / 2.0f + 165, 200, 50 };
            DrawTexture(BackBut, backButton.x, backButton.y, WHITE);

            DrawText("", backButton.x + 40, backButton.y + 10, 30, RAYWHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), backButton)) {
                PlaySound(buttonSound);

                currentState = NOMBRE_SELECTION;
            }    // Level buttons area
            Rectangle easyButton = { screenWidth / 2.0f - 100, screenHeight / 2.0f - 65, 200, 50 };
            Rectangle mediumButton = { screenWidth / 2.0f - 100, screenHeight / 2.0f + 15, 200, 50 };
            Rectangle hardButton = { screenWidth / 2.0f - 100, screenHeight / 2.0f + 85, 200, 50 };

            // Drawing buttons
            DrawTexture(easybut, easyButton.x, easyButton.y, WHITE);
            DrawText("", easyButton.x + 50, easyButton.y + 10, 30, DARKGRAY);

            DrawTexture(normalbut, mediumButton.x, mediumButton.y, WHITE);
            DrawText("", mediumButton.x + 50, mediumButton.y + 10, 30, DARKGRAY);

            DrawTexture(hardbut, hardButton.x, hardButton.y, WHITE);
            DrawText("", hardButton.x + 50, hardButton.y + 10, 30, DARKGRAY);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), easyButton)) {
                PlaySound(buttonSound);
                StopSound(bgSound);
                PlaySound(PantherSound);
                difficulty = 0; // easy
                currentState = GAME;
            }
            else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), mediumButton)) {
                PlaySound(buttonSound);
                StopSound(bgSound);
                PlaySound(PantherSound);

                difficulty = 1; // medium
                currentState = GAME;
            }
            else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), hardButton)) {
                PlaySound(buttonSound);
                StopSound(bgSound);
                PlaySound(hardSound);

                difficulty = 2; // hard
                currentState = GAME;
            }

            EndDrawing();
        }
        else if (currentState == GAME) {
            // Create a Level object with the selected difficulty
            Level currentLevel(difficulty);

            // Run the level
            currentLevel.Run(game);

            // Check if the user clicked "Retour" (return to menu)
            if (currentState == NOMBRE_SELECTION) {
                StopSound(PantherSound);
                PlaySound(buttonSound);
                continue;  // Restart the main loop
            }

            break; // Exit the loop when the game ends
        }


    }

    // Unloading ressources
    UnloadSound(buttonSound);
    UnloadSound(bgSound);
    UnloadSound(winnerSound);
    UnloadSound(hardSound);
    UnloadSound(PantherSound);
    // Unload the button texture before closing
    UnloadTexture(normalbut);

    UnloadTexture(background);

    CloseAudioDevice();
    CloseWindow();
    return 0;
}