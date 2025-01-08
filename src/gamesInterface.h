
#ifndef GAME_INTERFACE
#define GAME_INTERFACE 

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class GameInterface {
public:
    virtual void updateLogic(GLFWwindow* window, glm::vec2 mousePos) = 0;
    virtual void draw(GLFWwindow* window, glm::mat4 proj) = 0;
};

#endif
