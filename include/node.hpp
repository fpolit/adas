/*
 * Node Template class
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */


#ifndef _NODE_H
#define _NODE_H

#include <list>
using namespace std;

#include "helper.hpp"
#include "exceptions/node.hpp"

template<typename T>
class Node
{
protected:
  T data;
  unsigned int depth;
  Node<T>* parent;
  list<Node<T>*> children;

public:
  Node(T data): data{data}, parent{nullptr}, depth{0} {}
  Node(T data, Node<T>* parent): data{data}, parent{parent}
  {
    parent->add_child(this);
  }

  Node(T data, Node<T>* parent, list<Node<T>*> children)
    : data{data}, parent{parent}, children{children}
  {
    parent->add_child(this);
  }

  T get_data(){return data;}
  Node<T>* get_parent(){return parent;}
  void set_depth(unsigned int tree_depth)
  {
    depth = tree_depth;
    for(Node<T>* child: children)
      if(child != nullptr)
        child->set_depth(depth +1);
  }

  list<Node<T>*> get_children(){return children;}
  unsigned int get_depth(){return depth;}

  void add_child(Node<T>* child)
  {
    child->set_depth(depth+1);
    child->set_parent(this);
    children.push_back(child);
  }

  void set_parent(Node<T>* parent)
  {
    try
      {
        if(parent == nullptr)
          throw NullParentNode();

        this->parent = parent;
      }
    catch(exception& error)
      {
        cout << error.what() << endl;
        exit(EXIT_FAILURE);
      }
    //parent->add_child(this); // NOTE
  }

  bool equal_children(Node<T> node)
  {
    // implemnt a more efficient algorithm to compare 2 sets
    // using this theorem:
    // A = B  <-> A c B and |A| = |B|

    list<Node<T>*> node_children = node.get_children();
    if(this->children.size() != node_children.size())
      return false;

    for(Node<T>* child: node_children)
      if(!this->has_child(child))
        return false;

    return true;
  }

  bool operator==(Node<T> node)
  {
    //bool are_equal = true;

    Node<T>* parent_node = node.get_parent();
    unsigned int node_depth = node.get_depth();
    T node_data = node.get_data();

    if(depth != node_depth || data != node_data)
      return false;

    if(!this->equal_children(node))
      return false;

    if((parent == nullptr && parent_node != nullptr) ||
       (parent != nullptr && parent_node == nullptr) ||
       !(parent != nullptr && parent_node != nullptr && *parent == *parent_node))
      return false;

    return true;
  }

  bool has_child(BinaryNode<T>* node)
  {
    if(*this == *node)
      return true;

    // implemet a more efficient search (BINARY SEARCH)
    for(BinaryNode<T>* child: children)
      {
        if(child != nullptr && child.has_child(node))
          return true;
      }
    return false;
  }

  friend ostream& operator<<(ostream& out, Node<T>* node)
  {
    unsigned int depth = node->get_depth();
    T data = node->get_data();
    string tab = repeat("\t", depth);

    out << tab << data << endl;
    //tab += "\t";
    for(Node<T>* child: node->get_children())
      {
        if(child != nullptr)
          out << child;
      }
    return out;
  }
};

#endif //_NODE_H