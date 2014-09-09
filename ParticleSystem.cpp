#include "ParticleSystem.h"
#include <iostream>
#include <random>
#include <thread>

static const unsigned MAX_PARTICLES = 500;

ParticleSystem::ParticleSystem(glm::mat4* viewMatrix, glm::mat4* projMatrix) :
  mProjMatrix(projMatrix),
  mViewMatrix(viewMatrix)
{
  // The VBO containing the 4 vertices of the particles.
  // Thanks to instancing, they will be shared by all particles.
  static const GLfloat g_vertex_buffer_data[] = {
     -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
     -0.5f,  0.5f, 0.0f,
      0.5f,  0.5f, 0.0f,
  };

  glGenBuffers(1, &mBillboardVertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, mBillboardVertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

  // The VBO containing the positions and sizes of the particles
  glGenBuffers(1, &mParticlesPositionBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, mParticlesPositionBuffer);
  // Initialize with empty (NULL) buffer : it will be updated later, each frame.
  glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLES * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

  // The VBO containing the colors of the particles
  glGenBuffers(1, &mParticlesColorBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, mParticlesColorBuffer);
  // Initialize with empty (NULL) buffer : it will be updated later, each frame.
  glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLES * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);

  // load vertex and fragment shaders into opengl
  std::vector<Shader> shaders;
  shaders.push_back(Shader::createFromFile("./particles.vertexshader", GL_VERTEX_SHADER));
  shaders.push_back(Shader::createFromFile("./particles.fragmentshader", GL_FRAGMENT_SHADER));
  mProgram.setShaders(shaders);

  // RANDOMIZE
  std::random_device rd;
  std::default_random_engine gen(rd());
  std::uniform_real_distribution<float> dist(-100.0f, 100.0f);
  std::uniform_real_distribution<float> dist2(10.0f, 1000.0f);
  std::uniform_real_distribution<float> dist3(0.001, 1.0f);

  for(int i = 0; i < MAX_PARTICLES/2; i++) {
    mPositions.push_back(glm::vec3(-150, 0, 0) + glm::vec3(dist(gen), dist(gen), dist(gen)));
    mVelocities.push_back(glm::vec3(dist3(gen), dist3(gen), dist3(gen)));
    mAccelerations.push_back(glm::vec3(0, 0, 0));
    mMasses.push_back(dist2(gen));
  }

  for(int i = MAX_PARTICLES/2; i < MAX_PARTICLES; i++) {
    mPositions.push_back(glm::vec3(150, 0, 0) + glm::vec3(dist(gen), dist(gen), dist(gen)));
    mVelocities.push_back(glm::vec3(dist3(gen), dist3(gen), dist3(gen)));
    mAccelerations.push_back(glm::vec3(0, 0, 0));
    mMasses.push_back(dist2(gen));
  }

  std::cerr << __FILE__ << ":" << __LINE__ << ": " << glGetError() << std::endl;
}

