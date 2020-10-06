#include<iostream>
#include<vector>
#include<cmath>
#include<bitset>
#include<random>
#include<tuple>

using namespace std;

class Node {
    private:
    uint64_t key;
    bool removed;

    public:
    Node(uint64_t key);
    Node();
    uint64_t getNodeKey();
    bool isRemoved();
};