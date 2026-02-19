#include "CS3113/animation/cs3113.h"

// Global Constants
constexpr int SCREEN_WIDTH  = 1600 / 2,
              SCREEN_HEIGHT = 900 / 2,
              FPS           = 120,
              SIZE          = 500 / 2,
              SPEED         = 200,

              FRAMES_PER_SECOND = 14;

constexpr float SIZE_RATIO  = 48.0f / 64.0f;

constexpr char    BG_COLOUR[] = "#404F59";
constexpr Vector2 ORIGIN      = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 },
                  BASE_SIZE   = { (float) SIZE * SIZE_RATIO, (float) SIZE },
                  SPRITESHEET_DIMENSIONS = { 8, 6 };

constexpr TextureType TEXTURE_TYPE = ATLAS;

const std::map<Direction, std::vector<int>> ANIMATION_ATLAS = {
    {DOWN,  {  0,  1,  2,  3,  4,  5,  6,  7 }},
    {LEFT,  {  8,  9, 10, 11, 12, 13, 14, 15 }},
    {UP,    { 24, 25, 26, 27, 28, 29, 30, 31 }},
    {RIGHT, { 40, 41, 42, 43, 44, 45, 46, 47 }},
};

// Assets from @see https://sscary.itch.io/the-adventurer-female
constexpr char PROTAG_FILEPATH[] = "assets/game/walk.png";

// Global Variables
AppStatus gAppStatus     = RUNNING;
float     gAngle         = 0.0f,
          gPreviousTicks = 0.0f,
          
          gAnimationTime = 0.0f;

Vector2 gPosition  = ORIGIN,
        gMovement  = { 0.0f, 0.0f },
        gScale     = BASE_SIZE;

Texture2D gTexture;

int gAnimationIndex = 0;

Direction        gWalkingDirection = DOWN;
std::vector<int> gAnimationIndices = ANIMATION_ATLAS.at(gWalkingDirection);

// Function Declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();
Rectangle getUVRectangle(const Texture2D *texture, int index, int rows, 
    int cols);
bool isColliding(const Vector2 *positionA, const Vector2 *scaleA, 
    const Vector2 *positionB, const Vector2 *scaleB);

/**
 * @brief Calculates and returns the UV coordinates and dimensions of a 
 * rectangle slice from a texture based on the given index, number of rows, and
 * number of columns.
 * 
 * @param texture a pointer to a `Texture2D` struct, contains information about
 * a 2D texture such as its width and height.
 * @param index represents the index of the specific slice within a texture 
 * atlas. Each slice is a sub-image within the texture atlas that contains 
 * multiple images arranged in rows and columns.
 * @param rows represents the number of rows in which the texture is divided.
 * This parameter is used to calculate the vertical position of the texture 
 * slice based on the index provided.
 * @param cols represents the number of columns in a grid layout. It is used in
 * the `getUVRectangle` function to calculate the UV coordinates for a specific
 * index within the grid.
 * 
 * @return a `Rectangle` struct that represents a portion of a texture based on
 * the provided parameters. The `Rectangle` struct contains the top-left 
 * x-coordinate, top-left y-coordinate, width, and height of the specified
 * portion of the texture.
 */
Rectangle getUVRectangle(const Texture2D *texture, int index, int rows, int cols)
{
    float uCoord = (float) (index % cols) / (float) cols;
    uCoord *= texture->width;

    float vCoord = (float) (index / cols) / (float) rows;
    vCoord *= texture->height;

    float sliceWidth  = texture->width  / (float) cols;
    float sliceHeight = texture->height / (float) rows;

    // printf("Rectangle { %.2f, %.2f, %.2f, %.2f }\n", 
    //     uCoord, 
    //     vCoord, 
    //     sliceWidth, 
    //     sliceHeight
    // );

    return { 
        uCoord,     // top-left x-coord
        vCoord,     // top-left y-coord
        sliceWidth, // width of slice
        sliceHeight // height of slice
    };
}

/**
 * @brief Checks for a square collision between 2 Rectangle objects.
 * 
 * @see 
 * 
 * @param positionA The position of the first object
 * @param scaleA The scale of the first object
 * @param positionB The position of the second object
 * @param scaleB The scale of the second object
 * @return true if a collision is detected,
 * @return false if a collision is not detected
 */
