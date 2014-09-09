#include "Camera.h"

Camera::Camera(unsigned int width, unsigned int height) {
  mProjMatrix = glm::perspective<float>(45.0f, (float)width / (float)height,
                                            1.0f, 1000.0f);
  mPosition = glm::vec3(0,0,0);
  mTarget = glm::vec3(0,0,0);
  rebuildView();
}

const glm::mat4& Camera::viewMatrix() {
  return mViewMatrix;
}

const glm::mat4& Camera::projMatrix() {
  return mProjMatrix;
}

void Camera::move(const glm::vec3& v) {
  mPosition += v;
  rebuildView();
}

void Camera::target(const glm::vec3& target) {
  mTarget = target;
  rebuildView();
}

void Camera::rebuildView() {
  mViewMatrix = glm::lookAt(mPosition, mTarget, glm::vec3(0, 1, 0));
}
