#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Shader {
public:
    unsigned int id;

    // Constructor
    Shader();
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
    
    void generate(const char* vertexShaderPath, const char* fragmentShaderPath);
    
    void activate();

    // utility functions
    string loadShaderSrc(const char* filename);
    GLuint compileShader(const char* filepath, GLenum type);

    // uniform functions
    void setMat4(const string& name, glm::mat4 val);

    void setInt(const string& name, int value);

    void setFloat(const string& name, float value);
};

#endif 
 

