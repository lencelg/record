#ifndef INGREDIENT_H
#define INGREDIENT_H
#include "sub_ingredients.h"
#include <string>
class Ingredient {
public:
  double get_price_unit() { return price_unit; }
  size_t get_units() { return units; }
  virtual std::string get_name() = 0;

  double price() { return get_price_unit() * get_units(); }

protected:
  Ingredient(double price_unit, size_t units)
      : price_unit(price_unit), units(units) {}
  double price_unit;
  size_t units;
  std::string name;
};
DEFCLASS(Cinnamon, 5);
DEFCLASS(Chocolate, 5);
DEFCLASS(Sugar, 1);
DEFCLASS(Cookie, 10);
DEFCLASS(Espresso, 15);
DEFCLASS(Milk, 10);
DEFCLASS(MilkFoam, 5);
DEFCLASS(Water, 1);

#endif // INGREDIENT_H
