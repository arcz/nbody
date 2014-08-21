#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

int main() {

  if( !glfwInit() ) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  glfwSetErrorCallback([](int error, const char* description) { std::cerr << description << std::endl; });

  glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
  //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
  //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

  // Open a window and create its OpenGL context
  GLFWwindow* window; // (In the accompanying source code, this variable is global)
  window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);
  if( window == NULL ) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window); // Initialize GLEW
  glewExperimental=true; // Needed in core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    return -1;
  }

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  glfwSetKeyCallback(window, key_callback);
  while (!glfwWindowShouldClose(window)) 
  {
    glClearColor(0.1,0.2,0.3,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glTranslatef(0, 0, -2);
    glBegin(GL_POLYGON);
        glColor3f(1.0, 0.2, 0.2);
        glVertex3f(0.25, 0.25, 0.0);
        glVertex3f(0.75, 0.25, 0.0);
        glVertex3f(0.75, 0.75, 0.0);
        glVertex3f(0.25, 0.75, 0.0);
    glEnd();
    glFlush();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
