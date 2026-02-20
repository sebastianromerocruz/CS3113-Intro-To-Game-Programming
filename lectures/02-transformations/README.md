<h2 align=center>Week II</h2>

<h1 align=center>Transformations</h1>

<h3 align=center>XXIX Guardian Moon, Imperial Year MMXXVI</h3>

<p align=center><strong><em>Song of the day</strong>: <a href="https://youtu.be/Q02RoRVJOVs?si=MUWENoPDiEak0N-K"><strong><u>Iced Coffee</u></strong></a> by Red Velvet (2022)</em></p>

---

## Sections

1. [**The XYZs of Game Programming**](#1)
2. [**Transformations**](#2)
    - [**Scaling**](#2-1)
    - [**Rotation**](#2-2)
    - [**Translation**](#2-3)
3. [**Transformations in Raylib**](#3)
    - [**Scaling**](#3-1)
    - [**Rotation**](#3-2)
    - [**Translation**](#3-3)

---

<a id="1"></a>

## The XYZs of Game Programming

Much like we discussed [**last time**](https://github.com/sebastianromerocruz/CS-3113-Intro-To-Game-Programming/tree/main/lectures/01-introduction#1), the number one "property" that makes games feel immersive is their ability to simulate the real world. To this end, it's only natural that we start by exploring the ways we can represent space in a quantifiable (and, therefore, programmable) way. 

So, how do we simulate movement through space? Physics teaches us to do so via systems called [**vectors**](https://en.wikipedia.org/wiki/Vector_(mathematics_and_physics)), whereby each vector contains an X-, Y-, and Z-coordinate in [**cartesian space**](https://en.wikipedia.org/wiki/Cartesian_coordinate_system):

<a id="fg-1"></a>

<p align=center>
    <img src="assets/cartesian.png">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure I</strong>: Four two-dimensional points in cartesian space.
    </sub>
</p>

Of course, to model objects in real-life, we would add an extra dimension. This makes sense; we exist in three-dimensional space, and as such, it would take three values to determine our location. It will thus, then, not surprise you to learn that modelling in video games works pretty much in exactly the same way. In just about every situation regarding how a game object exists within your game's space, we will be dealing with:

1. An initial set of coordinate (x-, y-, and z-values in cartesian space), stored in a vector.
2. A **transformation** of some sort acting on these coordinates.
3. The resulting coordinate vector.

<br>

<a id="2"></a>

## Transformations

_Transformations?_ you ask, _what are those?_ Paraphrasing quite a bit, transformations in game programming a functions that act on a point in space in order for that point to move somewhere else. 

<a id="fg-2"></a>

<p align=center>
    <img src="assets/what-transformations-are.png">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure II</strong>: You know?
    </sub>
</p>

For example, if point `p` starts at location (1, 0) in frame one and ends at location (1.05, -0.05) in frame 2, then we say that _point `p` underwent a transformation_. Now, it might seem like these transformations are only about moving, or, _translating_ things from place to the other (and, in a sense, it is), but they are a little bit more nuanced than that.

In reality, we have three types of transformations: **scaling**, **rotation**, and the familiar **translation**. Let's tackle those one-by-one.

<a id="2-1"></a>

### Scaling

Scaling, properly defined, is a transformation that _enlarges and/or shrinks objects_ by some sort of **scale factor**. Typically, we have two types of scaling:

1. **Uniform (Isotropic) Scaling**: Where the object enlarges/shrinks the same in all cartesian directions. For example...
    - Zooming in to/out of an image
    - "Heartbeat" effects
2. **Non-Uniform (Anisotropic) Scaling**: Where the object enlarges/shrinks differently in at least one of the cartesian directions. For example...
    - Shadow effects on the ground

For example, consider the following scaling operation:

<a id="fg-3"></a>

<p align=center>
    <img src="assets/scaling.png">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure III</strong>: A simple triangle being uniformly scaled by a factor of 2 alongside with its vector notation equivalent.
    </sub>
</p>

As you can see by the operations taking place, scaling is fairly simple: we take the points composing an object and we multiply their components by a specific scale factor. Note that the name "scaling" is not coincidental here. Scalar factors are, by definition _directionless_—that is, the scaling factor itself does not have an x-, y-, and/or z-component. It is us, the programmers, who choose to apply it to one or all components of a point's vector.

<a id="2-2"></a>

### Rotation

Things get quite a bit more complicated when trying to model rotation. Luckily for us, raylib will do most of the heavy-lifting, but I'll go through the math below to illustrate what actually goes on under the hood. Unlike scaling, rotation is very much _directional_—that is, it contains its own x-, y-, z-components that need to be factored into the process. Note, too, that all of the rotations we will be doing in this class will be done _about the object's origin_. So, how does a rotation look like?

<a id="fg-4"></a>

<p align=center>
    <img src="assets/rotation.png">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure IV</strong>: A simple triangle being rotated along its z-axis. Notice that the rotation matrix on the left is a <em>4 x 4</em> matrix.
    </sub>
</p>

As you can see, our target location is defined not by simply multiplying a number across all components of every coordinate, but rather through [**matrix multiplication**](https://www.mathsisfun.com/algebra/matrix-multiplying.html) using something called the [**rotation matrix**](https://en.wikipedia.org/wiki/Rotation_matrix). We won't have to deal with any matrices when we deal with raylib, but it is good to keep in mind that there's quite a bit of linear algebra that goes into this operation.

<a id="2-3"></a>

### Translation

Last but not least we have **translation** which, in a way, is the most straight forward of all. Translation moves every point of an object by the same distance in any given direction. So, yes, this transformation is also directional, which does make it a tad bit more complex than scaling, but not quite as much as rotation:

<a id="fg-5"></a>

<p align=center>
    <img src="assets/translation.png">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure V</strong>: A simple triangle being translated by a 3<code>x</code> - 2<code>y</code> vector.
    </sub>
</p>

Note that, unlike scaling and rotation, translation involves _addition_ as opposed to multiplication. Because of this, applying all three transformations consecutively is actually quite involved. Like I said, though, raylib allows us to sort of bypass all of those difficulties in favour of a simpler (if less flexible) interface.

<br>

<a id="3"></a>

## Transformations in Raylib

Now onto programming. We will begin in earnest by drawing onto our screen the most basic of all building blocks of computer graphics: the **triangle**.

In your _`render`_ method, go ahead and type in the following line of code (after `BeginDrawing` and `ClearBackground` but before `EndDrawing`):

```cpp
DrawPoly({ SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 }, 3, 100, 0.0f, RED);
```

Running our program, we should see the following:

<a id="fg-6"></a>

<p align=center>
    <img src="assets/transformations-01.png">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure VI</strong>: Welcome to game programming.
    </sub>
</p>

Fascinating! Now, why are triangles the building blocks of game programming? Well, triangles are the polygons with the least amount of sides possible. Therefore, one can theoretically build literally any shape by creating a **mesh** made out of triangles:

<a id="fg-7"></a>

<p align=center>
    <img src="assets/mesh.png">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure VII</strong>: A model of a <a href="https://www.researchgate.net/figure/D-mesh-triangles-with-different-resolution-3D-Modelling-for-programmers-Available-at_fig2_322096576">bunny</a> at different resolutions.
    </sub>
</p>

Now, the `DrawPoly` (draw polygon) function takes care of basically all three of our transformations, one by one. Consider the names of its parameters:

```c++
void DrawPoly(Vector2 center, int sides, float radius, float rotation, Color color);
```

One-by-one, we have:
- **`Vector2 center`**: A raylib object representing the location of the origin of your polygon, represented itself by a vector. Note that _coordinates in raylib are measued from the top-left corner_. Therefore, the centre of the screen is _not_ (0.0, 0.0), but rather (Width<sub><em>window</em></sub> / 2, Height<sub><em>window</em></sub> / 2).
- **`int sides`**: This value indicates which `n`-polygon we want to draw. In our case, `n` = 3, for a triangle.
- **`int radius`**: This integer represents the length of each of the polygon's sides. In other words, this parameter represents our _scale factor_. Because this factor is scaling our polygon in every direction equally, we can only perform uniform scaling with this function (which is enough for now).
- **`float rotation`**: This, in turn, takes care of our rotation. Note that, for this function, all rotations are done _about the z-axis_ (that is, the axis that goes through the screen).
- **`Color color`**: As the name implies, this will determine the solid colour that will your polygon.

So let's go ahead and apply some transformations to it. 

<a id="3-1"></a>

### Scaling

First up: scaling. Let's set our initial triangle scale factor to be `100`:

```c++
// ...

// ...

float gScaleFactor = 100.0f;

// ...

void render() 
{
    // ...
    
    DrawPoly({ SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 }, 3, gScaleFactor, 0.0f, RED);
    
    // ...
}
```

What if we wanted our triangle, as our first "game mechanic" of the semester, to grow by 1% every single frame? Certainly, the answer to this lies in changing the value of `gCurrentScale` every frame. But _where_ would we do this?

Remember from last week that [**`render`**](https://github.com/sebastianromerocruz/CS-3113-Intro-To-Game-Programming/tree/main/lectures/01-introduction#main) is our dedicated function for all things related to drawing pixels on the screen, and that is _all_ that it should do. It should not have to deal with updating any of the game's logic whatsoever. That, instead, is the job of **`update`**. So, if we want something to be 101% of its previous size every frame, we should multiply our scale factor by a multiplier of `1.01f` _every frame_:

```c++
// ...

void update()
{
    gScaleFactor *= 1.01f;
}

// ...
```

Et voilá!

<a id="fg-8"></a>

<p align=center>
    <img src="assets/scaling.gif">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure VIII</strong>: Absolutely terrifying.
    </sub>
</p>

<a id="3-2"></a>

### Rotation

Rotations are basically going to work exactly the same. To make it a little more interesting, though, instead of have it rotate constantly to the right, let's have it do something closer to a metronomic motion, rotating from left to right:

```c++
// ...

enum Direction { LEFT, RIGHT };      // turning left or right?

// ...

constexpr float LIMIT_ANGLE = 20.0f; // when turning directions will flip

Direction gDirection = RIGHT;        // start by rotating right
float gAngle         = 0.0f;

// ...

void update() 
{
    gScaleFactor *= 1.01f;

    // Increase angle by 1.0f times either 1
    // if we're turning right or -1 if we're
    // turning left
    gAngle += 1.0f * gDirection == RIGHT ? 1 : -1;

    // Once we reach the limit angle, switch direction
    if      (gAngle >  LIMIT_ANGLE) gDirection = LEFT;
    else if (gAngle < -LIMIT_ANGLE) gDirection = RIGHT;
}
```

<a id="fg-9"></a>

<p align=center>
    <img src="assets/rotation_scaling.gif">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure IX</strong>: Both rotation and scaling in action.
    </sub>
</p>

<a id="3-3"></a>

### Translation

Finally, let's move our triangle around the screen. Maybe having it traverse from the top-left corner (0, 0) to the bottom right corner (`SCREEN_WIDTH`, `SCREEN_HEIGHT`)? For this transformation, we will be utilising raylib's `Vector2` class to keep track of our x- and y-coordinates (instead of having two free-floating variables keeping track of the same thing):

```c++
Vector2 gPosition = { 0.0f, 0.0f };

void update() 
{
    // note that I made this factor much smaller
    gScaleFactor *= 1.0025f;

    // translation
    if (gPosition.x < SCREEN_WIDTH)  gPosition.x += 1.0f;
    if (gPosition.y < SCREEN_HEIGHT) gPosition.y += 0.5f;

    // Increase angle by 1.0f times either 1
    // if we're turning right or -1 if we're
    // turning left
    gAngle += 1.0f * gDirection == RIGHT ? 1 : -1;

    // Once we reach the limit angle, switch direction
    if      (gAngle >  LIMIT_ANGLE) gDirection = LEFT;
    else if (gAngle < -LIMIT_ANGLE) gDirection = RIGHT;
}
```

<a id="fg-10"></a>

<p align=center>
    <img src="assets/all.gif">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure X</strong>: Rotation, scaling, and translation in action.
    </sub>
</p>

In the future, we will have vectors for all three transformations, not just for translation. But this is enough for a quick proof-of-concept. 

Congrats! We've got pixels moving on the screen! Another _huge_ step for our game engine.