#ifndef SHADER_H
#define SHADER_H
#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "LightSource.hpp"

struct SurfaceProperties {
    uint diffuseTex;
    uint specularTex;
    float shininess;
};

class Shader
{
public:
    unsigned int ID;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const std::string& vertexPath, const std::string& fragmentPath)
    {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexPath.c_str());
            fShaderFile.open(fragmentPath.c_str());
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode   = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    ~Shader() {
        glDeleteProgram(ID);
    }
    
    // activate the shader
    // ------------------------------------------------------------------------
    void use()
    {
        glUseProgram(ID);
    }
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setUniform(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    
    void setUniform(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    
    void setUniform(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    
    void setUniform(const std::string &name, glm::vec2 value) const
    {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), value.x, value.y);
    }
    
    void setUniform(const std::string &name, glm::vec3 value) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
    }
    
    void setUniform(const std::string &name, glm::vec4 value) const
    {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w);
    }
    
    void setUniform(const std::string &name, const glm::mat2& value) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }
    
    void setUniform(const std::string &name, const glm::mat3& value) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }
    
    void setUniform(const std::string &name, const glm::mat4& value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }
    
    void setUniform(const std::string &name, const SurfaceProperties& value) const
    {
        setUniform(name + ".shininess", value.shininess);
    }
    
    void setCommon(const std::string &name, const LightInfo::Generic* info) {
        setUniform(name + ".diffuse", info->diffuse);
        setUniform(name + ".specular", info->specular);
        setUniform(name + ".ambient", info->ambient);
    }
    
    void setUniform(const std::string &name, const LightInfo::Point& value) {
        setCommon(name, &value);
        setUniform(name + ".position", value.position);
        setUniform(name + ".polynom", value.polynom);
    }
    
    void setUniform(const std::string &name, const LightInfo::Spot& value) {
        setCommon(name, &value);
        setUniform(name + ".position", value.position);
        setUniform(name + ".direction", value.direction);
        setUniform(name + ".polynom", value.polynom);
        setUniform(name + ".cutOff", value.cutOff);
        setUniform(name + ".outerCutOff", value.outerCutOff);
    }
    
    void setUniform(const std::string &name, const LightInfo::Directional& value) {
        setCommon(name, &value);
        setUniform(name + ".direction", value.direction);
    }
    
    void setUniform(const std::string &name, const LightInfo::Ambient& value) {
        setCommon(name, &value);
    }
    
    void setUniform(const LightInfo::Generic* value) {
        using namespace Constants::LightSource;
        switch (value->type) {
            case Type::Point: {
                if (pointLightsCnt >= MAX_POINT_LIGHTS) {
                    throw std::runtime_error("Point Lights limit exceeded!");
                }
                const LightInfo::Point* info = static_cast<const LightInfo::Point*>(value);
                setUniform("pointLights[" + std::to_string(pointLightsCnt) + "]", *info);
                setUniform("pointLightsCnt", ++pointLightsCnt);
                break;
            }
            case Type::Spot: {
                if (spotLightsCnt >= MAX_SPOT_LIGHTS) {
                    throw std::runtime_error("Spot Lights limit exceeded!");
                }
                const LightInfo::Spot* info = static_cast<const LightInfo::Spot*>(value);
                setUniform("spotLights[" + std::to_string(spotLightsCnt) + "]", *info);
                setUniform("spotLightsCnt", ++spotLightsCnt);
                break;
            }
            case Type::Directional: {
                if (directionalLightsCnt >= MAX_DIRECTIONAL_LIGHTS) {
                    throw std::runtime_error("Directional Lights limit exceeded!");
                }
                const LightInfo::Directional* info = static_cast<const LightInfo::Directional*>(value);
                setUniform("directionalLights[" + std::to_string(directionalLightsCnt) + "]", *info);
                setUniform("directionalLightsCnt", ++directionalLightsCnt);
                break;
            }
            case Type::Ambient: {
                if (ambientLightsCnt >= MAX_AMBIENT_LIGHTS) {
                    throw std::runtime_error("Ambient Lights limit exceeded!");
                }
                const LightInfo::Ambient* info = static_cast<const LightInfo::Ambient*>(value);
                setUniform("ambientLights[" + std::to_string(ambientLightsCnt) + "]", *info);
                setUniform("ambientLightsCnt", ++ambientLightsCnt);
                break;
            }
                
            default:
                throw std::runtime_error("Unknown LightSource Type in setUniform!");
                break;
        }
    }

private:
    int pointLightsCnt = 0;
    int spotLightsCnt = 0;
    int directionalLightsCnt = 0;
    int ambientLightsCnt = 0;
    
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};
#endif
