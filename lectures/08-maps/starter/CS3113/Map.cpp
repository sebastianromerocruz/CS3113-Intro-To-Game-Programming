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
    : mMapColumns{ mapColumns }, mMapRows{ mapRows }, mLevelData{ levelData },
      mTextureAtlas{ LoadTexture(textureFilePath) }, mTileSize{ tileSize },
      mTextureColumns{ textureColumns }, mTextureRows{ textureRows },
      mOrigin{ origin }
{
    build();
}

Map::~Map()
{
    UnloadTexture(mTextureAtlas);
}

void Map::build()
{
    // TODO: Compute the map's boundaries in world coordinates, then
    //       precompute the texture area (Rectangle) of every tile in the atlas
    //       and store them in mTextureAreas.
}

void Map::render()
{
    // TODO: Draw every non-empty tile of the map. A tile index of 0 means
    //       "draw nothing".
}

bool Map::isSolidTileAt(Vector2 position, float *xOverlap, float *yOverlap)
{
    // TODO: Return true if the tile at `position` is solid, and write how far
    //       `position` has penetrated into that tile to xOverlap and yOverlap.
    return false;
}
