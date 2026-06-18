#include "Scene.h"

Scene::Scene() : mOrigin{{}} {}

Scene::Scene(Vector2 origin, const char *bgHexCode) : mOrigin{origin}, mBGColourHexCode {bgHexCode} 
{
    ClearBackground(ColorFromHex(bgHexCode));
}