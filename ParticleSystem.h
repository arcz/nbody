#pragma once
#include "Headers.h"
#include "Program.h"

class ParticleSystem {
public:
  ParticleSystem(glm::mat4* viewMatrix, glm::mat4* projMatrix);
  void draw();
  void update(float deltaTime);

protected:
  glm::mat4* mViewMatrix;
  glm::mat4* mProjMatrix;
  Program mProgram;
  GLuint mBillboardVertexBuffer;
  GLuint mParticlesPositionBuffer;
  GLuint mParticlesColorBuffer;
  std::vector<glm::vec3> mPositions;
  std::vector<glm::vec3> mVelocities;
  std::vector<glm::vec3> mAccelerations;
  std::vector<float> mMasses;
};
