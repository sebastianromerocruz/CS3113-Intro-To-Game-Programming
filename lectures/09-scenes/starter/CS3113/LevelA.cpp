#include "LevelA.h"

LevelA::LevelA()                                      : Scene { {0.0f}, nullptr   } {}
LevelA::LevelA(Vector2 origin, const char *bgHexCode) : Scene { origin, bgHexCode } {}

LevelA::~LevelA() { shutdown(); }

void LevelA::initialise()
{
    mGameState.nextSceneID = 0;

    // TODO: Load background music and jump sound

    // TODO: Create the map using mLevelData, LEVEL_WIDTH, LEVEL_HEIGHT, TILE_DIMENSION, and mOrigin

    // TODO: Create the player entity (Xochitl) with animation atlas, scale, jumping power,
    //       collider dimensions, and gravity acceleration
}

void LevelA::update(float deltaTime)
{
    // TODO: Update music stream

    // TODO: Update the player entity (pass deltaTime, nullptr player, mGameState.map, nullptr entities, 0)

    // TODO: Trigger scene switch to level 1 (LevelB) if player falls below END_GAME_THRESHOLD
    //       i.e. set mGameState.nextSceneID = 1;
}

void LevelA::render()
{
    ClearBackground(ColorFromHex(mBGColourHexCode));

    // TODO: Render the player entity and map
}

void LevelA::shutdown()
{
    // TODO: delete mGameState.xochitl and mGameState.map, then unload bgm and jumpSound
}
