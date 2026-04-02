#include "cs3113.h"

Color ColorFromHex(const char *hex)
{
    // Skip leading '#', if present
    if (hex[0] == '#') hex++;

    // Default alpha = 255 (opaque)
    unsigned int r = 0, 
                 g = 0, 
                 b = 0, 
                 a = 255;

    // 6‑digit form: RRGGBB
    if (sscanf(hex, "%02x%02x%02x", &r, &g, &b) == 3) {
        return (Color){ (unsigned char) r,
                        (unsigned char) g,
                        (unsigned char) b,
                        (unsigned char) a };
    }

    // 8‑digit form: RRGGBBAA
    if (sscanf(hex, "%02x%02x%02x%02x", &r, &g, &b, &a) == 4) {
        return (Color){ (unsigned char) r,
                        (unsigned char) g,
                        (unsigned char) b,
                        (unsigned char) a };
    }

    // Fallback – return white so you notice something went wrong
    return RAYWHITE;
}

/**
 * @brief Calculates and returns the magnitude of a 2D vector.
 * 
 * @param vector Any 2D raylib vector.
 */
float GetLength(const Vector2 vector)
{
    return sqrtf(
        pow(vector.x, 2) + pow(vector.y, 2)
    );
}

/**
 * @brief Mutates two dimensional vector to become its unit vector counterpart,
 * also known as a direction vector, retains the original vector’s orientation
 * but has a standardised length.
 * 
 * @see https://hogonext.com/how-to-normalize-a-vector/
 * 
 * @param vector Any 2D raylib vector.
 */
void Normalise(Vector2 *vector)
{
    float magnitude = GetLength(*vector);

    vector->x /= magnitude;
    vector->y /= magnitude;
}

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

    return { 
        uCoord,     // top-left x-coord
        vCoord,     // top-left y-coord
        sliceWidth, // width of slice
        sliceHeight // height of slice
    };
}

/**
 * The function `panCamera` smoothly adjusts the camera's target position towards a specified target
 * position.
 * 
 * @param camera The `camera` parameter is a pointer to a `Camera2D` struct, which likely contains
 * information about a 2D camera such as its position, target, zoom level, and other properties.
 * @param targetPosition The `targetPosition` parameter is a pointer to a `Vector2` structure that
 * represents the desired position where the camera should be focused or centered on.
 */
void panCamera(Camera2D *camera, const Vector2 *targetPosition)
{
    Vector2 positionDifference = Vector2Subtract(
        *targetPosition, 
        camera->target
    );

    camera->target = Vector2Add(
        camera->target, 
        Vector2Scale(positionDifference, 0.1f)
    ); // 0.1 = smoothing factor
}