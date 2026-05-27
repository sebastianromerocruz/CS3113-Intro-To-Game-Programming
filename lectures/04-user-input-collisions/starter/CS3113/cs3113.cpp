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
float GetLength(const Vector2 *vector)
{
    return sqrtf(
        pow(vector->x, 2) + pow(vector->y, 2)
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
    float magnitude = GetLength(vector);

    vector->x /= magnitude;
    vector->y /= magnitude;
}