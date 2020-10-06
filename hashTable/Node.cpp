#include "Node.hpp"

Node::Node(uint64_t key) {
    this->key = key;
    this->removed=false;
}

Node::Node() {  // false node.
    this->key = -1;
    this->removed = true;
}

uint64_t Node::getNodeKey() {
    return this->key;
}
bool Node::isRemoved() {
    return this->removed;
}