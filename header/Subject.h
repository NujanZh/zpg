#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>


class Observer;
class Subject {

std::vector<Observer*> views_;

public:
  virtual ~Subject() = default; // Added this to make Subject class polymorphic
  void Attach(Observer* observer);

  // TODO: Create a method so views can delete observer if they detach
  void Detach(Observer* observer);

  void Notify();
};


#endif