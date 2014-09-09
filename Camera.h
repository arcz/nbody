#pragma once
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

/**
 * Class representing basic camera
 */
class Camera {
public:
  /**
   * Constructor, calculated projection matrix
   * @param width width of viewport
   * @param height height of viewport
   */
  Camera(unsigned int width, unsigned int height);

  /**
   * Getter for view matrix
   * @return view matrix
   */
  const glm::mat4& viewMatrix();

  /**
   * Getter for projection matrix
   * @return projection matrix
   */
  const glm::mat4& projMatrix();

  /**
   * Move camera by vector relative to current position
   * @param v vector of distance to be added
   */
  void move(const glm::vec3& v);

  /**
   * Make camera look at specific target point
   * @param target point in space where to look at
   */
  void target(const glm::vec3& target);

private:
  /**
   * View matrix
   * http://3dgep.com/understanding-the-view-matrix/
   */
  glm::mat4 mViewMatrix;

  /**
   * Projection matrix
   * http://www.songho.ca/opengl/gl_projectionmatrix.html
   */
  glm::mat4 mProjMatrix;

  /**
   * Current position of camera
   */
  glm::vec3 mPosition;

  /**
   * Current target of camera
   */
  glm::vec3 mTarget;

  /**
   * Rebuild view matrix based on current position and target
   */
  void rebuildView();
};