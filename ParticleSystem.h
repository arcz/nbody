#pragma once
#include "Headers.h"
#include "Program.h"

/**
 * Main class of project, performs rendering of particles
 * and physical n-body simulation
 * http://en.wikipedia.org/wiki/N-body_simulation
 */
class ParticleSystem {
public:
  /**
   * Constructor, view and projection matrix is needed for
   * camera facing particles
   * @param viewMatrix cameras view matrix
   * @param projMatrix cameras projection matrix
   */
  ParticleSystem(const glm::mat4* const viewMatrix,
                 const glm::mat4* const projMatrix);

  /**
   * Draw instanced particles
   */
  void draw();

  /**
   * Move simulation to next step for given delta time
   * @param deltaTime delta time to next step
   */
  void update(float deltaTime);

protected:
  /**
   * Store view matrix to use for rendering
   */
  const glm::mat4* const mViewMatrix;

  /**
   * Store projection matrix to use for rendering
   */
  const glm::mat4* const mProjMatrix;

  /**
   * Particle rendering program
   */
  Program mProgram;

  /**
   * Vertex buffer for particle billboards
   */
  GLuint mBillboardVertexBuffer;

  /**
   * Buffer with positions of all particles
   */
  GLuint mParticlesPositionBuffer;

  /**
   * Buffer with colors of all particles
   */
  GLuint mParticlesColorBuffer;

  /**
   * Particles positions
   */
  std::vector<glm::vec3> mPositions;

  /**
   * Particles velocities
   */
  std::vector<glm::vec3> mVelocities;

  /**
   * Particles accelerations
   */
  std::vector<glm::vec3> mAccelerations;

  /**
   * Particles masses
   */
  std::vector<float> mMasses;
};
