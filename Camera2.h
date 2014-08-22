#pragma once
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

class Camera2 {
public:
  glm::mat4 mViewMatrix;
  glm::mat4 mProjMatrix;
  glm::vec3 mPosition;
  glm::vec3 mTarget;

  Camera2(unsigned int width, unsigned int height) {
    mProjMatrix = glm::perspective<float>(45.0f, (float)width/(float)height, 1.0f, 1000.0f);
    mPosition = glm::vec3(0,0,0);
    mTarget = glm::vec3(0,0,0);
    rebuildView();
  }

  void move(glm::vec3 v) {
    mPosition += v;
    rebuildView();
  }

  void rebuildView() {
    mViewMatrix = glm::lookAt(mPosition, mTarget, glm::vec3(0,1,0));
  }
};