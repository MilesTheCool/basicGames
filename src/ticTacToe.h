
#ifndef TIC_TAC_TOE_CLASS
#define TIC_TAC_TOE_CLASS
#include "gamesInterface.h"

class TicTacToe : public GameInterface {
public:
    TicTacToe();
    void updateLogic(GLFWwindow* window);
    void draw(GLFWwindow* window);
    bool isRunning() {return running;}
    ~TicTacToe();

private:
    const float bgColor[3] = {0.2f, 0.9f, 0.3f};
    bool running;
};

TicTacToe::TicTacToe() {
    running = true;
}

void TicTacToe::updateLogic(GLFWwindow* window) {
    // stop running if q is pressed
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {running = false;}
}

void TicTacToe::draw(GLFWwindow* window) {
    glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

TicTacToe::~TicTacToe() {
    // nothing to do yet
}


#endif