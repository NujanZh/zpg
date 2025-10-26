#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <glm/fwd.hpp>

#include "Camera.h"
#include "Shader.h"
#include "Subject.h"
#include "Observer.h"

class ShaderProgram : public Observer {
private:
  GLuint id_;
  Camera* camera_;

  std::vector<glm::vec3> lightPositions_;
  std::vector<glm::vec3> lightColors_;
  std::vector<glm::vec3> lightDiffuses_;

public:

  ~ShaderProgram() override;
  ShaderProgram(Shader& vertexShader, Shader& fragmentShader, Camera* camera);
  bool SetShaderProgram();
  void SetUniform(const char* name, const glm::mat4& matrix);
  void SetUniform(const char* name, const glm::vec3& vector);
  void SetUniform(const char* name, float value);
  void SetUniform(const char* name, int value);

  void Update(SubjectEvent event, const EventData& data) override;

  void UpdateAllLights();
  int GetLightCount();
  void SetLightPosition(int index, const glm::vec3& position);
  void SetLightColor(int index, const glm::vec3& color);
  void SetLightDiffuse(int index, const glm::vec3& diffuse);
  void AddLightSlot();
};

#endif
