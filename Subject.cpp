#include "header/Subject.h"
#include "header/Observer.h"

void Subject::Attach(Observer* observer) {
  views_.push_back(observer);
}

void Subject::Detach(Observer* observer) {
  std::erase(views_, observer);
}

void Subject::Notify(SubjectEvent event, const EventData& data) {
  for (const auto kView : views_) {
    kView->Update(event, data);
  }
}