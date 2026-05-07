#version 330

uniform sampler2D texture0;
uniform float blizzardIntensity;
uniform float time;

in vec2 fragTexCoord;
in vec2 fragPosition;

out vec4 finalColor;

float noise(vec2 coord)
{
    return fract(sin(dot(coord, vec2(12.9898, 78.233))) * 43758.5453);
}

void main()
{
    vec4 color = texture(texture0, fragTexCoord);

    if (blizzardIntensity > 0.0)
    {
        float whiten = blizzardIntensity * 0.7;
        color.rgb = mix(color.rgb, vec3(1.0), whiten);
        float n1 = noise(fragPosition * 0.06 + vec2(time * 2.5, time * 4.0));
        if (n1 > (1.0 - blizzardIntensity * 0.65))
        {
            color.rgb = mix(color.rgb, vec3(1.0), 0.8);
        }

        float n2 = noise(fragPosition * 0.15 + vec2(time * 5.0, time * 3.0));
        if (n2 > (1.0 - blizzardIntensity * 0.6))
        {
            color.rgb = mix(color.rgb, vec3(0.95), 0.5);
        }

        if (blizzardIntensity > 0.2)
        {
            float grey = dot(color.rgb, vec3(0.299, 0.587, 0.114));
            float desatAmount = (blizzardIntensity - 0.2) * 0.7;
            color.rgb = mix(color.rgb, vec3(grey), desatAmount);
        }

        if (blizzardIntensity > 0.3)
        {
            float streak = noise(vec2(fragPosition.x * 0.05 + time * 6.0, fragPosition.y * 0.008 + time * 12.0));
            if (streak > 0.85)
            {
                color.rgb = mix(color.rgb, vec3(0.95, 0.97, 1.0), 0.55);
            }
        }
    }

    finalColor = color;
}
