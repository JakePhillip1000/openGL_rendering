#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Keyboard {
    public:
        // key state callback
        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        // Accessors
        static bool key(int key);
        static bool keyChanged(int key);
        static bool keyWentUp(int key);
        static bool keyWentDown(int key);

    private:
        static bool keys[GLFW_KEY_LAST];
        static bool keysChanged[GLFW_KEY_LAST];

};

#endif