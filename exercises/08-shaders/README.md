<h2 align=center>Week 10</h2>

<h1 align=center>Shaders: <em>The Powers Of Colour</em></h1>

<h4 align=center><a href="starter.zip">Download The Project's Zip File Here</a><h4>

---

## Sections
1. [**The Problem**](#1)
2. [**The Requirements**](#2)
3. [**How and What to Submit**](#3)

---

<a id="1"></a>

## The Problem

If you run [**`main.cpp`**](main.cpp), you will see the following scene:

<a id="fg-1"></a>

<p align=center>
    <img src="assets/README/start.gif">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure I</strong>: Where Hinako, our witch this week, can charge up her powers by holding down the <code>s</code>-key.
    </sub>
</p>

Your goal is to add some logic the [**fragment shader**](shaders/fragment.glsl), and to your [**`main.cpp`**](main.cpp) file, to create the following level:

<a id="fg-2"></a>

<p align=center>
    <img src="assets/README/end.gif">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure II</strong>: Your goal.
    </sub>
</p>

In other words:

- Communicate to your fragment shader whether or not Hinako is charging.
- If Hinako is charging, your fragment shader will want to:
    1. Create the [**"spotlight" effect**](https://github.com/sebastianromerocruz/CS-3113-Intro-To-Game-Programming/tree/main/lectures/10-effects-shaders#fg-13).
    2. Drain the whole scene of colour, using the [**perceived luminance formula**](https://github.com/sebastianromerocruz/CS-3113-Intro-To-Game-Programming/tree/main/lectures/10-effects-shaders#greyscale).

<a id="2"></a>

## The Requirements

- You _must_ adhere to only concepts learned in class so far.
- Only the [**fragment shader**](shaders/fragment.glsl) and [**`main.cpp`**](main.cpp) files must be modified.
- You must try to minimise the amount of hard-coding (i.e. create as many constants and enums as possible!).
- If your finger even _hovers_ over the Copilot button on VSCode, I _swear to you_ that swift and merciless justice will fall upon your grade.

<br>

<a id="3"></a>

## How and What to Submit

1. Show your working solution to the professor. All group members must have it working on their computers for the whole team to get checked out.
2. You must submit in the relevant [**discussion board**](https://brightspace.nyu.edu/d2l/le/501465/discussions/topics/574634/View) on Brightspace. **Only one person per team must upload the team's solution, but that person must include everybody's names**. You submission ***must adhere to the following format***:
    - **Subject**: `Team #X`
    - **Body**: 
        ```
        - Team Member A Name (teamMemberAEmail@nyu.edu)
        - Team Member B Name (teamMemberBEmail@nyu.edu)
        - Team Member C Name (teamMemberCEmail@nyu.edu)
        - Team Member D Name (teamMemberDEmail@nyu.edu)
        - ...
        ```
    - **Attached File**: `teamX.zip` containing the following file structure...
        ```
        teamX
        ├── CS3113
        │   ├── Dungeon.cpp
        │   ├── Dungeon.h
        │   ├── Effects.cpp
        │   ├── Effects.h
        │   ├── Entity.cpp
        │   ├── Entity.h
        │   ├── Map.cpp
        │   ├── Map.h
        │   ├── Scene.cpp
        │   ├── Scene.h
        │   ├── ShaderProgram.cpp
        │   ├── ShaderProgram.h
        │   ├── cs3113.cpp
        │   └── cs3113.h
        ├── assets
        │   ├── README
        │   └── game
        │       ├── Blue_witch
        │       │   └── ...
        │       └── ...
        ├── main.cpp
        ├── makefile
        └── shaders
            ├── fragment.glsl
            └── vertex.glsl
        ```