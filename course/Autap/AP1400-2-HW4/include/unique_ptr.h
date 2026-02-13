#ifndef UNIQUE_PTR
#define UNIQUE_PTR
#include "gmock/gmock.h"
#include <stdexcept>
template <typename T> class UniquePtr {
private:
  T *_p;

public:
  UniquePtr() : _p(nullptr) {}
  UniquePtr(T *t) : _p(t) {}
  UniquePtr(UniquePtr &t) = delete;
  ~UniquePtr() { delete _p; }
  T *get() { return _p; }
  void reset(T *object = nullptr) {
    delete _p;
    _p = object;
  }
  T *release() {
    T *temp = _p;
    _p = nullptr;
    return temp;
  }
  bool operator!() { return _p == nullptr; }
  void operator=(const UniquePtr &other) = delete;
  T &operator*() { return *_p; }
  T *operator->() { return _p; }
  explicit operator bool() { return _p != nullptr; }
};
template <class T> inline T *make_unique(T t) { return new T(t); }
#endif // UNIQUE_PTR
