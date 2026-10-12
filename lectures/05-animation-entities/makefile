#############
# Animation #
#############

# Source and target
SRCS = animation_single_row.cpp
# SRCS = animation_atlas.cpp
# SRCS = entities.cpp

TARGET = raylib_app

# OS detection (macOS = Darwin, Windows via MinGW = MINGW*)
UNAME_S := $(shell uname -s)

# Add the CS3113 library if it exists
ifeq ($(wildcard CS3113/animation/cs3113.cpp),CS3113/animation/cs3113.cpp)
    SRCS += CS3113/animation/cs3113.cpp
endif

##############
#  Entities  #
##############
# Add the CS3113 library if it exists
# ifeq ($(wildcard CS3113/entities/cs3113.cpp),CS3113/entities/cs3113.cpp)
#     SRCS += CS3113/entities/cs3113.cpp
# endif

# # Add the Entities library if it exists
# ifeq ($(wildcard CS3113/entities/Entity.cpp),CS3113/entities/Entity.cpp)
#     SRCS += CS3113/entities/Entity.cpp
# endif

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
