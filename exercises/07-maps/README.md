<h2 align=center>Week 08</h2>

<h1 align=center>Physics: <em>Escape The Room</em></h1>

---

## Sections
1. [**The Problem**](#1)
2. [**The Requirements**](#2)
3. [**How and What to Submit**](#3)

---

<a id="1"></a>

## The Problem

If you run [**`main.cpp`**](main.cpp), you will see a scene similar to the one we created in today's class:

<a id="fg-1"></a>

<p align=center>
    <img src="assets/README/start.gif">
    </img>
</p>

<p align=center>
    <sub>
        <strong>Figure I</strong>: Your starting condition.
    </sub>
</p>

Your goal is to add some logic the **`Entity`** class (defined [**here**](CS3113/Entity.h) and implemented [**here**](CS3113/Entity.cpp)), to your `Map` class (defined [**here**](CS3113/Map.h) and implemented [**here**](CS3113/Map.cpp)), as well as to your [**`main.cpp`**](main.cpp) file, to create the following level:

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

1. Create a map with the following structure:
    ```
    44444444444444
    4      4     4
    4       4  4 4
    4            4
    4     4    4 4
    4   4     4  4
    44      44   4
    4   44       4
    4      4 44224
    4        44444
    42222222444444
    43333333444444
    44444444444444
    ```

    - **Dimensions:** 14 columns × 13 rows
    - **Legend:**
        - `4` = solid wall tile
        - `0` or space = empty tile
        - `2` = special tile (e.g. water, hazard, or goal)
        - `3` = ground/platform tile
2. Create a "botton" `Entity` around location (1, 5) that _disappears when the player steps on it_. Since this button is static, it is not part of your map.
3. As soon as the player steps on it, some of the "ceiling" of the map should disappear, allowing the player to exit it and jump off, ending the game.

<a id="2"></a>

## The Requirements

- You _must_ adhere to only concepts learned in class so far.
- You must try to minimise the amount of hard-coding (i.e. use your objects' coordinates, scales, create as many constants as possible!).
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
        ```
    - **Attached File**: `teamX.zip` containing the following file structure...
        ```
        teamX
        ├── CS3113
        │   ├── cs3113.h
        │   ├── cs3113.cpp
        │   ├── Map.cpp
        │   ├── Map.h
        │   ├── Entity.cpp
        │   └── Entity.h
        └── main.cpp
        ```