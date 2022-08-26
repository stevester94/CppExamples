#ifndef __TREES_HPP__
#define __TREES_HPP__
#include <list>

namespace tree {


// So it definitely makes sense to make a node a template, since
// the content of a node could be anything
template<class T>
class Node {

public:
    Node(T value) : left(nullptr), right(nullptr), value(value) {}
    Node() : left(nullptr), right(nullptr) {}

    Node(const Node<T>& old)
    {
        // std::cout << "Copy constructor called" << std::endl;
        value = old.value;
        left = old.left;
        right = old.right;
    }


    bool has_left() const  { return left != nullptr; }
    bool has_right() const { return right != nullptr; }

    Node& get_left() {
        if(has_left())
            return *left; 
        else
            throw std::runtime_error("Does not have a left child");
    }

    Node& get_right() {
        if(has_right())
            return *right; 
        else
            throw std::runtime_error("Does not have a right child");
    }

    void set_left(Node& n) { left = &n; }
    void set_right(Node& n) { right = &n; }

    void remove_left() { left = nullptr; }
    void remove_right() { right = nullptr; }

    T value;
    Node* left;
    Node* right;
};

}; //NS: tree

// namespace tree_v2
// {

// template<class T>
// class Node
// {
// public:




// };
// };

#endif