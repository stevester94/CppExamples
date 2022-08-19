#ifndef __TREES_HPP__
#define __TREES_HPP__
#include <list>

namespace graph {

template<class T>
class Edge;

// So it definitely makes sense to make a node a template, since
// the content of a node could be anything
template<class T>
class Node {
private:
    class Edge {
    public:
        Edge(Node<T>& source, Node<T>& destination, int weight) : source(source), destination(destination), weight(weight)
        {}

        Node& source;
        Node& destination;
        int weight;
    };

public:
    Node(T& value) {}

    void add_edge(Node<T>& destination, int weight)
    {
        edges.push_back(Edge(*this, destination, weight));
    }

    T& value;
    std::list<Edge> edges;
};

}; //NS: graph

#endif