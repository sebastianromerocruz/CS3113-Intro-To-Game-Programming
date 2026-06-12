#include "Map.h"

Map::Map(
    int           mapColumns,
    int           mapRows,
    unsigned int *levelData,
    const char   *textureFilePath,
    float         tileSize,
    int           textureColumns,
    int           textureRows,
    Vector2       origin
)
    : mMapColumns{ mapColumns }, mMapRows{ mapRows },
      mTextureAtlas{ LoadTexture(textureFilePath) }, mLevelData{ levelData },
      mTileSize{ tileSize }, mTextureColumns{ textureColumns },
      mTextureRows{ textureRows }, mOrigin{ origin }
{
    build();
}

Map::~Map()
{
    UnloadTexture(mTextureAtlas);
}

void Map::build()
{
}

void Map::render()
{
}

bool Map::isSolidTileAt(Vector2 position, float *xOverlap, float *yOverlap)
{
    return false;
}
