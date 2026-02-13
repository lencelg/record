#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H
#define DEFCLASS(class_name, price_units)                                      \
  class class_name : public Ingredient {                                       \
  public:                                                                      \
    class_name(size_t units) : Ingredient{price_units, units} {                \
      this->name = #class_name;                                                \
    }                                                                          \
    std::string get_name() override { return this->name; }                     \
  };

#endif // SUB_INGREDIENTS_H
