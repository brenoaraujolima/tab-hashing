#include "reader/TextProcessor.hpp"

int main(int argc, char *argv[]) {
    HashTable *h = new HashTable();
    TextProcessor *tp = new TextProcessor(argv[1],h);
    return 0;
}