// libs

// default libs
#include <string>

// raylib and raylib modules
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

// modules

// refresh window only
#include "refreshWindow/refreshWindow.h"

// native fullscreen (not stretched)
#include "nativeFullscreen/nativeFullscreen.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int guiWidth = 1280;
    const int guiHeight = 720;

    const int initialWidth = guiWidth;
    const int initialHeight = guiHeight;

    const int screenWidth = guiWidth;
    const int screenHeight = guiHeight;

    // Make the window, give it a title, width and height
    InitWindow(screenWidth, screenHeight, "leoht - raylib [core] - 3d scene");

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };
    Vector3 cubeSize = { 2.0f, 2.0f, 2.0f };

    Ray ray = { 0 };                    // Picking line ray
    RayCollision collision = { 0 };     // Ray collision hit info

    

    bool showFPS = false;               // Set showFPS state as false for later use
    SetTargetFPS(9999);                 // Set our game to run at 9999 frames-per-second as max
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {        // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        if (IsCursorHidden()) UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        // Toggle camera controls
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            if (IsCursorHidden()) EnableCursor();
            else DisableCursor();
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (!collision.hit) {
                ray = GetScreenToWorldRay(GetMousePosition(), camera);

                // Check collision between ray and box
                collision = GetRayCollisionBox(ray,
                            (BoundingBox){(Vector3){ cubePosition.x - cubeSize.x/2, cubePosition.y - cubeSize.y/2, cubePosition.z - cubeSize.z/2 },
                                          (Vector3){ cubePosition.x + cubeSize.x/2, cubePosition.y + cubeSize.y/2, cubePosition.z + cubeSize.z/2 }});
            }
            else collision.hit = false;
        }

        // Check if F5 is pressed to toggle the FPS display
        if (IsKeyPressed(KEY_F5)) {
            showFPS = !showFPS; // Toggle the showFPS flag
        }

        // Check if F4 is pressed to trigger a refresh
        if (IsKeyPressed(KEY_F4)) {
            refreshWindow();
        }

        // Check if F11 is pressed to toggle native fullscreen mode
        if (IsKeyPressed(KEY_F11)) {
            ToggleNativeFullscreen();
        }

        const int DLPad = 21; // Set left padding (adjust as needed)
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Calculate the position for the text to be in the bottom-right corner
            int textWidth = MeasureText("Right click mouse to toggle camera controls", 10);
            int TxPos1 = DLPad; // 10 is padding from the right
            int TyPos1 = GetScreenHeight() - 30; // 30 is the height of the text (for padding)

            BeginMode3D(camera);

                if (collision.hit) {
                    DrawCube(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, RED);
                    DrawCubeWires(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, MAROON);

                    DrawCubeWires(cubePosition, cubeSize.x + 0.2f, cubeSize.y + 0.2f, cubeSize.z + 0.2f, GREEN);
                }
                else {
                    DrawCube(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, GRAY);
                    DrawCubeWires(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, DARKGRAY);
                }

                DrawRay(ray, MAROON);
                DrawGrid(10, 1.0f);

            EndMode3D();

            if (collision.hit) DrawText("BOX SELECTED", (screenWidth - MeasureText("BOX SELECTED", 30)) / 2, (int)(screenHeight * 0.1f), 30, GREEN);

            DrawText("Right click mouse to toggle camera controls", TxPos1, TyPos1, 10, GRAY);

            std::string refreshRateT = std::to_string(GetMonitorRefreshRate(0));
            DrawText(refreshRateT.c_str(), 10, 20, 10, GRAY);

            // If showFPS is true, display the FPS using DrawFPS
            if (showFPS) {
                DrawFPS(10, 10); // Draw the FPS at position (10, 10)
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
