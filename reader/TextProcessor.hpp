#include<string>
#include<fstream>
#include "../hashTable/HashTable.hpp"

using namespace std;

class TextProcessor {
    private:
    ifstream input;
    fstream output;
    public:
    TextProcessor(string fileName,HashTable* h);
};

