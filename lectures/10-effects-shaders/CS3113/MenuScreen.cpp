#include "MenuScreen.h"

MenuScreen::MenuScreen() : Scene{{0.0f}, nullptr} { mIsGameplay = false; }
MenuScreen::MenuScreen(Vector2 origin, const char *bgHexCode) : Scene{origin, bgHexCode}
{ mIsGameplay = false; }
MenuScreen::~MenuScreen() {}

void MenuScreen::initialise()
{
    mGameState.nextSceneID = -1;
    mGameState.player = nullptr;
    mGameState.enemies = nullptr;
    mGameState.pickups = nullptr;
    mGameState.enemyCount = 0;
    mGameState.pickupCount = 0;
    mGameState.map = nullptr;
}

void MenuScreen::update(float deltaTime)
{
    if (IsKeyPressed(KEY_ENTER))
        mGameState.nextSceneID = 1;
}

void MenuScreen::render()
{
    ClearBackground(ColorFromHex("#1a1a2e"));

    const char *title = "HIGHWAY RUSH";
    int tw = MeasureText(title, 90);
    DrawText(title, (int)mOrigin.x - tw / 2, 100, 90, GOLD);

    const char *sub = "Press ENTER to start";
    int sw = MeasureText(sub, 32);
    DrawText(sub, (int)mOrigin.x - sw / 2, 240, 32, RAYWHITE);

    int instrY = 330;
    int lineH = 32;

    const char *i1 = "INSTRUCTIONS:";
    int i1w = MeasureText(i1, 28);
    DrawText(i1, (int)mOrigin.x - i1w / 2, instrY, 28, YELLOW);

    const char *i2 = "A / D  -  Steer left and right";
    int i2w = MeasureText(i2, 24);
    DrawText(i2, (int)mOrigin.x - i2w / 2, instrY + lineH + 10, 24, LIGHTGRAY);

    const char *i3 = "W / S  -  Accelerate / Brake";
    int i3w = MeasureText(i3, 24);
    DrawText(i3, (int)mOrigin.x - i3w / 2, instrY + lineH * 2 + 10, 24, LIGHTGRAY);

    const char *i4 = "Avoid other cars! Grab hearts for extra lives.";
    int i4w = MeasureText(i4, 22);
    DrawText(i4, (int)mOrigin.x - i4w / 2, instrY + lineH * 3 + 20, 22, LIGHTGRAY);

    const char *i5 = "Survive all three levels to win.";
    int i5w = MeasureText(i5, 22);
    DrawText(i5, (int)mOrigin.x - i5w / 2, instrY + lineH * 4 + 20, 22, LIGHTGRAY);
}

void MenuScreen::shutdown() {}
