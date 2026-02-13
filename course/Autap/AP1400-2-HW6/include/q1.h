// referencet form
// https://stackoverflow.com/questions/77591644/how-to-write-a-general-version-gradient-descent-algorithm-in-c
#ifndef Q1_H
#define Q1_H
#include <functional>
namespace q1 {
template <typename T, typename F>
T gradient_descent(const T &init_value, const T &step_size, F t = {}) {
  T val = init_value;
  auto accuracy = step_size * 1e-3;
  auto gradient = [&accuracy, &t](T &value) {
    return (t(value) - t(value - accuracy)) / accuracy;
  };
  while (abs(gradient(val)) > accuracy)
    val -= step_size * gradient(val);
  return val;
}
template <typename T>
T gradent_descent(const T &init_value, const T &step_size, T f(T)) {
  return gradient_descent<T, T(T)>(init_value, step_size, f);
}
} // namespace q1
#endif // Q1_H
