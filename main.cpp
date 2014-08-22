#include <cstdlib>
#include <cstdio>
#include <iostream>
#define GLM_FORCE_RADIANS
#include "Headers.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Program.h"
#include "Camera.h"

// constants
const glm::vec2 SCREEN_SIZE(800, 600);
// globals
Program* gProgram = NULL;
Camera gCamera;
GLuint gVAO = 0;
GLuint gVBO = 0;
GLfloat gDegreesRotated = 0.0f;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

static void LoadShaders() {
  std::vector<Shader> shaders;
  shaders.push_back(Shader::createFromFile("./vertex_shader.glsl", GL_VERTEX_SHADER));
  shaders.push_back(Shader::createFromFile("./fragment_shader.glsl", GL_FRAGMENT_SHADER));
  gProgram = new Program(shaders);
}

// loads a cube into the VAO and VBO globals: gVAO and gVBO
static void LoadCube() {
  // make and bind the VAO
  glGenVertexArrays(1, &gVAO);
  glBindVertexArray(gVAO);
  // make and bind the VBO
  glGenBuffers(1, &gVBO);
  glBindBuffer(GL_ARRAY_BUFFER, gVBO);
  // Make a cube out of triangles (two triangles per side)
  GLfloat vertexData[] = {
    // X Y Z U V
    // bottom
    -1.0f,-1.0f,-1.0f, 0.0f, 0.0f,
    1.0f,-1.0f,-1.0f, 1.0f, 0.0f,
    -1.0f,-1.0f, 1.0f, 0.0f, 1.0f,
    1.0f,-1.0f,-1.0f, 1.0f, 0.0f,
    1.0f,-1.0f, 1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f, 0.0f, 1.0f,
    // top
    -1.0f, 1.0f,-1.0f, 0.0f, 0.0f,
    -1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f,-1.0f, 1.0f, 0.0f,
    1.0f, 1.0f,-1.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    // front
    -1.0f,-1.0f, 1.0f, 1.0f, 0.0f,
    1.0f,-1.0f, 1.0f, 0.0f, 0.0f,
    -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    // back
    -1.0f,-1.0f,-1.0f, 0.0f, 0.0f,
    -1.0f, 1.0f,-1.0f, 0.0f, 1.0f,
    1.0f,-1.0f,-1.0f, 1.0f, 0.0f,
    1.0f,-1.0f,-1.0f, 1.0f, 0.0f,
    -1.0f, 1.0f,-1.0f, 0.0f, 1.0f,
    1.0f, 1.0f,-1.0f, 1.0f, 1.0f,
    // left
    -1.0f,-1.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, 1.0f,-1.0f, 1.0f, 0.0f,
    -1.0f,-1.0f,-1.0f, 0.0f, 0.0f,
    -1.0f,-1.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f, 1.0f, 0.0f,
    // right
    1.0f,-1.0f, 1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f, 1.0f, 0.0f,
    1.0f, 1.0f,-1.0f, 0.0f, 0.0f,
    1.0f,-1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 0.0f, 1.0f
  };
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
  // connect the xyz to the "vert" attribute of the vertex shader
  glEnableVertexAttribArray(gProgram->attrib("vert"));
  glVertexAttribPointer(gProgram->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), NULL);
  // connect the uv coords to the "vertTexCoord" attribute of the vertex shader
  //glEnableVertexAttribArray(gProgram->attrib("vertTexCoord"));
  //glVertexAttribPointer(gProgram->attrib("vertTexCoord"), 2, GL_FLOAT, GL_TRUE, 5*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));
  // unbind the VAO
  glBindVertexArray(0);
}


// update the scene based on the time elapsed since last update
void Update(float secondsElapsed, GLFWwindow* window) {
  //rotate the cube
  const GLfloat degreesPerSecond = 180.0f;
  gDegreesRotated += secondsElapsed * degreesPerSecond;
  while(gDegreesRotated > 360.0f) gDegreesRotated -= 360.0f;

  //move position of camera based on WASD keys, and XZ keys for up and down
  const float moveSpeed = 2.0; //units per second
  if(glfwGetKey(window, 'S')){
    gCamera.offsetPosition(secondsElapsed * moveSpeed * -gCamera.forward());
  } else if(glfwGetKey(window, 'W')){
    gCamera.offsetPosition(secondsElapsed * moveSpeed * gCamera.forward());
  }
  if(glfwGetKey(window, 'A')){
    gCamera.offsetPosition(secondsElapsed * moveSpeed * -gCamera.right());
  } else if(glfwGetKey(window, 'D')){
    gCamera.offsetPosition(secondsElapsed * moveSpeed * gCamera.right());
  }
  if(glfwGetKey(window, 'Z')){
    gCamera.offsetPosition(secondsElapsed * moveSpeed * -glm::vec3(0,1,0));
  } else if(glfwGetKey(window, 'X')){
    gCamera.offsetPosition(secondsElapsed * moveSpeed * glm::vec3(0,1,0));
  }

  //rotate camera based on mouse movement
  const float mouseSensitivity = 0.1;
  double mouseX, mouseY;
  glfwGetCursorPos(window, &mouseX, &mouseY);
  gCamera.offsetOrientation(mouseSensitivity * mouseY, mouseSensitivity * mouseX);
  glfwSetCursorPos(window, 0, 0); //reset the mouse, so it doesn't go out of the window
}



int main() {

  if( !glfwInit() ) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  glfwSetErrorCallback([](int error, const char* description) { std::cerr << description << std::endl; });

  glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
  //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
  //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

  // Open a window and create its OpenGL context
  GLFWwindow* window; // (In the accompanying source code, this variable is global)
  window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);
  if( window == NULL ) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window); // Initialize GLEW
  glewExperimental=true; // Needed in core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n"); return -1; }

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  glfwSetKeyCallback(window, key_callback);


  // print out some info about the graphics drivers
  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
  std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

  // OpenGL settings
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  // load vertex and fragment shaders into opengl
  LoadShaders();
  // create buffer and fill it with the points of the triangle
  LoadCube();
  // setup gCamera
  gCamera.setPosition(glm::vec3(0,0,4));
  gCamera.setViewportAspectRatio(SCREEN_SIZE.x / SCREEN_SIZE.y);

  while (!glfwWindowShouldClose(window))
  {
    // clear everything
    glClearColor(0, 0, 0, 1); // black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // bind the program (the shaders)
    gProgram->use();
    // set the "camera" uniform
    gProgram->setUniform("camera", gCamera.matrix());
    // set the "model" uniform in the vertex shader, based on the gDegreesRotated global
    gProgram->setUniform("model", glm::rotate(glm::mat4(), gDegreesRotated, glm::vec3(0,1,0)));
    // bind the texture and set the "tex" uniform in the fragment shader
    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, gTexture->object());
    //gProgram->setUniform("tex", 0); //set to 0 because the texture is bound to GL_TEXTURE0
    // bind the VAO (the triangle)
    glBindVertexArray(gVAO);
    // draw the VAO
    glDrawArrays(GL_TRIANGLES, 0, 6*2*3);
    // unbind the VAO, the program and the texture
    glBindVertexArray(0);
    //glBindTexture(GL_TEXTURE_2D, 0);
    gProgram->stopUsing();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
