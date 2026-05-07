#include "WinScreen.h"

WinScreen::WinScreen() : Scene{{0.0f}, nullptr} { mIsGameplay = false; }
WinScreen::WinScreen(Vector2 origin, const char *bgHexCode) : Scene{origin, bgHexCode}
{ mIsGameplay = false; }
WinScreen::~WinScreen() {}

void WinScreen::initialise()
{
    mGameState.nextSceneID = -1;
    mGameState.player = nullptr;
    mGameState.enemies = nullptr;
    mGameState.pickups = nullptr;
    mGameState.enemyCount = 0;
    mGameState.pickupCount = 0;
    mGameState.map = nullptr;
}

void WinScreen::update(float deltaTime)
{
    if (IsKeyPressed(KEY_ENTER))
        mGameState.nextSceneID = 0;
}

void WinScreen::render()
{
    ClearBackground(ColorFromHex("#0f3d0f"));

    const char *text = "YOU WIN!";
    int w = MeasureText(text, 100);
    DrawText(text, (int)mOrigin.x - w / 2, (int)mOrigin.y - 100, 100, GOLD);

    const char *sub = "You survived Highway Rush!";
    int sw = MeasureText(sub, 30);
    DrawText(sub, (int)mOrigin.x - sw / 2, (int)mOrigin.y + 30, 30, RAYWHITE);

    const char *sub2 = "Press ENTER to return to Menu";
    int sw2 = MeasureText(sub2, 24);
    DrawText(sub2, (int)mOrigin.x - sw2 / 2, (int)mOrigin.y + 90, 24, LIGHTGRAY);
}

void WinScreen::shutdown() {}
