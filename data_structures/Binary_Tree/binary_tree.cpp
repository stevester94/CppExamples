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
    cout << "(" << depth << "," << n.value << ")" << endl;
    if(n.has_left())
        dfs_print_recursive(n.get_left(), depth+1);
    if(n.has_right())
        dfs_print_recursive(n.get_right(), depth+1);
}

/*
We keep track of depth with just two counters, this is possible since we process one depth at a time, so we
can reason that all of the nodes that the current depth is adding belongs only to the next depth.
Therefore, we keep track of n_nodes_current_depth, n_nodes_next_depth. n_node_current_depth is never added to,
    it just takes the value of n_nodes_next_depth once we've exhausted the current depth.
*/
template<class T>
void bfs_print(Node<T>& root)
{
    std::queue<Node<T>> q;

    q.push(root);
    int depth = 0;
    int n_nodes_current_depth = 1;
    int n_nodes_next_depth = 0;

    while(not q.empty())
    {
        Node<T>& n = q.front();
        q.pop();

        cout << "(" << depth << "," << n.value << ")" << endl;

        if(n.has_left())
        {
            q.push(n.get_left());
            n_nodes_next_depth++;
        }
        if(n.has_right())
        {
            q.push(n.get_right());
            n_nodes_next_depth++;
        }
        
        n_nodes_current_depth--;    
        if(n_nodes_current_depth == 0)
        {
            depth++;
            n_nodes_current_depth = n_nodes_next_depth;
            n_nodes_next_depth = 0;
        }
    }
}


/*
Have to keep track of depth as a stack, I don't think there is any way around this.
*/
template<class T>
void dfs_print_stack(Node<T> root)
{
    std::stack<Node<T>> s;
    std::stack<int> depth_s;

    s.push(root);
    depth_s.push(0);

    while(not s.empty())
    {
        Node<T> n = s.top(); // There is some bizarre behavior here, try using a ref to see what I mean
        int depth = depth_s.top();
        s.pop();
        depth_s.pop();

        cout << "(" << depth << "," << n.value << ")" << endl;

        if(n.has_right())
        {
            s.push(n.get_right()); // This is corrupting something
            depth_s.push(depth+1);
        }
        if(n.has_left())
        {
            s.push(n.get_left()); // This is corrupting something
            depth_s.push(depth+1);
        }
    }
}

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

    ANNOUNCE_SECTION("BFS Print");
    bfs_print(A);

    ANNOUNCE_SECTION("DFS Print Stack");
    dfs_print_stack(A);
}