<h2 align=center>Week II</h2>

<h1 align=center>Transformations: <em>Funny Heartbeat</em></h1>

---

## Sections
1. [**The Problem**](#1)
2. [**Hints**](#2)
    - [**Constants**](#2-1)
    - [**Oscillating Behaviour**](#2-2)
    - [**Implementation Details**](#2-3)
3. [**How and What to Submit**](#3)

<p align=center><strong><a href="assets/01-transformations.zip">Download The Project Zip File Here</a></strong></p>

---

<a id="1"></a>

## The Problem

If you run the [**`main.cpp` file**](https://github.com/sebastianromerocruz/CS-3113-Intro-To-Game-Programming/blob/main/exercises/01-transformations/main.cpp) associated with this exercise, you will see the following triangle on your window:

<a id="fg-1"></a>

<p align=center>
    <img src="assets/start.png">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure I</strong>: Your starting conditions.
    </sub>
</p>

This makes sense, since the contents of `update()` are completely empty. Our goal is to add some game logic in there in order to get the following:

<a id="fg-2"></a>

<p align=center>
    <img src="assets/final.gif">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure II</strong>: Our goal.
    </sub>
</p>

In other words:

1. **Scale** the triangle in such a way that it produces a heartbeat-like _pulse_ effect.
2. **Translate** the triangle in such a way that it appears that it is _orbiting_ around some origin.

<br>

<a id="2"></a>

## Hints

<a id="2-1"></a>

### Constants

You will notice that your file has the following constants:

```c++
constexpr float RADIUS          = 100.0f, // radius of the orbit
                ORBIT_SPEED     = 0.05f,  // the speed at which the triangle will travel its orbit

                BASE_SIZE       = 50,     // the size of the triangle when it's not being scaled
                MAX_AMPLITUDE   = 10.0f,  // by how much the triangle will be expanding/contracting
                PULSE_SPEED     = 100.0f, // how fast the triangle is going to be "pulsing"
                PULSE_INCREMENT = 10.0f;  // the current value we're scaling by, related to the period
```

While using these constants is not strictly necessary, reading up on what the each do will definitely be helpful.

<a id="2-2"></a>

### Oscillating Behaviour

During lecture, we achieved the [**"metronomic" behaviour**](https://github.com/sebastianromerocruz/CS-3113-Intro-To-Game-Programming/tree/main/lectures/02-transformations#rotation-1) by having a limit and reversing the direction of the transformation every time that limit was reached. While this is a perfectly fine way of achieving oscillating behaviour, it's a little clunky. To give you a hint for a better way of going about it, check out the following:

<a id="fg-3"></a>

<p align=center>
    <img src="assets/circus.png">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure III</strong>: The relationship between the coordinates at any point of a circle's perimeter and the angle which it forms with the origin and the x-axis.
    </sub>
</p>

<a id="fg-4"></a>

<p align=center>
    <img src="assets/sin.png">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure IV</strong>: A cyclical relationship is usually described by a sinusodial function, such as this one.
    </sub>
</p>

### Implementation Details

Unlike the transformations we did in class, where we kept incrementing the value of `gAngle`/`gScalingFactor`/`gPosition.x`/`gPosition.y`, our behaviour is no longer linear at all. In other words, the values for all four of these variables will have to be calculated _from scratch every single frame_. However, that does not mean that you can't have another value constantly increasing as the frames go by. Think of how [**these types of functions work**](#fg-4), and how `x` changes of over time.

<br>

<a id="3"></a>

## How and What to Submit

1. Note that your solution _must_ adhere to what we're learned during class.
2. Show your working solution to the professor. All group members must have it working on their computers for the whole team to get checked out.
3. You must submit in the relevant [**"discussion" board**](https://brightspace.nyu.edu/d2l/le/501465/discussions/List?dst=1) on Brightspace. **Only one person per team must upload the team's solution, but that person must include everybody's names**. See below:

<a id="fg-5"></a>

<p align=center>
    <img src="assets/submit1.png">
    </img>
</p>

<a id="fg-6"></a>

<p align=center>
    <img src="assets/submit2.png">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figures V & VI</strong>: How to submit your work.
    </sub>
</p>