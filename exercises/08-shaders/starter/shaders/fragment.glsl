#version 330

const float RED_LUM_CONSTANT   = 0.2126;
const float GREEN_LUM_CONSTANT = 0.7152;
const float BLUE_LUM_CONSTANT  = 0.0722;
const float LINEAR_TERM        = 0.0005;  // linear term
const float QUADRATIC_TERM     = 0.00009; // quadratic term
const float MIN_BRIGHTNESS     = 0.05;    // avoid total darkness

uniform sampler2D texture0;
uniform vec2 lightPosition;

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
    finalColor = texture(texture0, fragTexCoord);
}