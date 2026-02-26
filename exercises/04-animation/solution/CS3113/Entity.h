#ifndef ENTITY_H
#define ENTITY_H

#include "cs3113.h"

enum Direction  { LEFT, UP, RIGHT, DOWN }; // For walking
enum WitchState { IDLE, POWERING_UP     };

class Entity
{
private:
    Vector2 mPosition;
    Vector2 mMovement;

    Vector2 mScale;
    Vector2 mColliderDimensions;
    
    std::map<WitchState, Texture2D> mTextures;
    Texture2D mCurrentTexture;
    TextureType mTextureType;
    Vector2 mSpriteSheetDimensions;
    
    std::map<WitchState, std::vector<int>> mAnimationAtlas;
    std::vector<int> mAnimationIndices;
    Direction mDirection;
    WitchState mWitchStatus;
    int mFrameSpeed;

    int mCurrentFrameIndex = 0;
    float mAnimationTime = 0.0f;

    int mSpeed;
    float mAngle;

    bool isColliding(Entity *other) const;
    void animate(float deltaTime);

public:
    static const int DEFAULT_SIZE        = 250;
    static const int DEFAULT_SPEED       = 200;
    static const int DEFAULT_FRAME_SPEED = 8;
    static const int IDLE_ROWS           = 6;
    static const int POWERING_UP_ROWS    = 8;

    Entity();;
    Entity(Vector2 position, Vector2 scale, std::vector<const char*> textureFilepaths, 
        TextureType textureType, Vector2 spriteSheetDimensions, 
        std::map<WitchState, std::vector<int>> animationAtlas);
    ~Entity();

    void update(float deltaTime);
    void render();
    void normaliseMovement() { Normalise(&mMovement); };
    void triggerPowerUp();

    // void moveUp()    { mMovement.y = -1; mDirection = UP;    }
    // void moveDown()  { mMovement.y =  1; mDirection = DOWN;  }
    // void moveLeft()  { mMovement.x = -1; mDirection = LEFT;  }
    // void moveRight() { mMovement.x =  1; mDirection = RIGHT; }

    void resetMovement() { mMovement = { 0.0f, 0.0f }; }

    Vector2     getPosition()              const { return mPosition;              }
    Vector2     getMovement()              const { return mMovement;              }
    Vector2     getScale()                 const { return mScale;                 }
    Vector2     getColliderDimensions()    const { return mScale;                 }
    Vector2     getSpriteSheetDimensions() const { return mSpriteSheetDimensions; }
    std::map<WitchState, Texture2D> getTextures()        const { return mTextures;         }
    TextureType getTextureType()           const { return mTextureType;           }
    // Direction   getDirection()             const { return mDirection;             }
    int         getFrameSpeed()            const { return mFrameSpeed;            }
    int         getSpeed()                 const { return mSpeed;                 }
    float       getAngle()                 const { return mAngle;                 }


    std::map<WitchState, std::vector<int>> getAnimationAtlas() const { return mAnimationAtlas; }

    void setPosition(Vector2 newPosition)
        { mPosition = newPosition;                }
    void setMovement(Vector2 newMovement)
        { mMovement = newMovement;                }
    void setScale(Vector2 newScale)
        { mScale = newScale;                      }
    void setColliderDimensions(Vector2 newDimensions) 
        { mColliderDimensions = newDimensions;    }
    void setSpriteSheetDimensions(Vector2 newDimensions) 
        { mSpriteSheetDimensions = newDimensions; }
    void setSpeed(int newSpeed)
        { mSpeed  = newSpeed;                     }
    void setFrameSpeed(int newSpeed)
        { mFrameSpeed = newSpeed;                 }
    void setAngle(float newAngle) 
        { mAngle = newAngle;                      }
};

#endif // ENTITY_H