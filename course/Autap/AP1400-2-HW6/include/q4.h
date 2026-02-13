#ifndef Q4_H
#define Q4_H
#include <algorithm>
#include <vector>
namespace q4 {
struct Vector2D {
  double x{};
  double y{};
};

struct Sensor {
  Vector2D pos;
  double accuracy;
};
inline Vector2D kalman_filter(std::vector<Sensor> sensors) {
    double x = 0 ,y = 0, accuracy = 0;
    auto f = [&x, &y, &accuracy](const auto& sensor) {
        x += sensor.pos.x * sensor.accuracy;
        y += sensor.pos.y * sensor.accuracy;
        accuracy += sensor.accuracy;
    };
    std::for_each(sensors.begin(), sensors.end(), f);
    x /= accuracy, y /= accuracy;
    return Vector2D{x , y};
}
}; // namespace q4
#endif // Q4_H
