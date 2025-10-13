#include "header/Model.h"

Model::Model(std::vector<float>& points, int count) : points_(points), count_(count), vao_(0), vbo_(0) {
  glGenBuffers(1, &vbo_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, points_.size() * sizeof(float), points_.data(), GL_STATIC_DRAW);

  glGenVertexArrays(1, &vao_);
  glBindVertexArray(vao_);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
}

Model::~Model() {
  glDeleteVertexArrays(1, &vao_);
}

void Model::Draw() {
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, count_);
}
