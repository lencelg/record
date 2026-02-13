#ifndef CAPPUCCINO
#define CAPPUCCINO
#include "espresso_based.h"
#include "ingredient.h"
#include "sub_ingredients.h"
class Cappuccino : public EspressoBased {
public:
  Cappuccino() : EspressoBased() {
    EspressoBased::ingredients.push_back(new Espresso(2));
    EspressoBased::ingredients.push_back(new Milk(2));
    EspressoBased::ingredients.push_back(new MilkFoam(1));
  }
  Cappuccino(const Cappuccino &cap)
      : side_items(cap.side_items), EspressoBased(cap) {}
  ~Cappuccino() { side_items.clear(); }
  void operator=(const Cappuccino &cap) {
    this->side_items = cap.side_items;
    ingredients = cap.ingredients;
  }

  virtual std::string get_name() { return "Cappuccino"; }
  virtual double price() {
    double cnt = 0;
    for (const auto i : ingredients)
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

#endif // CAPPUCCINO
