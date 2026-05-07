#ifndef WINSCREEN_H
#define WINSCREEN_H

#include "MenuScreen.h"

class WinScreen : public Scene
{
public:
    WinScreen();
    WinScreen(Vector2 origin, const char *bgHexCode);
    ~WinScreen();

    void initialise() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;
};

#endif
