#pragma once
#include "Headers.h"
#include "Program.h"

class PhysicsSystem {
public:
  virtual void update(float deltaTime) = 0;
};

class ParticleSystem {
public:
  virtual void draw() = 0;

private:
  Program mProgram; 
  std::vector<glm::vec3> mPositions;
};

/**
  For testing puposes
*/
class FixedParticleSystem : public ParticleSystem {
public:
  virtual void draw();
  void randomize(unsigned count = 1000, glm::vec3 Position = glm::vec3(0,0,0));
};

class NbodyParticleSystem : public ParticleSystem, public PhysicsSystem {
public:
  virtual void draw();
  virtual void update(float deltaTime);
private:
  std::vector<glm::vec3> mVelocities;
  std::vector<glm::vec3> mAccelerations;
};

