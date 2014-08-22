#pragma once
#include "Headers.h"
#include <string>
#include <stdexcept>

class Shader {
public:
  static Shader createFromFile(const std::string& filePath, GLenum shaderType);
  Shader(const std::string& shaderCode, GLenum shaderType);

  Shader(const Shader& other);
  Shader& operator= (const Shader& other);
  GLuint object() const;
  ~Shader();

private:
  GLuint mObject;
  unsigned* mRefCount;

  void retain();
  void release();
};
