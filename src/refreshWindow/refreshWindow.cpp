#include "refreshWindow.h"
#include <raylib.h>

#if defined(__linux__)
#include <X11/Xlib.h> // X11 for Linux
#endif

static const int guiWidth = 1280;
static const int guiHeight = 720;

void refreshWindow() {
        // Clear the window's drawing
        ClearBackground(RAYWHITE);
}
