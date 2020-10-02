#include "hashTable/HashTable.hpp"

int main() {
    HashTable *h = new HashTable();
    h->insert(4,"Fortaleza");
    h->insert(20, "Santos");
    h->insert(20,"Goiania");
    h->insert(10, "BUenos Aires");
    h->insert(210, "Brasilia");
    h->insert(16,"Belo Horizonte");
    h->insert(40,"Recife");
    h->insert(27,"Campinas");
    h->insert(2,"Aracoiaba");
    h->insert(8,"Florianopolis");

    h->remove(20);
    h->remove(40);
    h->remove(210);
    h->remove(10);

    h->insert(10,"California");

    cout << h->search(5) << endl;

    h->printTable(h->getTable());
    return 0;
}