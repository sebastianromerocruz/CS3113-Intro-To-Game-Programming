#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() : mIsLoaded(false) { mShader = { 0 }; }
ShaderProgram::~ShaderProgram()                   { unload();        }

bool ShaderProgram::load(const std::string &vertexPath, const std::string &fragmentPath)
{
    unload(); // unload any previous shader

    mShader = LoadShader(vertexPath.c_str(), fragmentPath.c_str());

    if (mShader.id == 0)
    {
        printf("Failed to load shader: '%s', '%s'\n", vertexPath.c_str(), fragmentPath.c_str());
        mIsLoaded = false;
        return false;
    }

    printf("Successfully loaded shader: '%s', '%s'\n", vertexPath.c_str(), fragmentPath.c_str());

    mIsLoaded = true;
    return true;
}

void ShaderProgram::begin() { if (mIsLoaded) BeginShaderMode(mShader); }
void ShaderProgram::end()   { if (mIsLoaded) EndShaderMode();          }

void ShaderProgram::setVector2(const std::string &name, const Vector2 &value)
{
    if (!mIsLoaded) return;

    int locationID = GetShaderLocation(mShader, name.c_str());
    if (locationID != NOT_LOADED) 
        SetShaderValue(mShader, locationID, &value, SHADER_UNIFORM_VEC2);
}

void ShaderProgram::setFloat(const std::string &name, float value)
{
    if (!mIsLoaded) return;

    int locationID = GetShaderLocation(mShader, name.c_str());
    if (locationID != NOT_LOADED)
        SetShaderValue(mShader, locationID, &value, SHADER_UNIFORM_FLOAT);
}

void ShaderProgram::setInt(const std::string &name, int value)
{
    if (!mIsLoaded) return;

    int locationID = GetShaderLocation(mShader, name.c_str());
    if (locationID != NOT_LOADED)
        SetShaderValue(mShader, locationID, &value, SHADER_UNIFORM_INT);
}

void ShaderProgram::unload()
{
    if (mIsLoaded)
    {
        UnloadShader(mShader);
        mShader = { 0 };
        mIsLoaded = false;
    }
}