bool isColliding(const Vector2 *positionA,  const Vector2 *scaleA, 
                 const Vector2 *positionB, const Vector2 *scaleB)
{
    float xDistance = fabs(positionA->x - positionB->x) - ((scaleA->x + scaleB->x) / 2.0f);
    float yDistance = fabs(positionA->y - positionB->y) - ((scaleA->y + scaleB->y) / 2.0f);

    if (xDistance < 0.0f && yDistance < 0.0f) return true;

    return false;
}

/**
 * Renders a texture on screen with specified position, scale, and texture type.
 * 
 * @param texture pointer to a `Texture2D` struct, which contains information
 * about a 2D texture, such as its width, height, and pixel data. This struct 
 * is used to represent textures in 2D graphics rendering.
 * @param position the position at which the object will be rendered on the 
 * screen. It is a pointer to a `Vector2` struct that contains the x and y 
 * coordinates of the position. The object will be centered at these 
 * coordinates on the screen.
 * @param scale the scaling factor to be applied to the rendered object.
 * @param textureType an enum type that specifies the type of texture being
 * rendered. It can have two possible values:
 *      - SINGLE: for objects not using a texture-atlas
 *      - ATLAS:  for ebjects using a texture atlas
 */
void renderObject(const Texture2D *texture, const Vector2 *position, 
                  const Vector2 *scale, TextureType textureType)
{
    Rectangle textureArea;

    switch (textureType)
    {
        case SINGLE:
            // Whole texture (UV coordinates)
            textureArea = {
                // top-left corner
                0.0f, 0.0f,

                // bottom-right corner (of texture)
                static_cast<float>(texture->width),
                static_cast<float>(texture->height)
            };
            break;
        case ATLAS:
            textureArea = getUVRectangle(
                texture, 
                gAnimationIndices[gAnimationIndex], 
                6, 8
            );
            break;
        default: break;
    }

    // Destination rectangle – centred on gPosition
    Rectangle destinationArea = {
        position->x,
        position->y,
        static_cast<float>(scale->x),
        static_cast<float>(scale->y)
    };

    // Origin inside the source texture (centre of the texture)
    Vector2 originOffset = {
        static_cast<float>(scale->x) / 2.0f,
        static_cast<float>(scale->y) / 2.0f
    };

    // Render the texture on screen
    DrawTexturePro(
        *texture, 
        textureArea, destinationArea, originOffset,
        gAngle, WHITE
    );
}

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Animation (Atlas)");

    gTexture  = LoadTexture(PROTAG_FILEPATH);

    SetTargetFPS(FPS);
}

void processInput() 
{
    gMovement = { 0.0f, 0.0f };

    if (IsKeyDown(KEY_A)) 
    {
        gMovement.x = -1;
        gWalkingDirection = LEFT;
    }
    else if (IsKeyDown(KEY_D)) 
    {
        gMovement.x =  1;
        gWalkingDirection = RIGHT;
    }
    if (IsKeyDown(KEY_W)) 
    {
        gMovement.y = -1;
        gWalkingDirection = UP;
    }
    else if (IsKeyDown(KEY_S)) 
    {
        gMovement.y =  1;
        gWalkingDirection = DOWN;
    }

    // to avoid faster diagonal speed
    if (GetLength(&gMovement) > 1.0f) Normalise(&gMovement);

    if (IsKeyPressed(KEY_Q) || WindowShouldClose()) gAppStatus = TERMINATED;
}

void update() 
{
    // Delta time
    float ticks = (float) GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks  = ticks;

    gAnimationIndices = ANIMATION_ATLAS.at(gWalkingDirection);

    gPosition = {
        gPosition.x + SPEED * gMovement.x * deltaTime,
        gPosition.y + SPEED * gMovement.y * deltaTime
    };

    if (GetLength(&gMovement) != 0)
    {
        gAnimationTime += deltaTime;
        float secondsPerFrame = 1.0f / FRAMES_PER_SECOND;

        if (gAnimationTime >= secondsPerFrame)
        {
            gAnimationTime = 0.0f;

            gAnimationIndex++;
            gAnimationIndex %= gAnimationIndices.size();
        }
    }
}

void render()
{
    BeginDrawing();
    ClearBackground(ColorFromHex(BG_COLOUR));

    renderObject(&gTexture, &gPosition, &gScale, TEXTURE_TYPE);

    EndDrawing();
}

void shutdown() 
{ 
    CloseWindow();
    UnloadTexture(gTexture);
}

int main(void)
{
    initialise();

    while (gAppStatus == RUNNING)
    {
        processInput();
        update();
        render();
    }

    shutdown();

    return 0;
}