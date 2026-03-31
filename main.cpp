// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include <cmath>
// #include <iostream>

// // Vertex Shader
// const char* vertexShaderSource = R"(
// #version 330 core
// layout (location = 0) in vec3 aPos;

// uniform vec2 offset;

// void main() {
//     gl_Position = vec4(aPos.xy + offset, aPos.z, 1.0);
// }
// )";

// // Fragment Shader
// const char* fragmentShaderSource = R"(
// #version 330 core
// out vec4 FragColor;

// void main() {
//     FragColor = vec4(0.2, 0.8, 0.3, 1.0);
// }
// )";

// int main() {
//     // Init GLFW
//     if (!glfwInit()) {
//         std::cout << "Failed to init GLFW\n";
//         return -1;
//     }

//     GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle", NULL, NULL);
//     if (!window) {
//         std::cout << "Failed to create window\n";
//         glfwTerminate();
//         return -1;
//     }

//     glfwMakeContextCurrent(window);

//     // Init GLAD
//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//         std::cout << "Failed to initialize GLAD\n";
//         return -1;
//     }

//     // Viewport
//     glViewport(0, 0, 800, 600);

//     // Shaders
//     unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//     glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//     glCompileShader(vertexShader);

//     unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//     glCompileShader(fragmentShader);

//     // Shader program
//     unsigned int shaderProgram = glCreateProgram();
//     glAttachShader(shaderProgram, vertexShader);
//     glAttachShader(shaderProgram, fragmentShader);
//     glLinkProgram(shaderProgram);

//     glDeleteShader(vertexShader);
//     glDeleteShader(fragmentShader);

//     // Triangle vertices
//     float drone[] = {
//         -0.1f, -0.1f, 0.0f,
//          0.1f, -0.1f, 0.0f,
//          0.0f,  0.1f, 0.0f
//     };

//     float missile[] = {
//         -0.1f, -0.1f, 0.0f,
//          0.1f, -0.1f, 0.0f,
//          0.0f,  0.1f, 0.0f
//     };

//     // Drone vertices
//     float droneX = 0.5f;
//     float droneY = 0.0f;

//     // Missile vertices
//     float missileX = -0.5f;
//     float missileY = -0.5f;


//     unsigned int missileVAO, missileVBO;

//     glGenVertexArrays(1, &missileVAO);
//     glGenBuffers(1, &missileVBO);

//     glBindVertexArray(missileVAO);

//     glBindBuffer(GL_ARRAY_BUFFER, missileVBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(missile), missile, GL_STATIC_DRAW);

//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);

//     unsigned int VBO, VAO;
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);

//     glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(drone), drone, GL_STATIC_DRAW);

//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);

//     float posX = 0.0f;
//     int offsetLoc = glGetUniformLocation(shaderProgram, "offset");
  

//     // Render loop
//     while (!glfwWindowShouldClose(window)) {
//         glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);
        
//         posX += 0.001f;
//         if (posX > 1.0f || posX < -1.0f)
//         posX = -posX;

//         float time = glfwGetTime();

//         float prevDroneX = droneX;
//         float prevDroneY = droneY;

//         droneX = 0.5f * cos(time);
//         droneY = 0.5f * sin(time);

//         float velX = droneX - prevDroneX;
//         float velY = droneY - prevDroneY;   

//         float t = 20.0f;
//         float futureDroneX = droneX + velX * t;
//         float futureDroneY = droneY + velY * t;

//         //direction vector from missile to drone
//         float dirX = futureDroneX - missileX;
//         float dirY = futureDroneY - missileY;

//         //normalize the direction vector
//         float length = sqrt(dirX * dirX + dirY * dirY);

//         dirX /= length;
//         dirY /= length;

//         float speed = 0.003f;

//         //move misile towards drone
//         missileX += dirX * speed;
//         missileY += dirY * speed;

//         glUseProgram(shaderProgram);

//         //Drone
//         glUniform2f(offsetLoc, droneX, droneY);
//         glBindVertexArray(VAO);
//         glDrawArrays(GL_TRIANGLES, 0, 3);

//         //Missile
//         glUniform2f(offsetLoc, missileX, missileY);
//         glBindVertexArray(missileVAO);
//         glDrawArrays(GL_TRIANGLES, 0, 3);

//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     glfwTerminate();
//     return 0;
// }

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "entities/drone.h"
#include "entities/missile.h"
#include "systems/interception.h"
#include "renderer/renderer.h"

int main() {

    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "Sim", NULL, NULL);
    if (!window) return -1;

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD failed\n";
        return -1;
    }

    glViewport(0, 0, 800, 600);

    initRenderer();

    Drone drone;
    Missile missile;

    drone.x = 0.5f;
    drone.y = 0.0f;

    missile.x = -0.5f;
    missile.y = -0.5f;
    missile.speed = 0.003f;
    missile.angle = 0.0f;

    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float time = glfwGetTime();

        drone.update(time);
        updateInterception(drone, missile);

        drawObject(drone.x, drone.y, 0.2f, 0.8f, 0.3f);
        drawObject(missile.x, missile.y, 1.0f, 0.0f, 0.0f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}