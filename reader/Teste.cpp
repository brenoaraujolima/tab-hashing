#include "TextProcessor.hpp"

int main() {
    HashTable *h = new HashTable(); 
    TextProcessor *tp = new TextProcessor("arquivo.txt",h);
    
    return 0;
}