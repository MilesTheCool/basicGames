

#include <iostream>
#include <string>

#include "glad/glad.h"
#include <GLFW/glfw3.h>  // LET ME KNOW ASAP IF THIS CANNOT BE INCLUDED.

#include "gamesInterface.h"
#include "pong.h"
#include "ticTacToe.h"


/// @brief when window is resized by user, update OpenGL viewport to match the new window size
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {glViewport(0,0,width,height);}


int main() {

    // setup environment
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window
    GLFWwindow* window = glfwCreateWindow(800,600,"BasicGames", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    // setup GLAD loader
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return 1;
    }

    // set viewport
    glViewport(0,0,800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // tell it what function to use when screen size is changed

    // define each color for each game
    float ttt[]  = {};  // green

    std::cout << "Choose what to do:\n\t1. Pong\n\t2. Tic-Tac-Toe\n\t3. return to menu\n\tEnter ESCAPE to quit" << std::endl;
    while (!glfwWindowShouldClose(window)) {
        // draw window
        

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();

        // check inputs
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {glfwSetWindowShouldClose(window, true);}

        if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {        
            Pong* pong = new Pong();
            while (pong->isRunning()) {
                pong->updateLogic(window);
                pong->draw(window);
            }
            delete pong;
        }

        else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            TicTacToe* ttt = new TicTacToe();
            while (ttt->isRunning()) {
                ttt->updateLogic(window);
                ttt->draw(window);
            }
            delete ttt;
        }
    }
        //else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {currentGame = menu;}


    glfwTerminate();
    return 0;
}
