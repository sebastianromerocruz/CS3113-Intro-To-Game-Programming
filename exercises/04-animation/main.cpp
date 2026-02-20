#include "CS3113/Entity.h"

// Global Constants
constexpr int SCREEN_WIDTH  = 1600 / 2,
              SCREEN_HEIGHT = 900 / 2,
              FPS           = 120;

constexpr char    BG_COLOUR[] = "#404F59";
constexpr Vector2 ORIGIN      = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

// Global Variables
AppStatus gAppStatus = RUNNING;
float gPreviousTicks = 0.0f;

Entity *witch = nullptr;

// Function Declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Animation / Entities");

    std::map<WitchState, std::vector<int>> animationAtlas = {
        {IDLE,        {  0, 1, 2, 3, 4, 5       }},
        {POWERING_UP, {  0, 1, 2, 3, 4, 5, 6, 7 }}
    };

    // Assets from @see https://9e0.itch.io/witches-pack
    witch = new Entity(
        ORIGIN,                       // position
        { 250.0f, 250.0f },           // scale
        {
            "assets/game/idle.png",
            "assets/game/attack.png"
        },                            // texture file addresses
        ATLAS,                        // single image or atlas?
        { 6, 1 },                     // atlas dimensions
        animationAtlas                // actual atlas
    );

    SetTargetFPS(FPS);
}

void processInput() 
{
    if (IsKeyPressed(KEY_Q) || WindowShouldClose()) gAppStatus = TERMINATED;
}

void update() 
{
    // Delta time
    float ticks = (float) GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks  = ticks;

    // we're not checking collisions—for now
    witch->update(deltaTime);
}

void render()
{
    BeginDrawing();
    ClearBackground(ColorFromHex(BG_COLOUR));

    witch->render();

    EndDrawing();
}

void shutdown() 
{ 
    CloseWindow();
    
}

int main(void)
{
    initialise();

    while (gAppStatus == RUNNING)
    {
        processInput();
        update();
        render();
    }

    shutdown();

    return 0;
}