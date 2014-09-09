#pragma once
#include "Headers.h"
#include "Program.h"

class ParticleSystem {
public:
  ParticleSystem(const glm::mat4* const viewMatrix,
                 const glm::mat4* const projMatrix);
  void draw();
  void update(float deltaTime);

protected:
  const glm::mat4* const mViewMatrix;
  const glm::mat4* const mProjMatrix;
  Program mProgram;
  GLuint mBillboardVertexBuffer;
  GLuint mParticlesPositionBuffer;
  GLuint mParticlesColorBuffer;
  std::vector<glm::vec3> mPositions;
  std::vector<glm::vec3> mVelocities;
  std::vector<glm::vec3> mAccelerations;
  std::vector<float> mMasses;
};
