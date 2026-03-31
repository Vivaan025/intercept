#include "renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include <iostream>

// shaders
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec2 offset;

void main() {
    gl_Position = vec4(aPos.xy + offset, 0.0, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

uniform vec3 color;

void main() {
    FragColor = vec4(color, 1.0);
}
)";

unsigned int VAO, VBO;
unsigned int shaderProgram;
int offsetLoc;
int colorLoc;

void initRenderer() {

    // compile shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    offsetLoc = glGetUniformLocation(shaderProgram, "offset");
    colorLoc  = glGetUniformLocation(shaderProgram, "color");

    if (colorLoc == -1)
        std::cout << "color uniform not found!\n";

    if (offsetLoc == -1)
        std::cout << "offset uniform not found!\n";

    const int segments = 100;
    const float radius = 0.1f;

    std::vector<float> vertices;

    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * M_PI * i / segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0.0f);
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    offsetLoc = glGetUniformLocation(shaderProgram, "offset");
}

void drawObject(float x, float y, float colorR, float colorG, float colorB) {
    glUseProgram(shaderProgram);
    glUniform2f(offsetLoc, x, y);

    // int colorLoc = glGetUniformLocation(shaderProgram, "color");
    glUniform3f(colorLoc, colorR, colorG, colorB);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 102);
}