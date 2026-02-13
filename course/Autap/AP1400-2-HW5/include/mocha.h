#ifndef MOCHA_H
#define MOCHA_H
#include "espresso_based.h"
class Mocha : public EspressoBased {
public:
  Mocha() : EspressoBased() {
    EspressoBased::ingredients.push_back(new Espresso(2));
    EspressoBased::ingredients.push_back(new Milk(2));
    EspressoBased::ingredients.push_back(new MilkFoam(1));
    EspressoBased::ingredients.push_back(new Chocolate(1));
  }
  Mocha(const Mocha &cap) : side_items(cap.side_items) {}
  ~Mocha() { side_items.clear(); }
  void operator=(const Mocha &cap) { this->side_items = cap.side_items; }

  virtual std::string get_name() override { return "Mocha"; }
  virtual double price() override {
    double cnt = 0;
    for (const auto i : EspressoBased::ingredients)
      cnt += i->price();
    for (const auto s : side_items)
      cnt += s->price();
    return cnt;
  }

  void add_side_item(Ingredient *side) { side_items.push_back(side); }
  std::vector<Ingredient *> &get_side_items() { return side_items; }

private:
  std::vector<Ingredient *> side_items;
};

#endif // MOCHA_H
