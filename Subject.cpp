#include "header/Subject.h"
#include "header/Observer.h"

void Subject::Attach(Observer* observer) {
  views_.push_back(observer);
}

void Subject::Detach(Observer* observer) {
  std::erase(views_, observer);
}

void Subject::Notify() {
  for (const auto kView : views_) {
    kView->Update(this); // Now safe, as Observer is fully defined
  }
}