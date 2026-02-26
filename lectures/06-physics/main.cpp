#include "CS3113/Entity.h"

// Global Constants
constexpr int SCREEN_WIDTH  = 1000,
              SCREEN_HEIGHT = 600,
              FPS           = 120;

constexpr char BG_COLOUR[]    = "#C0897E";
constexpr Vector2 ORIGIN      = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

constexpr int   NUMBER_OF_TILES         = 10;
constexpr float TILE_DIMENSION          = 50.0f,
                // in m/ms², since delta time is in ms
                ACCELERATION_OF_GRAVITY = 981.0f,
                FIXED_TIMESTEP          = 1.0f / 60.0f;

// Global Variables
AppStatus gAppStatus   = RUNNING;
float gPreviousTicks   = 0.0f,
      gTimeAccumulator = 0.0f;

Entity *gXochitl = nullptr;
Entity *gTiles  = nullptr;

// Function Declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Physics");

    /*
        ----------- PROTAGONIST -----------
    */
    std::map<Direction, std::vector<int>> animationAtlas = {
        {DOWN,  {  0,  1,  2,  3,  4,  5,  6,  7 }},
        {LEFT,  {  8,  9, 10, 11, 12, 13, 14, 15 }},
        {UP,    { 24, 25, 26, 27, 28, 29, 30, 31 }},
        {RIGHT, { 40, 41, 42, 43, 44, 45, 46, 47 }},
    };

    float sizeRatio  = 48.0f / 64.0f;

    // Assets from @see https://sscary.itch.io/the-adventurer-female
    gXochitl = new Entity(
        {ORIGIN.x, ORIGIN.y - 200.0f}, // position
        {250.0f * sizeRatio, 250.0f},  // scale
        "assets/game/walk.png",        // texture file address
        ATLAS,                         // single image or atlas?
        { 6, 8 },                      // atlas dimensions
        animationAtlas                 // actual atlas
    );

    gXochitl->setJumpingPower(400.0f);
    gXochitl->setColliderDimensions({
        gXochitl->getScale().x / 3.0f,
        gXochitl->getScale().y / 3.0f
    });
    gXochitl->setAcceleration({0.0f, ACCELERATION_OF_GRAVITY});

    /*
        ----------- TILES -----------
    */
    gTiles = new Entity[NUMBER_OF_TILES];

    // Compute the left‑most x coordinate so that the entire row is centred
    float leftMostX = ORIGIN.x - (NUMBER_OF_TILES * TILE_DIMENSION) / 2.0f;

    for (int i = 0; i < NUMBER_OF_TILES - 1; i++) 
    {
        // assets from @see https://kenney.nl/assets/pixel-platformer-industrial-expansion
        gTiles[i].setTexture("assets/game/tile_0000.png");
        gTiles[i].setScale({TILE_DIMENSION, TILE_DIMENSION});
        gTiles[i].setColliderDimensions({TILE_DIMENSION, TILE_DIMENSION});
        gTiles[i].setPosition({
            leftMostX + i * TILE_DIMENSION, 
            ORIGIN.y + TILE_DIMENSION
        });
    }

    // Allocate the tile for the horizontal collision
    gTiles[NUMBER_OF_TILES - 1].setTexture("assets/game/tile_0000.png");
    gTiles[NUMBER_OF_TILES - 1].setScale({TILE_DIMENSION, TILE_DIMENSION});
    gTiles[NUMBER_OF_TILES - 1].setColliderDimensions({TILE_DIMENSION, TILE_DIMENSION});
    gTiles[NUMBER_OF_TILES - 1].setPosition({ORIGIN.y + TILE_DIMENSION, ORIGIN.y - TILE_DIMENSION});

    SetTargetFPS(FPS);
}

void processInput() 
{
    gXochitl->resetMovement();

    if      (IsKeyDown(KEY_A)) gXochitl->moveLeft();
    else if (IsKeyDown(KEY_D)) gXochitl->moveRight();

    if (IsKeyPressed(KEY_W) && gXochitl->isCollidingBottom()) gXochitl->jump();

    // to avoid faster diagonal speed
    if (GetLength(gXochitl->getMovement()) > 1.0f) 
        gXochitl->normaliseMovement();

    if (IsKeyPressed(KEY_Q) || WindowShouldClose()) gAppStatus = TERMINATED;
}

void update() 
{
    // Delta time
    float ticks = (float) GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks  = ticks;

    // Fixed timestep
    deltaTime += gTimeAccumulator;

    if (deltaTime < FIXED_TIMESTEP)
    {
        gTimeAccumulator = deltaTime;
        return;
    }

    while (deltaTime >= FIXED_TIMESTEP)
    {
        gXochitl->update(FIXED_TIMESTEP, gTiles, NUMBER_OF_TILES);

        for (int i = 0; i < NUMBER_OF_TILES; i++) 
            gTiles[i].update(FIXED_TIMESTEP, nullptr, 0);

        deltaTime -= FIXED_TIMESTEP;
    }
}

void render()
{
    BeginDrawing();
    ClearBackground(ColorFromHex(BG_COLOUR));

    gXochitl->render();

    for (int i = 0; i < NUMBER_OF_TILES; i++) gTiles[i].render();

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