#include "HashTable.hpp"

HashTable::HashTable() {
    this->size = 2;
    this->filledSpaces = 0;
    table.resize(this->size, NULL);
}

Node* HashTable::getNode(int i) {
    return this->table[i];
}

vector<Node*> HashTable::getTable() {
    return this->table;
}

int HashTable::getFilledSpaces() {
    return this->filledSpaces;
}

bool HashTable::isEmpty() {
    return filledSpaces == 0;
}

bool HashTable::isFull() {
    return filledSpaces == this->size;
}

int HashTable::hashFunction(int key) {
     return key % this->size;
}

int HashTable::linearProbing(int key, int i) {
    return (hashFunction(key)+i) % size;
}

bool HashTable::timeToDoubling() {
    return this->filledSpaces == (this->size);
}

tuple<int,int> HashTable::mapString(string operation, int value) {
    if(operation == "INC")
        return this->insert(value);
    else if(operation == "REM") {
        return this->remove(value);
    }
    else if(operation == "BUS") {
        return this->search(value);
    }
    return make_tuple(-2,-2);
}
void HashTable::tableDoubling(vector<Node*> &table) {
    vector<Node*> aux(filledSpaces);
    int newKey;
    for(int i=0,j=0; i<table.size(); i++) {
        if(table[i]!=NULL && !table[i]->isRemoved()) {
            aux[j] = table[i];
            j++;
        }
    }
    this->size*=2;
    table.clear();
    table.resize(this->size,NULL);
    for(int i=0; i<aux.size(); i++) {
         int j=0;
         do {
             newKey = linearProbing(aux[i]->getNodeKey(), j);
             j++;
         }while(table[newKey]!=NULL);
         table[newKey] = aux[i];
     }
}

bool HashTable::timeToHalving() {
    return filledSpaces <= (this->size/4);
}

void HashTable::tableHalving(vector<Node*> &table) {
    vector<Node*> aux(filledSpaces);
    int newKey;
    for(int i=0,j=0; i<table.size(); i++) {
        if(table[i]!=NULL && !table[i]->isRemoved()) {
            aux[j] = table[i];
            j++;
        }
    }
    this->size/=2;
    table.clear();
    table.resize(this->size,NULL);

    for(int i=0; i<aux.size(); i++) {
         int j=0;
         do {
             newKey = linearProbing(aux[i]->getNodeKey(), j);
             j++;
         }while(table[newKey]!=NULL);
         table[newKey] = aux[i];
     }
}

void HashTable::printTable(vector<Node*> table) {
    for(int i=0; i<table.size(); i++) {
        if(table[i] == NULL ){
            cout << "no nulo" << endl;
            cout << "Tamanho da tabela: " << this->size << endl;
            cout << "------------------------------------------------------" << endl;
        }
        else {
            cout << "Posicao: " << i << endl;
            cout << "Chave: " << table[i]->getNodeKey() << endl;
            cout << "Tamanho da tabela: "<< table.size() << endl;
            cout << "------------------------------------------------------" << endl;
        }
        
    }
    cout << "preenchido: " << this->getFilledSpaces() << endl;
}

int HashTable::getSize() {
    return this->size;
}

tuple<int,int> HashTable::insert(int key) {
    Node *n = new Node(key);
    int i=0, slot;
    tuple<int,int> final;
    do {
        slot = linearProbing(key, i);
        i++;
    }while(table[slot]!=NULL);
    this->table[slot] = n;
    this->filledSpaces++;
    final = make_tuple(hashFunction(key),slot);
    if(timeToDoubling()) {
        tableDoubling(this->table);
        // cout << "o tamanho atual e:" << this->size<<endl;
    }
    return final;
}

tuple<int,int> HashTable::remove(int key) {
    Node *dummy = new Node();
    int index = get<1>(search(key)), i=1;
    tuple<int,int> final;
    get<0>(final) = hashFunction(key);
    if(index == -1) {
        get<1>(final) = -1;
    }
    else if(table[index]->getNodeKey() == key) {
        table[index] = dummy;
        get<1>(final) = index;
    }
    else {
        do {
            index = linearProbing(key,i);
            i++;
        }while(table[index]!=NULL || table[index]->getNodeKey() == key);
        table[index] = dummy;
        get<1>(final) = index;
    }
    filledSpaces--;
    if(timeToHalving())
        tableHalving(table);
    return final;
}

tuple<int,int> HashTable::search(int key) {
    int i = 0; int j;
    do {
        j = linearProbing(key, i);
        if(table[j]!=NULL && table[j]->getNodeKey() == key) {
            return make_tuple(hashFunction(key),j);
        }
        i++;
    }while(table[j]!=NULL || i==size);
    return make_tuple(hashFunction(key),-1);
}

int HashTable::findSlot(int key) {
    int temp=0, i=0;
    do {
        temp = linearProbing(0,i);
        if(table[temp]!=NULL) {
            return i;
        }
        else {
            i++;
        }
    }while(i<=hashFunction(key)-1);
    return -1;
}