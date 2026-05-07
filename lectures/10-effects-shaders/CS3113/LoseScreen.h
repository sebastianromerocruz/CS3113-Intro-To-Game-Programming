#ifndef LOSESCREEN_H
#define LOSESCREEN_H

#include "WinScreen.h"

class LoseScreen : public Scene
{
public:
    LoseScreen();
    LoseScreen(Vector2 origin, const char *bgHexCode);
    ~LoseScreen();

    void initialise() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;
};

#endif
