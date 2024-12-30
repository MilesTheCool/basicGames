
#ifndef GAME_INTERFACE
#define GAME_INTERFACE 

#include "glad/glad.h"
#include "../includes/glfw3.h"

class GameInterface {
public:
    virtual void updateLogic(GLFWwindow* window) = 0;
    virtual void draw(GLFWwindow* window) = 0;
};

#endif
