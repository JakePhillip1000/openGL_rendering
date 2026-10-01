#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Texture {
public:
    Texture();
    Texture(const char* path, const char* name, bool defaultParams = true);

    void generate();
    void load(bool flip = true);

    void setFilters(GLenum all);
    void setFilters(GLenum mag, GLenum min);

    void setWrap(GLenum all);
    void setWrap(GLenum s, GLenum t);

    void bind();

    int id;
    unsigned int tex;
    std::string name;

private:
    static int currentId;
    std::string path;
    int width;
    int height;
    int nChannels;

};

#endif