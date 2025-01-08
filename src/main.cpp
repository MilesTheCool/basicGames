

#include <iostream>
#include <string>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "gamesInterface.h"
#include "pong.h"
#include "ticTacToe.h"
#include "button.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


/// @brief when window is resized by user, update OpenGL viewport to match the new window size
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

glm::vec2 getModifiedMousePos(GLFWwindow* window);

int SCREEN_WIDTH = 1024;
int SCREEN_HEIGHT = 576;

int main() {

    
    // setup environment
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window
    GLFWwindow* window = glfwCreateWindow(1024,576,"BasicGames", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwSetWindowAspectRatio(window, 16, 9); // lock window to a 16:9 aspect ratio
    glfwSetWindowSizeLimits(window, 576, 324, GLFW_DONT_CARE, GLFW_DONT_CARE);  // set minimum size, no maximum
    glfwMakeContextCurrent(window);

    // setup GLAD loader
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return 1;
    }

    // set viewport
    glViewport(0,0,1024, 576);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // tell it what function to use when screen size is changed

    // set projection
    glm::mat4 projection = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -0.1f, 100.0f);

    // set colors
    glm::vec3 pongColor{0.9f, 0.3f, 0.3f};
    glm::vec3 tttColor{0.2f, 0.9f, 0.3f};
    glm::vec3 menuColor{0.2f, 0.3f, 0.3f};

    // create button
    Button pongButton = Button(glm::vec2(0,1), glm::vec2(1,1), pongColor);
    Button tttButton = Button(glm::vec2(15,1), glm::vec2(1,1), tttColor);

    while (!glfwWindowShouldClose(window)) {
        // draw window
        glClearColor(menuColor.x, menuColor.y, menuColor.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        pongButton.draw(projection);
        tttButton.draw(projection);

        glfwSwapBuffers(window);
        glfwPollEvents();

        // get and display mouse pos
        
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            glm::vec2 mousePos = getModifiedMousePos(window);
            if (pongButton.isClicked(mousePos.x, mousePos.y)) {
                Pong* pong = new Pong();
                while (pong->isRunning()) {
                    pong->updateLogic(window, getModifiedMousePos(window));
                    pong->draw(window, projection);
                }
                delete pong;
            }
            else if (tttButton.isClicked(mousePos.x, mousePos.y)){
               TicTacToe* ttt = new TicTacToe();
                while (ttt->isRunning()) {
                    ttt->updateLogic(window, getModifiedMousePos(window));
                    ttt->draw(window, projection);
                }
                delete ttt;
            }
        }
    }

    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0,0,width,height);
    SCREEN_HEIGHT = height;
    SCREEN_WIDTH = width;
}


glm::vec2 getModifiedMousePos(GLFWwindow* window) {
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    // force x to be [0,16] based on screen width
    x = (x * 16) / SCREEN_WIDTH;

    // force y to be [0,9] based on screen height
    y = (y * 9) / SCREEN_HEIGHT;

    // y 0 is top 9 is bottom, invert it so 0 is bottom 9 is top
    y = 9 - y;

    return glm::vec2(x,y);
}