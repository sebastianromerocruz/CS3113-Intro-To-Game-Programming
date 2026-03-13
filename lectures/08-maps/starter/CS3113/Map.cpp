#include "Map.h"

Map::Map(int mapColumns, int mapRows, unsigned int *levelData,
         const char *textureFilePath, float tileSize, int textureColumns,
         int textureRows, Vector2 origin) :
         mMapColumns {mapColumns}, mMapRows {mapRows},
         mTextureAtlas { LoadTexture(textureFilePath) },
         mLevelData {levelData }, mTileSize {tileSize},
         mTextureColumns {textureColumns}, mTextureRows {textureRows},
         mOrigin {origin} { build(); }

Map::~Map() { UnloadTexture(mTextureAtlas); }

void Map::build()
{
    // Calculate map boundaries in world coordinates
    mLeftBoundary   = mOrigin.x - (mMapColumns * mTileSize) / 2.0f;
    mRightBoundary  = mOrigin.x + (mMapColumns * mTileSize) / 2.0f;
    mTopBoundary    = mOrigin.y - (mMapRows * mTileSize) / 2.0f;
    mBottomBoundary = mOrigin.y + (mMapRows * mTileSize) / 2.0f;

    // Precompute texture areas for each tile
    for (int row = 0; row < mTextureRows; row++)
    {
        for (int col = 0; col < mTextureColumns; col++)
        {
            Rectangle textureArea = {
                (float) col * (mTextureAtlas.width / mTextureColumns),
                (float) row * (mTextureAtlas.height / mTextureRows),
                (float) mTextureAtlas.width / mTextureColumns,
                (float) mTextureAtlas.height / mTextureRows
            };

            mTextureAreas.push_back(textureArea);
        }
    }
}

void Map::render()
{
    // Draw each tile in the map
    for (int row = 0; row < mMapRows; row++)
    {
        // Draw each column in the row
        for (int col = 0; col < mMapColumns; col++)
        {
            // Get the tile index at the current row and column
            int tile = mLevelData[row * mMapColumns + col];

            // If the tile index is 0, we do not draw anything
            if (tile == 0) continue;

            Rectangle destinationArea = {
                mLeftBoundary + col * mTileSize,
                mTopBoundary  + row * mTileSize,
                mTileSize,
                mTileSize
            };

            // Draw the tile
            DrawTexturePro(
                mTextureAtlas,
                mTextureAreas[tile - 1], // -1 because tile indices start at 1
                destinationArea,
                {0.0f, 0.0f}, // origin
                0.0f,         // rotation
                WHITE         // tint
            );
        }
    }
}

bool Map::isSolidTileAt(Vector2 position, float *xOverlap, float *yOverlap)
{
    *xOverlap = 0.0f;
    *yOverlap = 0.0f;

    if (position.x < mLeftBoundary || position.x > mRightBoundary ||
        position.y < mTopBoundary  || position.y > mBottomBoundary)
        return false;

    int tileXIndex = floor((position.x - mLeftBoundary) / mTileSize);
    int tileYIndex = floor((position.y - mTopBoundary) / mTileSize);

    if (tileXIndex < 0 || tileXIndex >= mMapColumns ||
        tileYIndex < 0 || tileYIndex >= mMapRows)
        return false;

    int tile = mLevelData[tileYIndex * mMapColumns + tileXIndex];
    if (tile == 0) return false;

    float tileCentreX = mLeftBoundary + tileXIndex * mTileSize + mTileSize / 2.0f;
    float tileCentreY = mTopBoundary + tileYIndex * mTileSize + mTileSize / 2.0f;

    *xOverlap = fmaxf(0.0f, (mTileSize / 2.0f) - fabs(position.x - tileCentreX));
    *yOverlap = fmaxf(0.0f, (mTileSize / 2.0f) - fabs(position.y - tileCentreY));

    return true;
}
