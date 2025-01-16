#include "nativeFullscreen.h"

#include <raylib.h>

static const int guiWidth = 1280;
static const int guiHeight = 720;

static int nativefsWidth = 0;  // To store the width of the primary screen
static int nativefsHeight = 0; // To store the height of the primary screen
static bool isFullscreen = false; // To track fullscreen state

void GetPrimaryMonitorDimensions() {
    #if defined(_WIN32)
    // Windows: Use Raylib's internal functions to get the primary monitor's dimensions
    int monitorCount = GetMonitorCount();  // Get the number of monitors
    if (monitorCount > 0) {
        nativefsWidth = GetMonitorWidth(0);  // Get the width of the primary monitor (index 0)
        nativefsHeight = GetMonitorHeight(0); // Get the height of the primary monitor
    }
    #elif defined(__linux__)
    // Linux: Use Raylib to get the screen width and height of the primary monitor
    int monitorCount = GetMonitorCount();  // Get the number of monitors
    if (monitorCount > 0) {
        nativefsWidth = GetMonitorWidth(0);  // Get the width of the primary monitor (index 0)
        nativefsHeight = GetMonitorHeight(0); // Get the height of the primary monitor
    }
    #endif
}

// Function to toggle fullscreen and handle resolution automatically
void ToggleNativeFullscreen() {
    GetPrimaryMonitorDimensions(); // Ensure that the screen size is fetched

    if (!isFullscreen) {
        // Set the window size to match the primary monitor's resolution
        SetWindowSize(nativefsWidth, nativefsHeight);
        SetWindowState(FLAG_FULLSCREEN_MODE); // Set to fullscreen mode
        isFullscreen = true;
    } else {
        SetWindowSize(guiWidth, guiHeight); // Reset to the normal window resolution
        ClearWindowState(FLAG_FULLSCREEN_MODE); // Exit fullscreen mode
        isFullscreen = false;
    }
}
