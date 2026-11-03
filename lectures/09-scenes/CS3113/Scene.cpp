#include "Scene.h"

Scene::Scene() : mGameState{}, mOrigin{} {}

Scene::Scene(Vector2 origin, const char *bgHexCode)
    : mGameState{}, mOrigin{ origin }, mBGColourHexCode{ bgHexCode }
{}
