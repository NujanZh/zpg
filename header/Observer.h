#ifndef OBSERVER_H
#define OBSERVER_H

class Subject;
class Observer {
public:
  virtual ~Observer() = default;
  virtual void Update(Subject* theChangedSubject) = 0;
};


#endif