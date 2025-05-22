
#include "raylib.h"

// TODO:
//
// Login screen w/ username and password
// Introduce song library, UI with pause, volume slider and display img w/ text
// Import songs
// Ability to make playlists
// Ordered and shuffle options
// Algorithm for genres and song lengths
// Toggle for explicit songs
// Language support
//
// AND MUCH MORE!



//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);
    
    int display = GetCurrentMonitor();
    SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
    ToggleFullscreen();
    
    // Font
    Font JupiterFont = LoadFont("romulus.png");

    // Images to initialize
    Image loginScreenPNG = LoadImage("mainmenucover.png");  
    Texture2D textureLogin = LoadTextureFromImage(loginScreenPNG);  
    UnloadImage(loginScreenPNG);
    
    Image loginLogoPNG = LoadImage("canoeLogo.png");
    ImageResize(&loginLogoPNG, 256, 256);
    Texture2D textureLoginLogo = LoadTextureFromImage(loginLogoPNG);  
    
    // Booleans for screens
    bool loginScreen = true;
    
    // Positions for vectors
    Vector2 posCanoeLogin = {850, 200};
    
    // Alphas
    float alphaLogin = 0.0f;   
    float alphaLoginLogo = 0.0f;
    
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        
            if (loginScreen) {
                if (alphaLogin < 1) alphaLogin += 0.03f;
                if (alphaLoginLogo < 0.8) alphaLoginLogo += 0.03f;
                ClearBackground(BLACK);
                DrawTexture(textureLogin, screenWidth-800, screenHeight-900, Fade(WHITE, 0.5f)); 
                DrawTextEx(JupiterFont, "CANOE", posCanoeLogin, 150, 25, Fade(WHITE, alphaLogin));  
                DrawTexture(textureLoginLogo, screenWidth-250, screenHeight-265, Fade(WHITE, alphaLoginLogo));
                
                DrawRectangle(640, 510, 620, 120, Fade(BLACK, alphaLogin));
                DrawRectangle(650, 520, 600, 100, Fade(DARKGRAY, alphaLogin));                
                
                DrawRectangle(640, 670, 620, 120, Fade(BLACK, alphaLogin));
                DrawRectangle(650, 680, 600, 100, Fade(DARKGRAY, alphaLogin));
            }
            

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    
    UnloadImage(loginLogoPNG);
    UnloadTexture(textureLoginLogo);
 
    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded resources at this point

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
