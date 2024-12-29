
#ifndef GAME_INTERFACE
#define GAME_INTERFACE 

#include "glad/glad.h"
#include <GLFW/glfw3.h>

class GameInterface {
public:
    virtual void updateLogic(GLFWwindow* window) = 0;
    virtual void draw(GLFWwindow* window) = 0;
};

#endif