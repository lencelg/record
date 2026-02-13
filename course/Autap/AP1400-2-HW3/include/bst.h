#ifndef BST_H
#define BST_H
#include <functional>
#include <initializer_list>
#include <iostream>
#include <ostream>
#include <queue>
#include <utility>
class BST {
public:
  class Node {
  public:
    Node(int value, Node *left, Node *right)
        : value(value), left(left), right(right) {}
    Node() : value(0), left(nullptr), right(nullptr) {}
    Node(const Node &node)
        : value(node.value), left(node.left), right(node.right) {}

    bool operator>(int number) { return value > number; }
    bool operator>=(int number) { return value >= number; }
    bool operator<(int number) { return value < number; }
    bool operator<=(int number) { return value <= number; }
    bool operator==(int number) { return value == number; }

    friend std::ostream &operator<<(std::ostream &stream,
                                    const BST::Node &node);

    friend bool operator>(int number, const BST::Node &node);
    friend bool operator>=(int number, const BST::Node &node);
    friend bool operator<(int number, const BST::Node &node);
    friend bool operator<=(int number, const BST::Node &node);
    friend bool operator==(int number, const BST::Node &node);

    int value = 0;
    Node *left = nullptr;
    Node *right = nullptr;
  };
  BST(std::initializer_list<int> list);
  BST(BST &other);
  BST(BST &&other);

  ~BST();

  Node *&get_root();
  void bfs(std::function<void(Node *&node)> func);
  size_t length();
  bool add_node(int value);
  Node **find_node(int value);
  Node **find_parent(int value);
  Node **find_successor(int value);
  bool delete_node(int value);

  BST &operator++();
  BST operator++(int);

  BST &operator=(BST &other);
  BST &operator=(BST &&other);

  friend std::ostream &operator<<(std::ostream &stream, BST &bst);

private:
  Node *root = nullptr;
};

#endif // BST_H
