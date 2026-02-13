#ifndef SHARED_PTR
#define SHARED_PTR
template <typename T> class SharedPtr {
private:
  T *_p;
  int* cnt;

public:
  SharedPtr() : _p(nullptr) , cnt(new int(0)) {}
  SharedPtr(T *other) : _p(other), cnt(new int(1)) {}
  SharedPtr(SharedPtr &other) : _p(other._p), cnt(other.cnt){
    (*cnt)++;
  }
  ~SharedPtr() {
    if(cnt) {
      (*cnt)--;
      if((*cnt) == 0) {
        delete cnt;
        delete _p;
      }
      cnt = nullptr;
      _p = nullptr;
    } 
  }
  int use_count() { return cnt ? (*cnt): 0; }
  void operator=(SharedPtr &other) {
    if(this != &other) {
      delete _p;
      _p = other.get();
      cnt = other.cnt;
      (*cnt)++;
    }
  }
  T *operator->() { return _p; }
  T &operator*() { return *_p; }
  T *get() { return _p; }
  void reset(T *object = nullptr) {
    (*cnt)--;
    delete _p;
    _p = object;
    cnt = object ? new int(1) : new int(0);
  }
  explicit operator bool() { return _p != nullptr; }
};
template <typename T> inline T *make_shared(T object) { return new T(object); }
#endif // SHARED_PTR
