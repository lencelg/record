#ifndef Q3_H
#define Q3_H
#include <cstddef>
#include <fstream>
#include <queue>
#include <sstream>
#include <string>
namespace q3 {
struct Flight {
  std::string flight_number;
  size_t duration;
  size_t connections;
  size_t connection_times;
  size_t price;
};
struct comapre {
  bool operator()(const Flight &a, const Flight &b) {
    auto f = [](const Flight &flight) {
      return flight.duration + flight.connection_times + 3 * flight.price;
    };
    return f(a) >= f(b);
  }
};
inline std::priority_queue<Flight, std::vector<Flight>, comapre>
gather_flights(std::string filename) {
  std::priority_queue<Flight, std::vector<Flight>, comapre> res;
  std::string line;
  std::ifstream file;
  file.open(filename);
  if (!file) return {};
  while (std::getline(file, line)) {
    Flight a;
    std::istringstream iss(line);
    std::string token;

    std::getline(iss, token, ':');
    std::getline(iss, token, ' ');
    a.flight_number = token;

    std::getline(iss, token, ':');
    std::getline(iss, token, ' ');
    auto con_process = [](std::string token) {
      auto pos = token.find('h');
      size_t hour = std::stoul(token.substr(0, pos));
      size_t min = 0;
      auto min_pos = token.find('m');
      if (min_pos != std::string::npos)
        min = std::stoul(token.substr(pos + 1, min_pos));
      return hour * 60 + min;
    };
    a.duration = con_process(token);

    std::getline(iss, token, ':');
    std::getline(iss, token, ' ');
    a.connections = std::stoul(token);

    std::getline(iss, token, ':');
    std::getline(iss, token, ' ');
    size_t cnt = 0;
    std::istringstream con_iss(token);
    while (std::getline(con_iss, token, ','))
      cnt += con_process(token);
    a.connection_times = cnt;

    std::getline(iss, token, ':');
    std::getline(iss, token);
    a.price = std::stoul(token);
    res.push(a);
  }
  return res;
}
} // namespace q3

#endif // Q3_H
