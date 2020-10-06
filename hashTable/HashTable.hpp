#include "Node.hpp"

#define initial_size 2
#define doubling_percent 0.75
#define halving_percent 0.25
#define max_removed_percent 0.25

using namespace std;

class HashTable {
    private:
    uint8_t randomTable[256][8];
    vector<Node*> table;
    int size;
    int filledSpaces;
    int removedSpaces;
    short int control;

    public:
    HashTable();
    vector<Node*> getTable();
    Node* getNode(int i);
    int getSize();
    int getFilledSpaces();
    short int getControl();
    void setControl(int control);
    bool isEmpty();
    bool isFull();
    
    void fillRandomTable();
    uint64_t generateRandomNumber();
    vector<bitset<8> > breakKey(uint64_t key);

    int hashFunction(uint64_t key);
    int linearProbing(uint64_t key, int i);
    tuple<int,int> mapString(string line,uint64_t value);

    bool timeToDoubling();
    bool timeToHalving();
    bool timeToClean();

    void tableDoubling(vector<Node*> &table);
    void tableHalving(vector<Node*> &table);
    void tableClean(vector<Node*> &table);
    vector<Node*> copyElements();
    void reallocateElements(vector<Node*> &aux);

    void printTable(vector<Node*> table);

    tuple<int,int> insert(uint64_t key);
    tuple<int,int> remove(uint64_t key);
    tuple<int,int> search(uint64_t key);
    int findSlot(uint64_t key);
};