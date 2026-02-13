#ifndef Q2_H
#define Q2_H
#include <algorithm>
#include <cstddef>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
namespace q2 {
struct Patient {
  std::string name;
  size_t age;
  size_t smokes;
  size_t area_q;
  size_t alkhol;
};
inline std::vector<Patient> read_file(std::string filename) {
  std::vector<Patient> res;
  std::ifstream file;
  file.open(filename);
  if (!file)
    return {};
  std::string line;
  std::getline(file, line);
  std::getline(file, line);
  while (std::getline(file, line)) {
    Patient p;
    std::string token;
    std::istringstream iss(line);
    std::getline(iss, token, ',');
    p.name = token;
    if(p.name[p.name.length() - 1] != ' ')  p.name += " ";
    std::getline(iss, token, ',');
    p.name += token;
    std::getline(iss, token, ',');
    p.age = std::stoul(token);
    std::getline(iss, token, ',');
    p.smokes = std::stoul(token);
    std::getline(iss, token, ',');
    p.area_q = std::stoul(token);
    std::getline(iss, token, ',');
    p.alkhol = std::stoul(token);
    res.push_back(p);
  }
  file.close();
  return res;
}
inline void sort(std::vector<Patient> &v) {
    return std::sort(v.begin(), v.end(), [](Patient& a, Patient & b) {
            auto f = [](Patient & p) {return 3 * p.age + 5 * p.smokes + 2 * p.area_q + 4 * p.alkhol;};
            return f(a) > f(b);
            });
}
} // namespace q2

#endif // Q2_H
