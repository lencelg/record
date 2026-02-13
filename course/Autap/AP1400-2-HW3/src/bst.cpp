#include "bst.h"
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <vector>
BST::BST(std::initializer_list<int> list) : root(nullptr) {
  for (auto v : list) {
    add_node(v);
  }
}
BST::BST(BST &other) {
  std::vector<Node *> container;
  other.bfs([&container](Node *&node) { container.push_back(node); });
  for (auto &n : container)
    this->add_node(n->value);
}
BST::BST(BST &&other) {
  this->root = other.root;
  other.root = nullptr;
}
BST::~BST() {
  std::vector<Node *> nodes;
  bfs([&nodes](BST::Node *&node) { nodes.push_back(node); });
  for (auto &node : nodes)
    delete node;
}
BST &BST::operator=(BST &other) {
  std::vector<Node *> container;
  other.bfs([&container](Node *&node) { container.push_back(node); });
  for (auto &n : container)
    this->add_node(n->value);
  return *this;
}
BST &BST::operator=(BST &&other) {
  this->root = other.root;
  other.root = nullptr;
  return *this;
}
std::ostream &operator<<(std::ostream &stream, BST::Node const &node) {
  stream << "current node address :" << &node
         << "current node value : " << node.value;
  if (node.left)
    stream << "   left node address :" << node.left;
  else
    stream << "    left node is nullptr" << std::endl;
  if (node.right)
    stream << "     right node address :" << node.right;
  else
    stream << "    right node is nullptr";
  return stream;
}
std::ostream &operator<<(std::ostream &stream, BST &bst) {
  stream << std::string(20, '*') << std::endl;
  bst.bfs([&stream](BST::Node *&node) {
    stream << "node address : " << node << " value " << node->value
           << std::endl;
    if (node->left) {
      stream << "node left child address : " << node->left << std::endl;
    }
    if (node->right) {
      stream << "node right child address : " << node->right << std::endl;
    }
  });
  stream << "binary search tree size :" << bst.length() << std::endl;
  stream << std::string(20, '*') << std::endl;
  return stream;
}

bool operator>(int number, const BST::Node &node) {
  return number > node.value;
}
bool operator>=(int number, const BST::Node &node) {
  return number >= node.value;
}
bool operator<(int number, const BST::Node &node) {
  return number < node.value;
}
bool operator<=(int number, const BST::Node &node) {
  return number <= node.value;
}
bool operator==(int number, const BST::Node &node) {
  return number == node.value;
}

BST::Node *&BST::get_root() { return root; }

void BST::bfs(std::function<void(Node *&node)> func) {
  if(root == nullptr) return;
  std::queue<Node *> q;
  q.push(get_root());
  while (!q.empty()) {
    auto cur = q.front();
    q.pop();
    func(cur);
    if (cur->left)
      q.push(cur->left);
    if (cur->right)
      q.push(cur->right);
  }
}

size_t BST::length() {
  int cnt = 0;
  std::function<void(Node * &node)> f = [&cnt](Node *&node) { ++cnt; };
  bfs(f);
  return cnt;
}

bool BST::add_node(int value) {
  if(!get_root()) {
    root = new Node(value, nullptr, nullptr);
    return true;
  }
  Node **temp = &get_root();
  while ((*temp)) {
    if ((*temp)->value == value)
      return false;
    else if ((*temp)->value > value)
      temp = &((*temp)->left);
    else
      temp = &((*temp)->right);
  }
  (*temp) = new Node(value, nullptr, nullptr);
  return true;
}

BST::Node **BST::find_node(int value) {
  auto temp = &get_root();
  while ((*temp)) {
    if ((*temp)->value == value)
      return temp;
    else if ((*temp)->value > value)
      temp = &((*temp)->left);
    else
      temp = &((*temp)->right);
  }
  return nullptr;
}

BST::Node **BST::find_parent(int value) {
  auto temp = &get_root();
  while ((*temp)) {
    if (((*temp)->left && (*temp)->left->value == value) || ((*temp)->right && (*temp)->right->value == value))
      return temp;
    else if ((*temp)->value > value)
      temp = &((*temp)->left);
    else
      temp = &((*temp)->right);
  }
  return nullptr;
}

BST::Node **BST::find_successor(int value) {
  // It's the node with the smallest value that is still greater than the target
  // value
  auto cur = find_node(value);
  if (!cur)
    return nullptr;
  else if ((*cur)->left == nullptr)
    return find_parent(value);
  else {
    cur = &((*cur)->left);
    while ((*cur)->right)
      cur = &((*cur)->right);
    return cur;
  }
}

bool BST::delete_node(int value) {
  Node **node = find_node(value);
  Node **parent = find_parent(value);
  if (!node) {
    return false;
  }

  Node *delete_node = *node;

  if (!delete_node->left && !delete_node->right) {
    if (parent) {
      if ((*parent)->left && (*parent)->left->value == value) {
        (*parent)->left = nullptr;
      } else {
        (*parent)->right = nullptr;
      }
    } else {
      root = nullptr;
    }
    delete delete_node;
  } else if (!delete_node->left || !delete_node->right) {
    Node *child = delete_node->left ? delete_node->left : delete_node->right;
    if (parent) {
      if ((*parent)->left && (*parent)->left->value == value) {
        (*parent)->left = child;
      } else {
        (*parent)->right = child;
      }
    } else {
      root = child;
    }
    delete delete_node;
  } else {
    Node **successor = find_successor(value);
    Node **successor_parent = find_parent((*successor)->value);
    std::swap((*successor)->value, delete_node->value);
    if ((*successor_parent)->left &&
        (*successor_parent)->left->value == value) {
      (*successor_parent)->left = nullptr;
    } else {
      (*successor_parent)->right = nullptr;
    }
    delete *successor;
  }
  return true;
}

BST &BST::operator++() {
  bfs([](Node *&node) { node->value += 1; });
  return *this;
}
BST BST::operator++(int) {
  BST copy = *this;
  bfs([](Node *&node) { node->value += 1; });
  return copy;
}
