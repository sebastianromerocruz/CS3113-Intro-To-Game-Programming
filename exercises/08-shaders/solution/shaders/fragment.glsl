#version 330

const float RED_LUM_CONSTANT   = 0.2126;
const float GREEN_LUM_CONSTANT = 0.7152;
const float BLUE_LUM_CONSTANT  = 0.0722;
const float LINEAR_TERM        = 0.0005;  // linear term
const float QUADRATIC_TERM     = 0.00009; // quadratic term
const float MIN_BRIGHTNESS     = 0.05;    // avoid total darkness

uniform sampler2D texture0;
uniform vec2 lightPosition;
uniform int isCharging;

in vec2 fragTexCoord;
in vec2 fragPosition;

out vec4 finalColor;

float attenuate(float distance, float linearTerm, float quadraticTerm)
{
    float attenuation = 1.0 / (1.0 + 
                               linearTerm * distance + 
                               quadraticTerm * distance * distance);

    return max(attenuation, MIN_BRIGHTNESS);
}

void main()
{
    if (isCharging == 1)
    {
        float distance = distance(lightPosition, fragPosition);
        float brightness = attenuate(distance, LINEAR_TERM, QUADRATIC_TERM);
        vec4 color = texture(texture0, fragTexCoord);
        vec3 monochrome = vec3(dot(vec3(RED_LUM_CONSTANT, GREEN_LUM_CONSTANT, BLUE_LUM_CONSTANT), color.rgb));

        finalColor = vec4(monochrome * brightness, color.a);
    } else 
    {
        finalColor = texture(texture0, fragTexCoord); 
    }
}