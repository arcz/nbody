#pragma once
#define GLM_FORCE_RADIANS

#include <vector>
#include <glm/glm.hpp>
#include "Headers.h"
#include "Shader.h"

/**
 * This class represents OpenGL program
 * http://www.opengl.org/wiki/Program_Object
 */
class Program {
public:
  /**
   * Costructor
   */
  Program();
  /**
   * Constructor that takes shaders to be linked
   */
  Program(const std::vector<Shader>& shaders);
  /**
   * Destroy program, deleted OpenGL program object
   */
  ~Program();

  /**
   * Links whole program for given shaders, typically
   * there should be passed vertex shader and fragment shader
   * @param shaders vector of compiled shaders @see Shader
   */
  void setShaders(const std::vector<Shader>& shaders);

  /**
   * Getter for OpenGL program object identificator
   * @return OpenGL program identificator
   */
  GLuint object() const;

  /**
   * Set shader to be used for subsequent draw calls
   */
  void use() const;

  /**
   * Check if this shader is used for rendering now
   * @return true if in use, false when not using
   */
  bool isInUse() const;

  /**
   * Stop using shader for drawing, opposite of use
   */
  void stopUsing() const;

  /**
   * Getter for index attribute declared in shader code
   * http://www.opengl.org/wiki/Vertex_Attribute
   * @attributeName Name of attribute declared in shader
   * @return Attribute index for provided name
   */
  GLint attrib(const GLchar* attributeName) const;

  /**
   * Getter for index of uniform declared in shader code
   * http://www.opengl.org/wiki/Uniform_(GLSL)
   * @uniformName Name of uniform declared in shader
   * @return Uniform index for provided name
   */
  GLint uniform(const GLchar* uniformName) const;

  /**
   * Bind 3x3 matrix to shader uniform
   * @param uniformName name of uniform in shader code
   * @param matrix 3x3 matrix
   */
  void setUniform(const GLchar* uniformName, const glm::mat3& matrix);

  /**
   * Bind 4x4 matrix to shader uniform
   * @param uniformName name of uniform in shader code
   * @param matrix 4x4 matrix
   */
  void setUniform(const GLchar* uniformName, const glm::mat4& matrix);

  /**
   * Bind 3-dim vector to shader uniform
   * @param uniformName name of uniform in shader code
   * @param vector 3-dim vector
   */
  void setUniform(const GLchar* uniformName, const glm::vec3& vector);

  /**
   * Bind 4-dim vector to shader uniform
   * @param uniformName name of uniform in shader code
   * @param vector 4-dim vector
   */
  void setUniform(const GLchar* uniformName, const glm::vec4& vector);

private:
  /**
   * OpenGL program object identificator
   */
  GLuint mObject;

  /**
   * Disable copying
   */
  Program(const Program&);
};
