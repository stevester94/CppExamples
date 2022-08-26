/*
<Synopsis, anythin interesting>
*/
#include <helpers.hpp>
#include <trees.hpp>
#include <iostream>
#include <queue>
#include <stack>

using std::cout;
using std::endl;

using tree::Node;

const std::string tree_visualization(
    "              A\n"
    "        B           E\n"
    "    C      D     F\n"
    "         Z\n"
);

template<class T>
void dfs_print_recursive(Node<T>& n, int depth=0)
{
    if(n.has_left())
    {
        dfs_print_recursive(n.get_left(), depth+1);
    }
    if(n.has_right())
    {
        dfs_print_recursive(n.get_right(), depth+1);
    }
    std::cout << n.value << std::endl;
}


#if 0
template<class T>
void dfs_print_stack(Node<T> root)
{
    std::stack<Node<T>*> s;

    Node<T>* n = &root;
    while(true)
    {
        // Keep pushing all the lefts until we have none
        while(n != nullptr)
        {
            s.push(n);
            n = n->left;
        }
        if(s.size() == 0)
            break;
        
        n = s.top();
        s.pop();

        // Process the current value
        std::cout << n->value << std::endl;

        // The right node will be placed on the stack if it actually exists
        n = n->right;
    }
}
#elif 1
template<class T>
void dfs_print_stack(Node<T> root)
{
    std::stack<Node<T>*> s;

    Node<T>* n;    
    s.push(&root);

    while(not s.empty())
    {
        n = s.top();
        s.pop();
        std::cout << n->value << std::endl;

        if(n->right)
            s.push(n->right);
        if(n->left)
            s.push(n->left);

    }
}
#endif

int main()
{
    Node<std::string> A(std::string("A"));
    Node<std::string> B(std::string("B"));
    Node<std::string> C(std::string("C"));
    Node<std::string> D(std::string("D"));
    Node<std::string> E(std::string("E"));
    Node<std::string> F(std::string("F"));
    Node<std::string> Z(std::string("Z"));
    // Node<std::string> G(std::string("G"));

    A.set_left(B); A.set_right(E);
    B.set_left(C); B.set_right(D);
    E.set_left(F); // E.set_right(G);
    D.set_left(Z);


    ANNOUNCE_SECTION("The Tree");
    cout << tree_visualization << endl;

    ANNOUNCE_SECTION("DFS Print Recursively");
    dfs_print_recursive(A);

    ANNOUNCE_SECTION("DFS Print Stack");
    dfs_print_stack(A);
}