#ifndef BUTTON_CLASS
#define BUTTON_CLASS

#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class Button {
public:
    Button(glm::vec2 position, glm::vec2 size, glm::vec3 color);
    
    void draw(glm::mat4 projection);

    bool isClicked(float x, float y) {return (x >= left && x <= left + width) && (y >= bottom && y <= bottom + height);}

private:

    /// @brief  create a compiled and linked shader program. Assume it always works
    void createShader();


    unsigned int shaderProgram;
    unsigned int VBO, VAO, EBO;
    float left, bottom, width, height;

    const char* VERTEX_SHADER_SOURCE = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform mat4 projection;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = projection * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    const char* FRAGMENT_SHADER_SOURCE = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 color;\n"
    "void main()\n"
    "{\n"
    "   FragColor = color;\n"
    "}\n\0";


};

Button::Button(glm::vec2 position, glm::vec2 size, glm::vec3 color){
    createShader();

    // update color in shader
    glUseProgram(shaderProgram);
    glUniform4f(glGetUniformLocation(shaderProgram, "color"), color.x, color.y, color.z, 1.0f);

    left = position.x;
    bottom = position.y;
    width = size.x;
    height = size.y;

    // get four corners based on supplied points
    float vertices[] = {
        left + width, bottom + height, 0.0f, // top right
        left + width, bottom, 0.0f,          // bottom right
        left, bottom, 0.0f,                  // bottom left
        left, bottom + height, 0.0f          // top left
    };

    // spit rectangle into two triangles to draw
    unsigned int indices[] = {
        0, 1, 3, 
        1, 2, 3 
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Button::createShader() {
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &VERTEX_SHADER_SOURCE, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &FRAGMENT_SHADER_SOURCE, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

void Button::draw(glm::mat4 projection) {
    glUseProgram(shaderProgram);

    // update projection
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

#endif