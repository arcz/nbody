#include <cstdlib>
#include <cstdio>
#include <iostream>
#define GLM_FORCE_RADIANS
#include "Headers.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Program.h"
#include "Camera2.h"
#include "ParticleSystem.h"
// constants
const glm::vec2 SCREEN_SIZE(1200, 800);

int main() {

  if( !glfwInit() ) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  glfwSetErrorCallback([](int error, const char* description) { std::cerr << description << std::endl; });

  glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

  // Open a window and create its OpenGL context
  GLFWwindow* window; // (In the accompanying source code, this variable is global)
  window = glfwCreateWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, "nbody", NULL, NULL);
  if(window == NULL) {
    glfwTerminate();
    return -1;
  }

  std::cerr << __LINE__ << ": " << glGetError() << std::endl;

  glfwMakeContextCurrent(window); // Initialize GLEW
  glewExperimental=true; // Needed in core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n"); return -1; }

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // print out some info about the graphics drivers
  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
  std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  // load vertex and fragment shaders into opengl
  std::vector<Shader> shaders;
  shaders.push_back(Shader::createFromFile("./vertex_shader.glsl", GL_VERTEX_SHADER));
  shaders.push_back(Shader::createFromFile("./fragment_shader.glsl", GL_FRAGMENT_SHADER));
  Program program(shaders);

  Camera2 camera(SCREEN_SIZE.x, SCREEN_SIZE.y);
  camera.move(glm::vec3(1.0f, 0, -5.0f));

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint vertexBuffer, indexBuffer;
  glGenBuffers(1, &vertexBuffer);
  glGenBuffers(1, &indexBuffer);
  GLuint indices[] = {0, 1, 2};
  GLfloat vertices[] = {
    0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 1.0f
  };

  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  std::cerr << __FILE__ << ":" << __LINE__ << ": " << glGetError() << std::endl;

  ParticleSystem particleSystem(&camera.mViewMatrix, &camera.mProjMatrix);

  double deltaTime = 1.0;
  const float cameraSpeed = 200.0f;

  while (!glfwWindowShouldClose(window))
  {
    float old_time = glfwGetTime();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
      camera.move(glm::vec3(0, 0, 1) * (float)deltaTime * cameraSpeed);

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
      camera.move(glm::vec3(0, 0, -1) * (float)deltaTime * cameraSpeed);

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
      camera.move(glm::vec3(1, 0, 0) * (float)deltaTime * cameraSpeed);

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
      camera.move(glm::vec3(-1, 0, 0) * (float)deltaTime * cameraSpeed);


    // clear everything
    glClearColor(0.1, 0.2, 0.3, 1); // black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // bind the program (the shaders)
    program.use();

    program.setUniform("model", glm::rotate(glm::mat4(), 0.0f, glm::vec3(0,1,0)));
    program.setUniform("view", camera.mViewMatrix);
    program.setUniform("proj", camera.mProjMatrix);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glVertexAttribPointer(program.attrib("position"), 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(program.attrib("position"));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    program.stopUsing();

    particleSystem.draw();

    glfwSwapBuffers(window);
    glfwPollEvents();

    deltaTime = glfwGetTime() - old_time;

    particleSystem.update(deltaTime);
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
