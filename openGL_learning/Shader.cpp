#include "Shader.h"

// Default constructor
Shader::Shader() {}
Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    generate(vertexShaderPath, fragmentShaderPath);
}

// The constructor
void Shader::generate(const char* vertexShaderPath, const char* fragmentShaderPath) {
    int success;
    char infoLog[512];

    GLuint vertexShader = compileShader(vertexShaderPath, GL_VERTEX_SHADER);
    GLuint fragShader = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

    this->id = glCreateProgram();
    glAttachShader(this->id, vertexShader);
    glAttachShader(this->id, fragShader);
    glLinkProgram(this->id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        cout << "Linking error: " << infoLog << endl;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
}

void Shader::activate() {
    glUseProgram(this->id);
}

string Shader::loadShaderSrc(const char* filename) {
    ifstream file;
    stringstream buff;

    file.open(filename);
    if (!file.is_open()) {
        cout << "Cannot open shader file: " << filename << endl;
        return "";
    }

    buff << file.rdbuf();
    return buff.str();
}

GLuint Shader::compileShader(const char* filepath, GLenum type) {
    int success;
    char infoLog[512];

    GLuint shaderId = glCreateShader(type);
    string src = loadShaderSrc(filepath);

    const char* shaderCode = src.c_str();
    glShaderSource(shaderId, 1, &shaderCode, NULL);
    glCompileShader(shaderId);

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        cout << "Shader compile error" << infoLog << endl;
    }

    return shaderId;
}

void Shader::setMat4(const string& name, glm::mat4 val) {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::setInt(const string& name, int value) {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

