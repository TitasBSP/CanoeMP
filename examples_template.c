
#include "raylib.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"
#include "math.h"
#include "rlgl.h"

// TODO:
//
// Login screen w/ username and password
// - Reintroduce rectangles for user and pass rects
// - test if typing works
// - comparison ifs for both username and passwords, you will do user appending later
// Introduce song library, UI with pause, volume slider and display img w/ text
// Import songs
// Ability to make playlists
// Ordered and shuffle options
// Algorithm for genres and song lengths
// Toggle for explicit songs
// Language support
//
// AND MUCH MORE!

char users[9][17] = {"titasp"};
char pass[9][17] = {"0000"};

char loginUSERNAMEinput[17] = "";
char loginPASSWORDinput[17] = "";


// Functions tied to the application

void deleteChars(int bar) {
    int len;
    
    switch (bar) {
        case 0:
            len = strlen(loginUSERNAMEinput);
            loginUSERNAMEinput[len - 1] = '\0';  // overwrite last character with null terminator
            break;        
        case 1:
            len = strlen(loginPASSWORDinput);
            loginPASSWORDinput[len - 1] = '\0';  // overwrite last character with null terminator
            break;
    }

    if (len == 0) {
        printf("Nothing to delete.\n"); // Debugger
        return;
    }

}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    int usernameLEN = strlen(loginUSERNAMEinput);
    int passwordLEN = strlen(loginPASSWORDinput);
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Canoe - Music Player");
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
    
    Image loginBTNPNG = LoadImage("loginbtn.png");
    ImageResize(&loginBTNPNG, 256, 128);
    Texture2D textureLoginBTN = LoadTextureFromImage(loginBTNPNG);  
    
    // Booleans for screens
    bool loginScreen = true;
    
    // Rectangles for hovers
    float loginBTNx = 840;
    float loginBTNy = 830;
    Rectangle loginBTN = {loginBTNx, loginBTNy, 200, 100};
    
    float userBLACKx = 640;
    float userBLACKy = 510;
    Rectangle userBLACK = {userBLACKx, userBLACKy, 620, 120};    
    
    float passBLACKx = 640;
    float passBLACKy = 670;
    Rectangle passBLACK = {passBLACKx, passBLACKy, 620, 120};
    
    
    // Positions for vectors
    Vector2 posCanoeLogin = {850, 240};
    Vector2 posLoginText = {840, 845};
    
    // Alphas
    float alphaLogin = 0.0f;   
    float alphaLoginLogo = 0.0f;
    float alphaLoginBTN = 1.0f;
    
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        int pressedKey = GetCharPressed();
        Vector2 MousePos = GetMousePosition();
        bool isHoveringLoginBTN = CheckCollisionPointRec(MousePos, loginBTN);
        bool isHoveringUSERwndw = CheckCollisionPointRec(MousePos, userBLACK);
        bool isHoveringPASSwndw  = CheckCollisionPointRec(MousePos, passBLACK);
        
        
        bool writingInUSERwndw = false;
        
        
        
        // IF-s for hovering
        if (isHoveringLoginBTN && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && loginScreen == true) {
            loginScreen = false;
            printf("working");
            fflush(stdout);
        } else if (isHoveringLoginBTN && loginScreen == true) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            alphaLoginBTN = 0.7f;
        } else {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            alphaLoginBTN = 1.0f;
        }
        
        // Logic

        int i = 0;
        int j = 0;
        if (usernameLEN < 16) {
            loginUSERNAMEinput[i] = (char)pressedKey;
            i++;
        } else {
            loginUSERNAMEinput[usernameLEN - 1] = '\0';
            i--;
        }        

        if (passwordLEN < 16) {
            loginPASSWORDinput[j] = (char)pressedKey;    
            j++;
        } else {
            loginPASSWORDinput[passwordLEN - 1] = '\0';
            j--;
        }    
        
        
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
                
                DrawRectangleRec(userBLACK, Fade(BLACK, alphaLogin));
                DrawRectangle(650, 520, 600, 100, Fade(DARKGRAY, alphaLogin));
                
                if (isHoveringUSERwndw && (MOUSE_LEFT_BUTTON) && loginScreen == true) {
                    writingInUSERwndw = true;
                    printf("working");
                    fflush(stdout);
                } else if (isHoveringLoginBTN && loginScreen == true) {
                    SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
                    alphaLoginBTN = 0.7f;
                } else {
                    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
                    alphaLoginBTN = 1.0f;
                }
                
                DrawRectangleRec(passBLACK, Fade(BLACK, alphaLogin));
                DrawRectangle(650, 680, 600, 100, Fade(DARKGRAY, alphaLogin));
      
                DrawTexture(textureLoginBTN, screenWidth+15, screenHeight+365, Fade(WHITE, alphaLoginBTN));
                DrawTextEx(JupiterFont, "Login", posLoginText, 70, 5, Fade(WHITE, alphaLoginBTN)); 
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
