 <h2 align=center>Week 10</h2>

<h1 align=center>Shaders</h1>

<h3 align=center>XVI Red Wolf Moon, Imperial Year MMXXVI</h3>

<p align=center><strong><em>Song of the day</strong></em>: <em><a href="https://youtu.be/dWvJPmfmhDA?si=zQb8U1mcbmCa48vH"><strong>Existential Crisis</a></strong> by WENDY (2025)</em></p>

---

## Sections

1. [**Shaders**](#1)
    - [**Vertex Shader**](#1-1)
        - [**Inputs: data coming from the CPU or vertex buffer**](#1-1-1)
        - [**Outputs: data to be passed to the fragment shader**](#1-1-2)
        - [**Uniforms: constant data supplied by the CPU**](#1-1-3)
        - [**The `main` function**](#1-1-4)
    - [**Fragment Shader**](#1-2)
        - [**Basic Shader Programming**](#1-2-1)
        - [**Greyscale**](#1-2-2)
    - [**Communicating With Shaders**](#1-3)

---

<a id="1"></a>

## Shaders

This is perhaps my favourite topic of the entire course, so it's a shame that we only get to touch it so briefly. Shaders are basically programs that run _directly on the GPU_ and control nearly every stage of the rendering pipeline. Instead of relying on [fixed-function graphics](https://en.wikipedia.org/wiki/Fixed-function_(computer_graphics)) (as we did in ye olde days), modern rendering is fully programmable: the GPU asks us how to process vertices, how to colour pixels, and how to apply lighting or special effects. Shaders give us that control. This also makes our games much more efficient—any work you can move from the CPU to the GPU—lighting, transformations, filtering—will run much faster.

We have two types of shaders:
- **Vertex Shader**: This shader translates the vertices that we feed into it to screen positions.
- **Fragment Shader**: For _each pixel_, the fragment shader determines exactly what colour to draw onto the screen. It does this by either grabbing a pixel/colour from a texture, or by interpolating by distance from the vertices.

<a id="fg-1"></a>

```
 +———————————————————+       +———————————————————+       +——————————————————————————————————————+
 |     Vertices      | ----> |   Vertex Shader   |       |                                      |
 +———————————————————+       +———————————————————+       |                                      |
                                      |                  |         +——————————————————+         |
                                      V                  |         | SUPER MARIO BROS |         |
                             +———————————————————+       |         +——————————————————+         |
                             |  Fragment Shader  | ----> |                                      |
                             +———————————————————+       |                                      |
                                                         |           > Start                    |
                                                         |           > Settings                 |
                                                         |                                      |
                                                         +——————————————————————————————————————+
```

<p align=center>
    <sub>
        <strong>Figure I</strong>: The shader pipeline.
</p>

So, what _can_ we program with shaders? Everything beyond the most basic rendering depends on shaders: lighting models, shadows, fog, bloom, outlines, distortion effects, water, particles, post-processing, and more. If you can think of an effect, you can usually write a shader to do it and, because shaders operate per-vertex and per-pixel, you can decide exactly how every pixel in your game should appear, using math, textures, and uniform parameters you pass in from the CPU to the GPU.

In order to get started, let's take a look at some bare-bones examples of both shaders.

<a id="1-1"></a>

### Vertex Shader

Shaders are typically written in [**glsl**](https://en.wikipedia.org/wiki/OpenGL_Shading_Language), or "[Open]GL Shading Language", which looks a lot like C. Let's take a look at it:

```glsl
// vertex.glsl
#version 330

in vec3 vertexPosition;
in vec2 vertexTexCoord;

out vec2 fragTexCoord;
out vec2 fragPosition;

uniform mat4 mvp;

void main()
{
    fragTexCoord = vertexTexCoord;
    fragPosition = vertexPosition.xy;
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}
```

This is a **vertex shader**, which runs once per vertex. Its job is to prepare data for the fragment shader and to compute each vertex’s final position on screen.

<a id="1-1-1"></a>

#### **Inputs**: data coming from the CPU or vertex buffer

```glsl
in vec3 vertexPosition;
in vec2 vertexTexCoord;
```

- `in` variables are what we call **vertex attributes**—data provided for each vertex (by Raylib internally).
- `vertexPosition` is the position of the vertex in x-/y-coordinates.
- `vertexTexCoord` is the 2D coordinate used to look up into a texture (i.e. the u-/v-coordinate).

These values are different for _each vertex_, so the shader will execute once per vertex with different input values.

<a id="1-1-2"></a>

#### **Outputs**: data to be passed to the fragment shader

```glsl
out vec2 fragTexCoord;
out vec2 fragPosition;
```

- `out` variables carry data from the **vertex shader** to the **fragment shader**. They are automatically interpolated across the polygon being drawn, meaning that if one vertex has `texCoord` (0,0) and another has (1,1), pixels in between get intermediate values.
- `fragTexCoord` is used for texture sampling in the fragment shader.
- `fragPosition` holds the 2D world position (x-/y-coordinates).

<a id="1-1-3"></a>

#### **Uniforms**: constant data supplied by the CPU

```glsl
uniform mat4 mvp;
```

- Uniforms don’t change per vertex; they change _per draw call_.
- Any variable marked as `uniform` represents data that is being manually passed (either by us or by raylib) into the shaders from our C++ code.
- `mvp` stands for **Model–View–Projection** matrix. This transforms a vertex from object space to the world space, then to the camera space and finally to the screen space.
- In raw OpenGL, we would upload this matrix each frame. Thankfully, raylib takes care of most of it for us.

<a id="1-1-4"></a>

#### The `main` function

```glsl
void main()
{
    fragTexCoord = vertexTexCoord;
    fragPosition = vertexPosition.xy;
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}
```

Line-by-line, we:

1. Pass the texture coordinate to the fragment shader. Sometimes there will be some calculations involved here in the case of shadows and lighting, but in our case the fragment shader will simply sample the sprite/tileset.
2. Store the X and Y components of the vertex’s position.
3. Define where the vertex ends up on screen. This step is actually extremely important but, again, we don't need to worry about this in our class.

<a id="1-2"></a>

### Fragment Shader

The fragment shader is where most of the action that we'll see in this class will happen. Right now, it's very simple:

```glsl
#version 330

uniform sampler2D texture0;

in vec2 fragTexCoord;
in vec2 fragPosition;

out vec4 finalColor;

void main()
{
    finalColor = texture(texture0, fragTexCoord);
}
```

- We've got `fragTexCoord` and `fragPosition` coming in from the _vertex shader_ (since they're `in` variables).
- We've got `texture0` being fed into the shader by our CPU every frame (since it's a `uniform` variable). This represents the actual texture file we use when calling the `render` function.
- We've got `finalColor` being pushed out of the shader. Basically, every fragment shader must output the final color of the current pixel it is working with. In our code, there's not a lot going on, we're simply sampling directly from the texture:
    ```glsl
    finalColor = texture(texture0, fragTexCoord);
    ```
    Just remember that this `out` variable is a `vec4` because it includes red, green, blue, and alpha values.

<a id="1-2-1"></a>

#### Basic Shader Programming

How can we change things up? Well, let's say we removed one or more of the channels out of `finalColor`:

```glsl
void main()
{
    vec4 color = texture(texture0, fragTexCoord);
    finalColor = vec4(color.r, 0.0, 0.0, color.a);
}
```

Xochitl now looks like she's in danger:

<a id="fg-2"></a>

<p align=center>
    <img src="assets/README/shader-red.png">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure II</strong>: Isolating only the red channel.
    <sub>
</p>

Or if we mixed the channels up:

```glsl
void main()
{
    vec4 color = texture(texture0, fragTexCoord);
    finalColor = vec4(color.g, color.b, color.r, color.a);
}
```

<a id="fg-3"></a>

<p align=center>
    <img src="assets/README/shader-mix.png">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure III</strong>: Scrambling the colour channels.
    <sub>
</p>

Or even inverting them?

```glsl
void main()
{
    vec4 color = texture(texture0, fragTexCoord);
    finalColor = vec4(1 - color.r, 1 - color.g, 1 - color.b, color.a);
}
```

<a id="fg-4"></a>

<p align=center>
    <img src="assets/README/shader-inverted.png">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure IV</strong>: Inverting the colour channels. I personally love this one.
    <sub>
</p>

<a id="1-2-2"></a>

#### Greyscale

We can also take advantage of luminance, the intensity of light emitted from a surface, to get a basic greyscale palette:

<a id="fg-5"></a>

<p align=center>
    <img src="assets/README/shader-basic-bw.png">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure V</strong>: A very basic form of monochrome.
    <sub>
</p>

We can also get a more nuanced grayscale by taking advantage of something called "perceived luminance", or how bright a light source appears to the human eye. Basically, in human vision:
- Green contributes most to perceived brightness
- Red contributes a bit less
- Blue contributes least

Research in colour science quantifies this into a standard formula for converting an RGB color into perceived luminance, using what are called the [**ITU-R BT.709 (sRGB) luminance coefficients**](https://en.wikipedia.org/wiki/Rec._709):

> *Y* = 0.2126*R* + 0.7152*G* + 0.0722*B*

I'm gonna add these in to my code, and use this formula to give me a nice, "realistic" monochrome (the dot product, by the way, is a compact way to write the above formula):

```glsl
// ...

const float RED_LUM_CONSTANT   = 0.2126;
const float GREEN_LUM_CONSTANT = 0.7152;
const float BLUE_LUM_CONSTANT  = 0.0722;

// ...

void main()
{
    vec4 color = texture(texture0, fragTexCoord);
    vec3 luminance = vec3(
        dot(
            vec3(RED_LUM_CONSTANT, GREEN_LUM_CONSTANT, BLUE_LUM_CONSTANT), 
            color.rgb
        )
    );
    finalColor = vec4(luminance.rgb, color.a);
}
```

<a id="fg-6"></a>

<p align=center>
    <img src="assets/README/shader-luminance-bw.png">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure VI</strong>: All around me are familiar faces.
    <sub>
</p>

<a id="1-3"></a>

### Communicating With Shaders

This is all well and good, but none of it necessarily does anything that couldn't be also done by simply adding more textures to our assets folder. Let's try something a little more exciting. If you've ever played [**Paper Mario 64**](https://en.wikipedia.org/wiki/Paper_Mario_(video_game)), you might recognise the following scene:

<a id="fg-7"></a>

<p align=center>
    <img src="assets/README/paper-mario.png">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure VII</strong>: Mario and his partner, Sparky.
    <sub>
</p>

When Mario has Sparky as his partner, she acts like a light source as she follows him around in dark rooms. The textures around the room never change at all—the brightness gradient is completely calculated (based on the position of Mario and Sparky) and applied by the shaders.

How can we do this? First, look at the shader-related code that I've included in our `main`:

```cpp
// main.cpp
// ...

ShaderProgram gShader;

// ...

void initialise()
{
    // ...

    gShader.load("shaders/vertex.glsl", "shaders/fragment.glsl");

    // ...
}

// ...

void render()
{
    BeginDrawing();
    BeginMode2D(gCamera);
    gShader.begin();

    // Shader-affected rendering happens here!

    gShader.end();
        EndMode2D();
    EndDrawing();
}

void shutdown() 
{
    // ..

    gShader.unload();

    // ...
}

// ...
```

The `ShaderProgram` class is defined as follows:

```cpp
class ShaderProgram 
{
private:
    Shader mShader;
    bool mIsLoaded;

public:
    static constexpr int NOT_LOADED = -1;

    ShaderProgram();
    ~ShaderProgram();

    bool load(const std::string &vertexPath, const std::string &fragmentPath);
    void unload();

    void begin();
    void end();

    void setVector2(const std::string &name, const Vector2 &value);
    void setFloat(const std::string &name, float value);
    void setInt(const std::string &name, int value);

    Shader &getShader()     { return mShader;   }
    bool   isLoaded() const { return mIsLoaded; }
};
```

The key lies in those setter methods:

```cpp
void setVector2(const std::string &name, const Vector2 &value);
void setFloat(const std::string &name, float value);
void setInt(const std::string &name, int value);
```

Remember how we said that [**`uniform` variables**](#1-1-3) are those whose values that we can send from our code to directly to the shaders? Let's take advantage of this system and start sending Xochitl's position to our fragment shader. 

First, add the variable to the shader file:

```glsl
// fragment.glsl
// ...

uniform vec2 lightPosition;

// ...
```

And use our setters in `main` to send it in:

```cpp
// main.cpp
// ...

Vector2 gLightPosition = { 0.0f, 0.0f };

// ...

void update() 
{
    // ...

    while (deltaTime >= FIXED_TIMESTEP)
    {
        // ...

        gLightPosition = gCurrentScene->getState().xochitl->getPosition();

        // ...
    }
}

void render()
{
    // ...

    gShader.begin();

    
    gShader.setVector2("lightPosition", gLightPosition);

    gCurrentScene->render();

    gShader.end();

    // ...
}
```

Note that the first parameter of each of these setters is the actual name of the `uniform` variable inside of the shader. It has to match _exactly_. One of the more frustrating sides of shader programming is that if you make a mistake, there will be no error messages; we're communicating directly with the GPU, and the GPU has no compiler.

Anyway, this, by itself, doesn't do anything—we'll have to add logic inside of the fragment shader to achieve our desired effect. The trick here is to check the distance from the light of each pixel. For this, we use something called the [**inverse-square law**](https://en.wikipedia.org/wiki/Inverse-square_law):

<a id="fg-8"></a>

<p align=center>
    <img src="assets/README/inverse-square-law-diagram.png">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure VIII</strong>: <code>S</code> represents the light source, while <code>r</code> represents the measured points. The lines represent the flux emanating from the sources and fluxes. The density of flux lines is inversely proportional to the square of the distance from the source because the surface area of a sphere increases with the square of the radius. Thus the field intensity is inversely proportional to the square of the distance from the source.
    <sub>
</p>

The formula to calculate how much light reaches a pixel based on distance—otherwise known as **attenuation**, is as follows:

```glsl
const float MIN_BRIGHTNESS = 0.05; // avoid total darkness

float attenuate(float distance, float linearTerm, float quadraticTerm)
{
    float attenuation = 1.0 / (1.0 + 
                               linearTerm * distance + 
                               quadraticTerm * distance * distance);
                               
    return max(attenuation, MIN_BRIGHTNESS);
}
```

Meaning, when `distance` is small, brightness ~= `1.0f` (a.k.a. full intensity). Now, let's apply it:

```glsl
// fragment.glsl
// ...

// Adjustable attenuation parameters
const float LINEAR_TERM    = 0.00003; // linear term
const float QUADRATIC_TERM = 0.00003; // quadratic term

// ...

void main()
{
    float distance   = distance(lightPosition, fragPosition);
    float brightness = attenuate(distance, LINEAR_TERM, QUADRATIC_TERM);
    vec4 color = texture(texture0, fragTexCoord);
    finalColor = vec4(color.rgb * brightness, color.a);
}
```

And we get this wonderful effect!

<a id="fg-9"></a>

<p align=center>
    <img src="assets/README/attenuation.gif">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure IX</strong>: The result is an effect that gives such an impression of polish and finesse for very little code.
    <sub>
</p>
