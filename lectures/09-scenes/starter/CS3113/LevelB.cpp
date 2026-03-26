#include "LevelB.h"

LevelB::LevelB()                                      : Scene { {0.0f}, nullptr   } {}
LevelB::LevelB(Vector2 origin, const char *bgHexCode) : Scene { origin, bgHexCode } {}

LevelB::~LevelB() { shutdown(); }

void LevelB::initialise()
{
    // TODO: Load background music and jump sound

    // TODO: Create the map using mLevelData, LEVEL_WIDTH, LEVEL_HEIGHT, TILE_DIMENSION, and mOrigin

    // TODO: Create the player entity (Xochitl) with animation atlas, scale, jumping power,
    //       collider dimensions, and gravity acceleration
}

void LevelB::update(float deltaTime)
{
    // TODO: Update music stream

    // TODO: Update the player entity (pass deltaTime, nullptr player, mGameState.map, nullptr entities, 0)
}

void LevelB::render()
{
    ClearBackground(ColorFromHex(mBGColourHexCode));

    // TODO: Render the player entity and map
}

void LevelB::shutdown()
{
    // TODO: delete mGameState.xochitl and mGameState.map, then unload bgm and jumpSound
}
