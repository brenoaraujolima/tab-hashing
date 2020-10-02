#include "Node.hpp"

Node::Node(int key) {
    this->key = key;
    this->removed=false;
}

Node::Node() {  // false node.
    this->key = -1;
    this->removed = true;
}

int Node::getNodeKey() {
    return this->key;
}
bool Node::isRemoved() {
    return this->removed;
}