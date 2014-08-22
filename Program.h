#pragma once
#define GLM_FORCE_RADIANS

#include <vector>
#include <glm/glm.hpp>
#include "Headers.h"
#include "Shader.h"

class Program {
public:
  Program(const std::vector<Shader>& shaders);
  ~Program();
    
  GLuint object() const;
  void use() const;
  bool isInUse() const;
  void stopUsing() const;

  /**
    @attributeName Name of attribute declared in shader
    @return Attribute index for provided name
  */
  GLint attrib(const GLchar* attributeName) const;

  /**
    @uniformName Name of uniform declared in shader
    @return Uniform index for provided name
  */
  GLint uniform(const GLchar* uniformName) const;
  void setUniform(const GLchar* uniformName, const glm::mat3& matrix);
  void setUniform(const GLchar* uniformName, const glm::mat4& matrix);
  void setUniform(const GLchar* uniformName, const glm::vec3& vector);
  void setUniform(const GLchar* uniformName, const glm::vec4& vector);

private:
  GLuint mObject;
  Program(const Program&);
};
