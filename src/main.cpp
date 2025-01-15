#define RAYGUI_IMPLEMENTATION
// libs

// default libs
#include <cstdlib>
#include <string>

// raylib and raylib modules
#include <raylib.h>

#include <raygui.h>

// modules

// refresh window only
#include "refreshWindow/refreshWindow.h"

// native fullscreen (not stretched)
#include "nativeFullscreen/nativeFullscreen.h"

// Define actions for each button with a variable for the URL
void OpenURL(const std::string& url) {
    #ifdef _WIN32  // Windows
        std::string command = "cmd /c start " + url;
        system(command.c_str());
    #else  // Linux
        std::string command = "xdg-open " + url;
        system(command.c_str());
    #endif
}

// Example functions that use the OpenURL function
void OpenGitHub() {
    OpenURL("https://github.com/monitio/leoht");
}

void OpenWiki() {
    OpenURL("https://github.com/monitio/leoht/wiki");
}

void OpenIssues() {
    OpenURL("https://github.com/monitio/leoht/issues");
}

void OpenPullRequests() {
    OpenURL("https://github.com/monitio/leoht/pulls");
}

void OpenLicense() {
    OpenURL("https://github.com/monitio/leoht/blob/main/LICENSE");
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------

    const std::string programVersion = "0.8.1";

    const int guiWidth = 1280;
    const int guiHeight = 720;

    const int initialWidth = guiWidth;
    const int initialHeight = guiHeight;

    const int screenWidth = guiWidth;
    const int screenHeight = guiHeight;

    // Make the window, give it a title, width and height
    InitWindow(screenWidth, screenHeight, "leoht - 3d scene");

    std::string refreshRateT = std::to_string(GetMonitorRefreshRate(0)) + " hz";

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

    bool showGuide = true;              // Control guide visability
    //std::string tutMessage = "Leoht [dynamicTutMessage] ^ %";
    std::string tutMessage = 
            "Hello and welcome to Leoht.\n"
            "You are currently using version " + programVersion + "\n\n"
            "The tutorial is on the Github wiki linked below this message.\n"
            "If you need help, please check in this order:\n"
            "the wiki, Github Issues/Pull requests, and then email me through the main email.\n\n"
            "Thanks,\nJames - Monitio creator";

    // dev-mode attributes
    bool debugMode = false;             // debugMode checking

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

        // Check if F5 is pressed to toggle debug mode
        if (IsKeyPressed(KEY_F5)) {
            debugMode = !debugMode; // Toggle the debugMode flag
        }

        // Check if F4 is pressed to trigger a refresh
        if (IsKeyPressed(KEY_F4)) {
            refreshWindow();
        }

        // Check if F11 is pressed to toggle native fullscreen mode
        if (IsKeyPressed(KEY_F11)) {
            ToggleNativeFullscreen();
        }

        if (IsKeyPressed(KEY_F1)) {
            showGuide = true; // Show the guide
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

            // If debugMode is true, display debug tools
            if (debugMode) {
                DrawFPS(10, 10);
                DrawText(refreshRateT.c_str(), 10, 30, 20, GRAY);
            }
            
            if (showGuide) {
                // Display message box
                int result = GuiMessageBox(
                    (Rectangle){ 85, 70, 450, 300 },
                    "#191#Leoht Guide",
                    tutMessage.c_str(),  // Use tutMessage
                    "GitHub;Wiki;Issues;Pull-Request;License"
                );
                
                // Check if the close button (index 0) is clicked
                if (result == 0) {
                    showGuide = false;  // Close the message box if close button clicked
                }
                // Handle button clicks
                else if (result == 1) OpenGitHub();
                else if (result == 2) OpenWiki();
                else if (result == 3) OpenIssues();
                else if (result == 4) OpenPullRequests();
                else if (result == 5) OpenLicense();
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
