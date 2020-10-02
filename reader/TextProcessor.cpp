#include "TextProcessor.hpp"

TextProcessor::TextProcessor(string fileName, HashTable* h) {
    string line, secondLine, temp;
    int value;
    tuple<int,int> data;
    ofstream output("saida.txt");
    this->input.open(fileName,ios::in);

    while(getline(input,line)) {
        output << line << "\n";
        temp = line.substr(0,3);
        value = stoi(line.substr(4));
        data = h->mapString(temp,value);
        output << get<0>(data) << "  ";
        output << get<1>(data) << "  ";
        cout << "hash: " <<get<0>(data) << endl;
        cout << "posicao: "<< get<1>(data) << endl;
        output << endl << endl << endl;
    }
}

string TextProcessor::mapping(string operation, int value) {

}