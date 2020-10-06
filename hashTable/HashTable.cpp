#include "HashTable.hpp"

HashTable::HashTable() {
    this->size = 2;
    this->filledSpaces = 0;
    this->removedSpaces = 0;
    this->control = 0;
    table.resize(this->size, NULL);
    this->fillRandomTable();
}

vector<Node*> HashTable::getTable() {
    return this->table;
}

Node* HashTable::getNode(int i) {
    return this->table[i];
}

int HashTable::getSize() {
    return this->size;
}

int HashTable::getFilledSpaces() {
    return this->filledSpaces;
}

short int HashTable::getControl() {
    return this->control;
}

void HashTable::setControl(int control) {
    this->control = control;
} 

bool HashTable::isEmpty() {
    return filledSpaces == 0;
}

bool HashTable::isFull() {
    return filledSpaces == this->size;
}

void HashTable::fillRandomTable() {
    for(int i=0; i<256; i++) {
        for(int j=0; j<8; j++) {
            this->randomTable[i][j] = generateRandomNumber();
        }
    }
}

uint64_t HashTable::generateRandomNumber() {
    mt19937_64 gen (std::random_device{}());
    uint64_t randomNumber = gen();
    randomNumber = 1+(rand()+randomNumber)/(1+rand()%5);
    return randomNumber;
}

vector<bitset<8> > HashTable::breakKey(uint64_t key) {
    vector<bitset<8> > block(8);
    block[0] = (key)&0xFFFF;
    block[1] = (key>>8)&0xFFFF;
    block[2] = (key>>16)&0xFFFF;
    block[3] = (key>>24)&0xFFFF;
    block[4] = (key>>32)&0xFFFF;
    block[5] = (key>>40)&0xFFFF;
    block[6] = (key>>48)&0xFFFF;
    block[7] = (key>>56)&0xFFFF;
    return block;
}

int HashTable::hashFunction(uint64_t key) {
    vector<bitset<8> > block(8);
    block = breakKey(key);
    bitset<8> st_hashing = (
        randomTable[block[0].to_ulong()][0] ^
        randomTable[block[1].to_ulong()][1] ^
        randomTable[block[2].to_ulong()][2] ^
        randomTable[block[3].to_ulong()][3] ^
        randomTable[block[4].to_ulong()][4] ^
        randomTable[block[5].to_ulong()][5] ^
        randomTable[block[6].to_ulong()][6] ^
        randomTable[block[7].to_ulong()][7] 
    ) % size;
    return st_hashing.to_ulong();
}

int HashTable::linearProbing(uint64_t key, int i) {
    return (hashFunction(key)+i) % size;
}

tuple<int,int> HashTable::mapString(string operation,uint64_t value) {
    if(operation == "INC") 
        return this->insert(value);
    else if(operation == "REM")
        return this->remove(value);
    else if(operation == "BUS")
        return this->search(value);
    return make_tuple(-2,-2);
}

bool HashTable::timeToDoubling() {
    return this->filledSpaces >= (this->size*doubling_percent);
}

bool HashTable::timeToHalving() {
    return filledSpaces <= (this->size*halving_percent);
}

bool HashTable::timeToClean() {
    return removedSpaces >= (this->size/4);
}

void HashTable::tableDoubling(vector<Node*> &table) {
    vector<Node*> aux = copyElements();
    this->size*=2;
    table.clear();
    table.resize(this->size,NULL);
    reallocateElements(aux);
}

void HashTable::tableHalving(vector<Node*> &table) {
    vector<Node*> aux = copyElements();
    this->size/=2;
    table.clear();
    table.resize(this->size,NULL);
    reallocateElements(aux);
    removedSpaces = 0;
}

void HashTable::tableClean(vector<Node*> &table) {
    vector<Node*> aux = copyElements();
    table.clear();
    table.resize(this->size,NULL);
    reallocateElements(aux);
    removedSpaces = 0;
}

vector<Node*> HashTable::copyElements() {
    vector<Node*> aux(filledSpaces);
    for(int i=0,j=0; i<table.size(); i++) {
        if(table[i]!=NULL && !table[i]->isRemoved()) {
            aux[j] = table[i];
            j++;
        }
    }
    return aux;
}

void HashTable::reallocateElements(vector<Node*> &aux) {
    int newKey, j;
    for(int i=0; i<aux.size(); i++) {
         j=0;
         do {
             newKey = linearProbing(aux[i]->getNodeKey(), j);
             j++;
         }while(table[newKey]!=NULL);
         table[newKey] = aux[i];
     }
}

void HashTable::printTable(vector<Node*> table) {
    for(int i=0; i<table.size(); i++) {
        if(table[i] == NULL )
            cout << "N  ";
        else if(table[i]->getNodeKey() == -1)
            cout << -1 << "  ";
        else 
            cout << table[i]->getNodeKey() << "  ";
    }
    cout << "preenchidos: " << this->getFilledSpaces() << "  ";
    cout << "removidos: " << this->removedSpaces << endl;
}

tuple<int,int> HashTable::insert(uint64_t key) {
    tuple<int,int> final;
    Node *n = new Node(key);
    int i=0, slot;
    do {
        slot = linearProbing(key, i);
        i++;
    }while(table[slot]!=NULL || i==size);
    if(i == size) {
        slot = findSlot(key);
    }
    if(table[slot] != NULL && table[slot]->isRemoved())
        removedSpaces--;
    this->table[slot] = n;
    this->filledSpaces++;
    final = make_tuple(hashFunction(key),slot);
    if(timeToDoubling()) {
        this->control = 1;
        tableDoubling(this->table);
    }
    return final;
}

tuple<int,int> HashTable::remove(uint64_t key) {
    Node *dummy = new Node();
    tuple<int,int> final;
    int index = get<1>(search(key)), i=1;
    get<0>(final) = hashFunction(key);
    if(index == -1) {
        get<1>(final) = -1;
        return final;
    }
    else if(table[index]->getNodeKey() == key) {
        table[index] = dummy;
        get<1>(final) = index;
        filledSpaces--;
        removedSpaces++;
    }
    
    if(timeToHalving()) {
        this->control = 2;
        tableHalving(table);
    }     
    else if(timeToClean()) {
        this->control = 3;
        tableClean(table);
    }  
    return final;
}

tuple<int,int> HashTable::search(uint64_t key) {
    int i = 0; int j;
    do {
        j = linearProbing(key, i);
        if(table[j]!=NULL && table[j]->getNodeKey() == key)
            return make_tuple(hashFunction(key),j);
        i++;
    } while(table[j]!=NULL || i==size);
    if(i == size) {
        for(int s=0; s<hashFunction(key); s++) {
            if(table[j]!=NULL && table[j]->getNodeKey() == key)
                return make_tuple(hashFunction(key),s);               
        }
        return make_tuple(hashFunction(key),j);
    }
    return make_tuple(hashFunction(key),-1);
}

int HashTable::findSlot(uint64_t key) {
    for(int i=0; i<hashFunction(key); i++) {
        if(table[i]==NULL) {
            return i;
        }
    }
    return -1;
}