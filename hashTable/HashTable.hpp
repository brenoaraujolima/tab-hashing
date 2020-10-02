#include "Node.hpp"
#include<tuple>

using namespace std;
class HashTable {
    private:
        vector<Node*> table;
        int size;
        int filledSpaces;
    public:
        HashTable();
        Node* getNode(int i);
        vector<Node*> getTable();
        int getFilledSpaces();
        bool isFull();
        bool isEmpty();
        int hashFunction(int key);
        int linearProbing(int key, int i);
        bool timeToDoubling();
        tuple<int,int> mapString(string line, int value);
        void tableDoubling(vector<Node*> &table);
        bool timeToHalving();
        void tableHalving(vector<Node*> &table);
        void printTable(vector<Node*> table);
        int getSize();
        tuple<int,int> insert(int key);
        tuple<int,int> remove(int key);
        tuple<int,int> search(int key);
        int findSlot(int key); 
};