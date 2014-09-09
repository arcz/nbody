#pragma once
#include "Headers.h"
#include <string>
#include <stdexcept>

/**
 * Class representing compiled OpenGL shader
 */
class Shader {
public:
  /**
   * Helper method for creating from file
   * @param filePath path to file
   * @param shaderType OpenGL shader type
   * @return compiled shader
   */
  static Shader createFromFile(const std::string& filePath, GLenum shaderType);
  /**
   * Constructor, but you may want to use createFromFile
   * @param shaderCode code of shader
   * @param shaderType OpenGL shader type
   */
  Shader(const std::string& shaderCode, GLenum shaderType);

  /**
   * Copy constructor, shaders can be copied and are reference counted
   * @param other shader to be copied
   */
  Shader(const Shader& other);
  /**
   * Assignment operator
   * @param other shader to be assigned
   */
  Shader& operator= (const Shader& other);
  /**
   * Getter for OpenGL identificator of shader
   * @return OpenGL identificator
   */
  GLuint object() const;
  ~Shader();

private:
  /**
   * OpenGL identificator of shader
   */
  GLuint mObject;
  /**
   * Number of references to this instance
   */
  unsigned* mRefCount;

  /**
   * Acquire resource, increments mRefCount
   */
  void retain();
  /**
   * Release resource, decreases mRefCount
   * when reference counter goes to zero, frees OpenGL shader
   */
  void release();
};
