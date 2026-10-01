#ifndef SCREEH_H
#define SCREEN_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Screen {
public:
    static unsigned SCR_WIDTH;
    static unsigned SCR_HEIGHT;

    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    Screen();

    // initialization
    bool init();
    void setParameters();

    // main loop
    void update();
    void newFrame();

    // window colosing accessor and modifier
    bool shouldClose();
    void setShouldClose(bool shouldClose);

private:
    GLFWwindow* window;

};

#endif 
