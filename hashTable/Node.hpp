#include<iostream>
#include<vector>

using namespace std;

class Node {
    private:
    int key;
    bool removed;

    public:
    int getNodeKey();
    Node(int key);
    Node();
    bool isRemoved();
};