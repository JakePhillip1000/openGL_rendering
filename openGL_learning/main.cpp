// must include glad before GLFW
#include <iostream>
#include <cmath>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

// header files
#include "Shader.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"
#include "Camera.h"
#include "screen.h"
#include "texture.h"
#include "model.h"
#include "cube.hpp"

using namespace std; 

float mixVal = 0.5f;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float theta = 45.0f;

glm::mat4 transform = glm::mat4(1.0f);
Joystick mainJ(0);

Camera cameras[2] = {
    Camera(glm::vec3(0.0f, 0.0f, 3.0f)),
    Camera(glm::vec3(10.0f, 10.0f, 10.0f)),
};

int activeCam = 0;

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

// the screen object
Screen screen;

// Call back the frame buffer
static void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

void processInput(double dt) {
    if (Keyboard::key(GLFW_KEY_ESCAPE)) {
        cout << "ESC pressed" << endl;
        screen.setShouldClose(true);
    }

    // change the texture clicking up and down arrow
    if (Keyboard::key(GLFW_KEY_UP)) {
        mixVal += 0.0005f;
        if (mixVal > 1) {
            mixVal = 1.0f;
        }
    }
    if (Keyboard::key(GLFW_KEY_DOWN)) {
        mixVal -= 0.0005f;
        if (mixVal < 0) {
            mixVal = 0.0f;
        }
    }

    // toggle camera
    if (Keyboard::keyWentDown(GLFW_KEY_TAB)) {
        activeCam += (activeCam == 0) ? 1 : -1;
    }

    // camera move
    if (Keyboard::key(GLFW_KEY_W)) {
        cameras[activeCam].updateCameraPos(CameraDirection::FOWARD, dt);
    }
    if (Keyboard::key(GLFW_KEY_S)) {
        cameras[activeCam].updateCameraPos(CameraDirection::BACKWARD, dt);
    }
    if (Keyboard::key(GLFW_KEY_D)) {
        cameras[activeCam].updateCameraPos(CameraDirection::RIGHT, dt);
    }
    if (Keyboard::key(GLFW_KEY_A)) {
        cameras[activeCam].updateCameraPos(CameraDirection::LEFT, dt);
    }
    if (Keyboard::key(GLFW_KEY_SPACE)) {
        cameras[activeCam].updateCameraPos(CameraDirection::UP, dt);
    }
    if (Keyboard::key(GLFW_KEY_LEFT_SHIFT)) {
        cameras[activeCam].updateCameraPos(CameraDirection::DOWN, dt);
    }

    double dx = Mouse::getDX();
    double dy = Mouse::getDY();
    
    if (dx != 0 || dy != 0) {
        cameras[activeCam].updateCameraDirection(dx, dy);
    }

    double scrollDy = Mouse::getScrollDY();
    if (scrollDy != 0) {
        cameras[activeCam].updateCameraZoom(scrollDy);
    }
}

int main(void)
{	
    std::cout << "========== PROGRAM STARTING ==========" << std::endl;
    int success;
    char infoLog[512];

	// starting the window
	if (!glfwInit()) {
		return -1;
	}

    if (!screen.init()) {
        cout << "Window cannot be created" << endl;
        glfwTerminate();
        return -1;
    }

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		cout << "Failed to initialize GLAD";
		glfwTerminate();
		return -1;
	}

    screen.setParameters();
    glEnable(GL_DEPTH_TEST); // for 3d objects, we need to use depth test

    // call the shader class and insert tha path
    Shader shader(
        "D:/OneDrive/openGL_learning/openGL_learning/object.vs",
        "D:/OneDrive/openGL_learning/openGL_learning/object.fs"
    );

    Cube cube(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.75f));
    cube.init();

    // update the mouse and keyboard event
    mainJ.update();
    if (mainJ.isPresent()) {
        cout << mainJ.getName() << " is present " << endl;
    }
    else {
        cout << "The mainJ is not present" << endl;
    }

	while (!screen.shouldClose()) {
        glfwPollEvents();

        double currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;
       
        screen.update();

        processInput(deltaTime);

        // Rotate the image texture using getTime method (rotate it with time)
        shader.activate();

        // create transformation for screen
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        view = cameras[activeCam].getViewMatrix();
        projection = glm::perspective(glm::radians(cameras[activeCam].getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        // set mix color
        shader.setFloat("mixVal", mixVal); // mix color when pressing keys
        shader.setMat4("transform", transform); // the keyboard event

        cube.render(shader);
        screen.newFrame();
	}

	glfwTerminate();
	return 0;
}


