<h1 align=center>Raylib Setup Guide (macOS & Windows)</h1>

<h3 align=center>MacOS & Windows</h3>

---

## Sections

1. [**MacOS Instructions**](#1)
   1. [**Step 1: Install Homebrew (if not already installed)**](#1-1)
   2. [**Step 2: Install Required Packages**](#1-2)
   3. [**Step 3: Verify Installation**](#1-3)
2. [**Windows Instructions (MinGW)**](#2)
   1. [**Install Raylib for Windows**](#2-1)
   2. [**Test `g++` and `make`**](#2-2)
3. [**Folder Setup**](#3)
4. [**Makefile Contents**](#4)
5. [**How to Use the Makefile**](#5)

---

<a id="1"></a>

## macOS Instructions

<a id="1-1"></a>

### Step 1: Install Homebrew (if not already installed)

If you don’t have Homebrew installed, open the Terminal and run:

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

<a id="1-2"></a>

### Step 2: Install Required Packages

```bash
brew install cmake raylib
```

This installs both CMake and Raylib system-wide. If you’re using an M1/M2/M3 Mac, Homebrew will automatically handle `arm64` binaries.

<a id="1-3"></a>

### Step 3: Verify Installation

Run the following commands on your Terminal:

```bash
cmake --version
pkg-config --modversion raylib
```

if you get "zsh: command not found: pkg-config", then install it:
```bash
brew install pkg-config
```

You should see version numbers for both `cmake` and `raylib`.

<br>

<a id="2"></a>

## Windows Instructions (MinGW)

<a id="2-1"></a>

### Step 1: Install Raylib for Windows

1. Download the precompiled Raylib binaries for MinGW:
   - [https://github.com/raysan5/raylib/releases](https://github.com/raysan5/raylib/releases)
   - Look for a `.zip` labeled `raylib_x.y.z_mingw-w64.zip`

2. Extract the contents to:
   `C:\raylib\`
   So you’ll have:
   - `C:\raylib\include\` (headers)
   - `C:\raylib\lib\` (compiled .a files)

3. Make sure `g++` and `make` are available in your `PATH` (via MinGW or MSYS2).
   - If you don’t have them, install [MSYS2](https://www.msys2.org/) and run:

     ```bash
     pacman -S mingw-w64-ucrt-x86_64-gcc make
     ```

<a id="2-2"></a>

### Step 2: Test `g++` and `make`

Open the terminal (MSYS2 or `cmd` if MinGW is installed globally):

```bash
g++ --version
make --version
```

If you see valid version outputs, you're ready to go.

<br>

<a id="3"></a>

## Folder Setup

Structure your projects like this:

```
project-name/
├── main.cpp
└── Makefile
```

<br>

<a id="4"></a>

## Makefile Contents

```makefile
# Source and target
SRCS = main.cpp
TARGET = raylib_app

# OS detection (macOS = Darwin, Windows via MinGW = MINGW*)
UNAME_S := $(shell uname -s)

# Add the CS3113 library if it exists
ifeq ($(wildcard CS3113/cs3113.cpp),CS3113/cs3113.cpp)
    SRCS += CS3113/cs3113.cpp
endif

# Default values
CXX = g++
CXXFLAGS = -std=c++11

# Raylib configuration using pkg-config
RAYLIB_CFLAGS = $(shell pkg-config --cflags raylib)
RAYLIB_LIBS = $(shell pkg-config --libs raylib)

ifeq ($(UNAME_S), Darwin)
    # macOS configuration
    CXXFLAGS += -arch arm64 $(RAYLIB_CFLAGS)
    LIBS = $(RAYLIB_LIBS) -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
    EXEC = ./$(TARGET)
else ifneq (,$(findstring MINGW,$(UNAME_S)))
    # Windows configuration (assumes raylib in C:/raylib)
    CXXFLAGS += -IC:/raylib/include
    LIBS = -LC:/raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm
    TARGET := $(TARGET).exe
    EXEC = ./$(TARGET)
else
    # Linux/WSL fallback
    CXXFLAGS +=
    LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    EXEC = ./$(TARGET)
endif

# Build rule
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

# Clean rule
clean:
	@if [ -f "$(TARGET)" ]; then rm -f $(TARGET); fi
	@if [ -f "$(TARGET).exe" ]; then rm -f $(TARGET).exe; fi

# Run rule
run: $(TARGET)
	$(EXEC)
```

<br>

<a id="5"></a>

## How to Use the Makefile

1. **Build the project**

```bash
make
```

2. **Run the project**

```bash
make run
```

3. **Clean up the binary**

```bash
make clean
```
