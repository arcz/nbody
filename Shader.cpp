#include "Shader.h"
#include <stdexcept>
#include <fstream>
#include <string>
#include <cassert>
#include <sstream>

Shader::Shader(const std::string& shaderCode, GLenum shaderType) {
  mObject = glCreateShader(shaderType);
  if(mObject == 0)
    throw std::runtime_error("glCreateShader failed");

  const char* code = shaderCode.c_str();
  glShaderSource(mObject, 1, (const GLchar**)&code, NULL);

  glCompileShader(mObject);

  GLint status;
  glGetShaderiv(mObject, GL_COMPILE_STATUS, &status);

  if (status == GL_FALSE) {
    std::string msg("Compile failure in shader:\n");

    GLint infoLogLength;
    glGetShaderiv(mObject, GL_INFO_LOG_LENGTH, &infoLogLength);
    char* strInfoLog = new char[infoLogLength + 1];
    glGetShaderInfoLog(mObject, infoLogLength, NULL, strInfoLog);
    msg += strInfoLog;
    delete[] strInfoLog;

    glDeleteShader(mObject); mObject = 0;
    throw std::runtime_error(msg);
  }

  mRefCount = new unsigned;
  *mRefCount = 1;
}

Shader Shader::createFromFile(const std::string& filePath, GLenum shaderType) {
  std::ifstream f;
  f.open(filePath.c_str(), std::ios::in | std::ios::binary);
  if (!f.is_open()) {
    throw std::runtime_error(std::string("Failed to open file: ") + filePath);
  }

  std::stringstream buffer;
  buffer << f.rdbuf();

  Shader shader(buffer.str(), shaderType);
  return shader;
}

GLuint Shader::object() const {
  return mObject;
} 

Shader::Shader(const Shader& other) : mObject(other.mObject), mRefCount(other.mRefCount) {
  retain();
}

Shader::~Shader() {
  if (mRefCount) release();
}

Shader& Shader::operator= (const Shader& other) {
  release();
  mObject = other.mObject;
  mRefCount = other.mRefCount;
  retain();
  return *this;
}

void Shader::retain() {
  assert(mRefCount);
  *mRefCount += 1;
}

void Shader::release() {
  assert(mRefCount && *mRefCount > 0);
  *mRefCount -= 1;

  if (*mRefCount == 0) {
    glDeleteShader(mObject); mObject = 0;
    delete mRefCount; mRefCount = NULL;
  }
}  

