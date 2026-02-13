#ifndef ESPRESSO_BASED_H
#define ESPRESSO_BASED_H
#include "ingredient.h"
#include <memory>
#include <string>
#include <vector>
class EspressoBased {
public:
  virtual std::string get_name() = 0;
  virtual double price() = 0;

  void brew() {}
  std::vector<Ingredient *> &get_ingredients() { return ingredients; }

  virtual ~EspressoBased() { ingredients.clear(); }

protected:
  EspressoBased() {}
  EspressoBased(const EspressoBased &esp)
      : name(esp.name), ingredients(esp.ingredients) {}
  void operator=(const EspressoBased &esp) {
    this->name = esp.name;
    this->ingredients = esp.ingredients;
  }

  std::vector<Ingredient *> ingredients;
  std::string name;
};

#endif // ESPRESSO_BASED_H
