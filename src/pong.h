#ifndef PONG_CLASS
#define PONG_CLASS
#include "gamesInterface.h"

class Pong : public GameInterface {
public:
    Pong();
    void updateLogic(GLFWwindow* window);
    void draw(GLFWwindow* window);
    bool isRunning() {return running;}
    ~Pong();

private:
    const float bgColor[3] = {0.9f, 0.3f, 0.3f};
    bool running;
};

Pong::Pong() {
    running = true;
}

void Pong::updateLogic(GLFWwindow* window) {
    // stop running if q is pressed
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {running = false;}
}

void Pong::draw(GLFWwindow* window) {
    glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

Pong::~Pong() {
    // nothing to do yet
}


#endif