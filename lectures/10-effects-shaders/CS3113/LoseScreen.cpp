#include "LoseScreen.h"

LoseScreen::LoseScreen() : Scene{{0.0f}, nullptr} { mIsGameplay = false; }
LoseScreen::LoseScreen(Vector2 origin, const char *bgHexCode) : Scene{origin, bgHexCode}
{ mIsGameplay = false; }
LoseScreen::~LoseScreen() {}

void LoseScreen::initialise()
{
    mGameState.nextSceneID = -1;
    mGameState.player = nullptr;
    mGameState.enemies = nullptr;
    mGameState.pickups = nullptr;
    mGameState.enemyCount = 0;
    mGameState.pickupCount = 0;
    mGameState.map = nullptr;
}

void LoseScreen::update(float deltaTime)
{
    if (IsKeyPressed(KEY_ENTER))
        mGameState.nextSceneID = 0;
}

void LoseScreen::render()
{
    ClearBackground(ColorFromHex("#3d0f0f"));

    const char *text = "GAME OVER";
    int w = MeasureText(text, 90);
    DrawText(text, (int)mOrigin.x - w / 2, (int)mOrigin.y - 100, 90, RED);

    const char *sub = "You crashed!";
    int sw = MeasureText(sub, 30);
    DrawText(sub, (int)mOrigin.x - sw / 2, (int)mOrigin.y + 30, 30, RAYWHITE);

    const char *sub2 = "Press ENTER to return to Menu";
    int sw2 = MeasureText(sub2, 24);
    DrawText(sub2, (int)mOrigin.x - sw2 / 2, (int)mOrigin.y + 90, 24, LIGHTGRAY);
}

void LoseScreen::shutdown() {}
