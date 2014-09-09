#include <cstdlib>
#include <cstdio>
#include <iostream>
#define GLM_FORCE_RADIANS
#include "Headers.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Program.h"
#include "ParticleSystem.h"
#include "Camera.h"

// constants
const glm::vec2 SCREEN_SIZE(1400, 800);

int main() {

  if( !glfwInit() ) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  glfwSetErrorCallback([](int error, const char* description) {
    std::cerr << description << std::endl;
  });

  glfwWindowHint(GLFW_SAMPLES, 4); // 4x multisampling
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for Mac OS
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Disalbe old OpenGL

  // Open a window and create its OpenGL context
  GLFWwindow* window;
  window = glfwCreateWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, "nbody", NULL, NULL);
  if(window == NULL) {
    glfwTerminate();
    return -1;
  }

  // Check for errors until here
  std::cerr << __LINE__ << ": " << glGetError() << std::endl;

  glfwMakeContextCurrent(window); // Initialize GLEW
  glewExperimental = true; // Needed in core profile
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // print out some info about the graphics drivers
  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
  std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

  // Enable depth testing so particles are rendered properly
  // no matter what order rendered
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  Camera camera(SCREEN_SIZE.x, SCREEN_SIZE.y);
  camera.move(glm::vec3(1.0f, 0, -5.0f));

  // Set Vertex Array Object
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Check for OpenGL errors until this line
  std::cerr << __FILE__ << ":" << __LINE__ << ": " << glGetError() << std::endl;

  ParticleSystem particleSystem(&camera.viewMatrix(), &camera.projMatrix());

  // time of rendering previous frame
  float deltaTime = 1.0;
  const float cameraSpeed = 200.0f;
  float time_buffer = 0.0f;
  char str_buffer[10];

  // Main loop, runs forever until exit key pressed
  while (!glfwWindowShouldClose(window))
  {
    time_buffer += deltaTime;
    if (time_buffer > 1.0f) {
      sprintf(str_buffer, "FPS: %f", 1.0f/deltaTime);
      glfwSetWindowTitle(window, str_buffer);
      time_buffer = 0.0f;
    }

    float old_time = glfwGetTime();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
      camera.move(glm::vec3(0, 0, 1) * (float)deltaTime * cameraSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
      camera.move(glm::vec3(0, 0, -1) * (float)deltaTime * cameraSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
      camera.move(glm::vec3(1, 0, 0) * (float)deltaTime * cameraSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
      camera.move(glm::vec3(-1, 0, 0) * (float)deltaTime * cameraSpeed);
    }

    // clear color buffer and depth buffer
    glClearColor(0, 0, 0, 1); // black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    particleSystem.draw();

    // about double buffering
    // http://en.wikipedia.org/wiki/Multiple_buffering
    glfwSwapBuffers(window);
    glfwPollEvents();

    // calculate delta time
    deltaTime = glfwGetTime() - old_time;

    // move simulation step forward
    particleSystem.update(deltaTime);
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
