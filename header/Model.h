#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <vector>

class Model {
private:
  GLuint vao_;
  GLuint vbo_;
  std::vector<float> points_;
  int count_;

public:
  Model(std::vector<float>& points, int count);
  ~Model();
  void Draw();
};

#endif

