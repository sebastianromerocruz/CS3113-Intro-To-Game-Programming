#include "Effects.h"

#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

class ShaderProgram 
{
private:
    Shader mShader;
    bool mIsLoaded;

public:
    static constexpr int NOT_LOADED = -1;

    ShaderProgram();
    ~ShaderProgram();

    // Loads a vertex + fragment shader pair
    bool load(const std::string &vertexPath, const std::string &fragmentPath);
    // Unload shader
    void unload();

    // Begins and ends use of the shader
    void begin();
    void end();

    // Set uniform by name
    void setVector2(const std::string &name, const Vector2 &value);
    void setFloat(const std::string &name, float value);
    void setInt(const std::string &name, int value);

    // Getters
    Shader &getShader()     { return mShader;   }
    bool   isLoaded() const { return mIsLoaded; }
};

#endif
