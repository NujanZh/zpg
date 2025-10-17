#ifndef ZPG_SHADERLOADER_H
#define ZPG_SHADERLOADER_H


#include <fstream>
#include <sstream>
#include <string>

#include "Shader.h"

class ShaderLoader {
public:
  static std::string LoadShader(const std::string& kPath) {
    std::ifstream file(kPath);

    if (!file.is_open()) {
      fprintf(stderr, "Failed to open file %s\n", kPath.c_str());
      exit(EXIT_FAILURE);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
  }

  static Shader CreateShaderFromFile(GLenum type, const std::string& kPath) {
    std::string shaderSource = LoadShader(kPath);

    if (shaderSource.empty()) {
      fprintf(stderr, "Shader source is empty in a file: %s\n", kPath.c_str());
      exit(EXIT_FAILURE);
    }

    return Shader(type, shaderSource.c_str());
  }
};

#endif
