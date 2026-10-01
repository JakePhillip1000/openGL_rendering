#include <iostream>
#include "Keyboard.h"

bool Keyboard::keys[GLFW_KEY_LAST] = { 0 };
bool Keyboard::keysChanged[GLFW_KEY_LAST] = { 0 };


// key state call back
void Keyboard::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key < 0 || key >= GLFW_KEY_LAST) {
        return;
    }

    if (action == GLFW_PRESS) {
        keys[key] = true;
        keysChanged[key] = true;
    }
    else if (action == GLFW_RELEASE) {
        keys[key] = false;
        keysChanged[key] = true;
    }
}


bool Keyboard::key(int key) {
    return keys[key];
}

bool Keyboard::keyChanged(int key) {
    /*
        Check the key change and set it to false because we dont want
        to see the key change every frame
    */
    bool ret = keysChanged[key];
    keysChanged[key] = false;
    return ret;
}

bool Keyboard::keyWentUp(int key) {
    return !keys[key] && keyChanged(key);
}

bool Keyboard::keyWentDown(int key) {
    return keys[key] && keyChanged(key);
}

