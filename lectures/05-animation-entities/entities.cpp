#include "CS3113/entities/Entity.h"

// Global Constants
constexpr int SCREEN_WIDTH  = 1600 / 2,
              SCREEN_HEIGHT = 900 / 2,
              FPS           = 120;

constexpr char    BG_COLOUR[] = "#404F59";
constexpr Vector2 ORIGIN      = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

// Global Variables
AppStatus gAppStatus = RUNNING;
float gPreviousTicks = 0.0f;

Entity *gProtag = nullptr;

// Function Declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Animation / Entities");

    std::map<Direction, std::vector<int>> animationAtlas = {
        {DOWN,  {  0,  1,  2,  3,  4,  5,  6,  7 }},
        {LEFT,  {  8,  9, 10, 11, 12, 13, 14, 15 }},
        {UP,    { 24, 25, 26, 27, 28, 29, 30, 31 }},
        {RIGHT, { 40, 41, 42, 43, 44, 45, 46, 47 }},
    };

    float sizeRatio  = 48.0f / 64.0f;

    /*
    By default, the colliders of our entity object will have the same
    dimensions as the entity's scale.

    Assets from @see https://sscary.itch.io/the-adventurer-female
    */
    gProtag = new Entity(
        ORIGIN,                       // position
        {250.0f * sizeRatio, 250.0f}, // scale
        "assets/game/walk.png",       // texture file address
        ATLAS,                        // single image or atlas?
        { 6, 8 },                     // atlas dimensions
        animationAtlas                // actual atlas
    );

    SetTargetFPS(FPS);
}

void processInput() 
{
    gProtag->resetMovement();

    if      (IsKeyDown(KEY_A)) gProtag->moveLeft();
    else if (IsKeyDown(KEY_D)) gProtag->moveRight();
    if      (IsKeyDown(KEY_W)) gProtag->moveUp();
    else if (IsKeyDown(KEY_S)) gProtag->moveDown();

    // to avoid faster diagonal speed
    if (GetLength(gProtag->getMovement()) > 1.0f) 
        gProtag->normaliseMovement();

    if (IsKeyPressed(KEY_Q) || WindowShouldClose()) gAppStatus = TERMINATED;
}

void update() 
{
    // Delta time
    float ticks = (float) GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks  = ticks;

    // we're not checking collisions—for now
    gProtag->update(deltaTime);
}

void render()
{
    BeginDrawing();
    ClearBackground(ColorFromHex(BG_COLOUR));

    gProtag->render();

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