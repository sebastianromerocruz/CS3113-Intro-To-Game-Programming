#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "Scene.h"

class MenuScreen : public Scene
{
public:
    MenuScreen();
    MenuScreen(Vector2 origin, const char *bgHexCode);
    ~MenuScreen();

    void initialise() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;
};

#endif