void ParticleSystem::draw() {
  glBindBuffer(GL_ARRAY_BUFFER, mParticlesPositionBuffer);
  glBufferData(GL_ARRAY_BUFFER, mPositions.size() * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
  glBufferSubData(GL_ARRAY_BUFFER, 0, mPositions.size() * sizeof(GLfloat) * 4, mPositions.data());

  glBindBuffer(GL_ARRAY_BUFFER, mParticlesColorBuffer);
  glBufferData(GL_ARRAY_BUFFER, mPositions.size() * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
  glBufferSubData(GL_ARRAY_BUFFER, 0, mPositions.size() * sizeof(GLfloat) * 4, mAccelerations.data());

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Use our shader
  mProgram.use();

  // Bind our texture in Texture Unit 0
  //glActiveTexture(GL_TEXTURE0);
  //glBindTexture(GL_TEXTURE_2D, Texture);
  // Set our "myTextureSampler" sampler to user Texture Unit 0
  //glUniform1i(TextureID, 0);

  // Same as the billboards tutorial
  glUniform3f(mProgram.uniform("CameraRight_worldspace"), (*mViewMatrix)[0][0], (*mViewMatrix)[1][0], (*mViewMatrix)[2][0]);
  glUniform3f(mProgram.uniform("CameraUp_worldspace"), (*mViewMatrix)[0][1], (*mViewMatrix)[1][1], (*mViewMatrix)[2][1]);

  glm::mat4 ViewProjectionMatrix = (*mProjMatrix) * (*mViewMatrix);
  glUniformMatrix4fv(mProgram.uniform("VP"), 1, GL_FALSE, &ViewProjectionMatrix[0][0]);

  // 1rst attribute buffer : vertices
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, mBillboardVertexBuffer);
  glVertexAttribPointer(
    0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
    3,                  // size
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    0,                  // stride
    (void*)0            // array buffer offset
  );

  // 2nd attribute buffer : positions of particles' centers
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, mParticlesPositionBuffer);
  glVertexAttribPointer(
    1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
    3,                                // size : x + y + z => 3
    GL_FLOAT,                         // type
    GL_FALSE,                         // normalized?
    0,                                // stride
    (void*)0                          // array buffer offset
  );

  // 3rd attribute buffer : particles' colors
  glEnableVertexAttribArray(2);
  glBindBuffer(GL_ARRAY_BUFFER, mParticlesColorBuffer);
  glVertexAttribPointer(
    2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
    3,                                // size : r + g + b + a => 4
    GL_FLOAT,                 // type
    GL_TRUE,                          // normalized?    *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***
    0,                                // stride
    (void*)0                          // array buffer offset
  );

  // These functions are specific to glDrawArrays*Instanced*.
  // The first parameter is the attribute buffer we're talking about.
  // The second parameter is the "rate at which generic vertex attributes advance when rendering multiple instances"
  // http://www.opengl.org/sdk/docs/man/xhtml/glVertexAttribDivisor.xml
  glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices -> 0
  glVertexAttribDivisor(1, 1); // positions : one per quad (its center)                 -> 1
  glVertexAttribDivisor(2, 1); // color : one per quad                                  -> 1

  // Draw the particules !
  // This draws many times a small triangle_strip (which looks like a quad).
  // This is equivalent to :
  // for(i in mPositions.size()) : glDrawArrays(GL_TRIANGLE_STRIP, 0, 4),
  // but faster.
  glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, mPositions.size());

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}

// stała grawitacji
static constexpr float G = 6.673848080E-3;
// dokładność działań na double
static constexpr float EPS2 = 1.0E+2;

void mThread(std::vector<glm::vec3>& mPositions,std::vector<float>& mMasses,std::vector<glm::vec3>& mAccelerations,std::vector<glm::vec3>& mVelocities,unsigned start,unsigned end,float deltaTime){
for(unsigned i=start; i<end; i++){
	mAccelerations[i] = glm::vec3(0.0f, 0.0f, 0.0f);
	for(unsigned j=0; j<MAX_PARTICLES; j++){
      if (i == j) continue;
      float rx = mPositions[j].x - mPositions[i].x;
      float ry = mPositions[j].y - mPositions[i].y;
      float rz = mPositions[j].z - mPositions[i].z;

      float distSqr = rx * rx + ry * ry + rz * rz + EPS2;
      float distSixth = distSqr * distSqr * distSqr;
      float invDistCube = 1.0f/sqrtf(distSixth);
      float s = mMasses[i] * invDistCube;
      mAccelerations[i].x += rx * s;
      mAccelerations[i].y += ry * s;
      mAccelerations[i].z += rz * s;
	}
    mVelocities[i] += mAccelerations[i] * deltaTime;
    mPositions[i] += mVelocities[i] * deltaTime;
} 

}

void ParticleSystem::update(float deltaTime) {
	std::thread ts[4];
    	ts[0] = std::thread(mThread,std::ref(mPositions),std::ref(mMasses),std::ref(mAccelerations),std::ref(mVelocities),0,MAX_PARTICLES/4,deltaTime);
	ts[1] = std::thread(mThread,std::ref(mPositions),std::ref(mMasses),std::ref(mAccelerations),std::ref(mVelocities),MAX_PARTICLES/4,MAX_PARTICLES/2,deltaTime);
	ts[2] = std::thread(mThread,std::ref(mPositions),std::ref(mMasses),std::ref(mAccelerations),std::ref(mVelocities),MAX_PARTICLES/2,3*MAX_PARTICLES/4,deltaTime);
	ts[3] = std::thread(mThread,std::ref(mPositions),std::ref(mMasses),std::ref(mAccelerations),std::ref(mVelocities),3*MAX_PARTICLES/4,MAX_PARTICLES,deltaTime);

	for(auto& t : ts) t.join();
}


