class Node;

template<class T>
class Edge {
public:
    Edge(Node& source, Node& destination, T& weight) : source(source), destination(destination), weight(weight)
    {}

    Node& source;
    Node& destination;
    T& weight;
}

template<class T>
class Node {
public:
    Node(T& value, std::list<Node&> neighbors_)

    T& value;
    std::list<Edge> edges;
};