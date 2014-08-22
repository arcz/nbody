#include "Program.h"
#include <stdexcept>
#include <glm/gtc/type_ptr.hpp>

Program::Program() : mObject(0) {}
Program::Program(const std::vector<Shader>& shaders) : mObject(0) {
  setShaders(shaders);
}

void Program::setShaders(const std::vector<Shader>& shaders) {
  // typically would be 2 shaders, one vertex and one fragment (pixel)
  if (shaders.size() <= 0)
    throw std::runtime_error("At least one shader is required to create program");

  mObject = glCreateProgram();
  if (mObject == 0)
    throw std::runtime_error("glCreateProgram failed");

  for (auto shader : shaders)
    glAttachShader(mObject, shader.object());

  glLinkProgram(mObject);

  // after linking we don't need attached shaders
  for (auto shader : shaders)
    glDetachShader(mObject, shader.object());

  // react if linking failed
  GLint status;
  glGetProgramiv(mObject, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) {
    std::string msg("Program linking failure");
    GLint infoLogLength;
    glGetProgramiv(mObject, GL_INFO_LOG_LENGTH, &infoLogLength);
    char* strInfoLog = new char[infoLogLength + 1];
    glGetProgramInfoLog(mObject, infoLogLength, NULL, strInfoLog);
    msg += strInfoLog;
    delete[] strInfoLog;

    glDeleteProgram(mObject); mObject = 0;
    throw std::runtime_error(msg);
  }
}

Program::~Program() {
  if (mObject != 0) glDeleteProgram(mObject);
}

GLuint Program::object() const {
  return mObject;
}

void Program::use() const {
  glUseProgram(mObject);
}

bool Program::isInUse() const {
  GLint currentProgram = 0;
  glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
  return (currentProgram == (GLint)mObject);
}

void Program::stopUsing() const {
  assert(isInUse());
  glUseProgram(0);
}

GLint Program::attrib(const GLchar* attribName) const {
  if (!attribName)
    throw std::runtime_error("attribName is NULL");

    GLint attrib = glGetAttribLocation(mObject, attribName);
  if (attrib == -1)
    throw std::runtime_error(std::string("Program attribute not found: '") + attribName +
                              std::string("'. Check attribute name in shader code"));
  return attrib;
}

GLint Program::uniform(const GLchar* uniformName) const {
  if (!uniformName)
    throw std::runtime_error("uniformName is NULL");

  GLint uniform = glGetUniformLocation(mObject, uniformName);
  if (uniform == -1)
    throw std::runtime_error(std::string("Program uniform not found: '") + uniformName +
                              std::string("'. Check uniform name in shader code"));
  return uniform;
}

void Program::setUniform(const GLchar* uniformName, const glm::mat3& matrix) {
  assert(isInUse());
  glUniformMatrix3fv(uniform(uniformName), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Program::setUniform(const GLchar* uniformName, const glm::mat4& matrix) {
  assert(isInUse());
  glUniformMatrix4fv(uniform(uniformName), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Program::setUniform(const GLchar* uniformName, const glm::vec3& vec) {
  glUniform3f(uniform(uniformName), vec.x, vec.y, vec.z);
}

void Program::setUniform(const GLchar* uniformName, const glm::vec4& vec) {
  glUniform4f(uniform(uniformName), vec.x, vec.y, vec.z, vec.w);
}

