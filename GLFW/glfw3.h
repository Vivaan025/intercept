#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GLFWwindow GLFWwindow;

int glfwInit(void);
void glfwTerminate(void);
GLFWwindow* glfwCreateWindow(int width, int height, const char* title, void* monitor, void* share);
void glfwMakeContextCurrent(GLFWwindow* window);
int glfwWindowShouldClose(GLFWwindow* window);
void glfwSwapBuffers(GLFWwindow* window);
void glfwPollEvents(void);
double glfwGetTime(void);
void* glfwGetProcAddress(const char* procname);

#ifdef __cplusplus
}
#endif