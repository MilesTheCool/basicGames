
#ifndef TIC_TAC_TOE_CLASS
#define TIC_TAC_TOE_CLASS
#include "gamesInterface.h"
#include "button.h"
#include <glm/glm.hpp>


class TicTacToe : public GameInterface {
public:
    TicTacToe();
    void updateLogic(GLFWwindow* window, glm::vec2 mousePos);
    void draw(GLFWwindow* window, glm::mat4 proj);
    bool isRunning() {return running;}
    ~TicTacToe();

private:
    const float bgColor[3] = {0.2f, 0.9f, 0.3f};
    bool running;
    Button button{glm::vec2(1, 8), glm::vec2(1,1), glm::vec3(0.2f, 0.3f, 0.3f)};
};

TicTacToe::TicTacToe(){
    running = true;
    Button button{glm::vec2(1, 8), glm::vec2(1,1), glm::vec3(0.2f, 0.3f, 0.3f)};
}

void TicTacToe::updateLogic(GLFWwindow* window, glm::vec2 mousePos) {
    // stop running if q is pressed
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {running = false;}

    if (glfwWindowShouldClose(window)) {running = false;}

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        if (button.isClicked(mousePos.x, mousePos.y)) {running = false;}

    }
}

void TicTacToe::draw(GLFWwindow* window, glm::mat4 proj) {
    glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    button.draw(proj);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

TicTacToe::~TicTacToe() {
    // nothing to do yet
}


#endif